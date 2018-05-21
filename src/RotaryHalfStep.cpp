/*
 * MIT License
 *
 * Copyright (c) 2018 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *     RotaryHalfStep.cpp
 * \brief
 *     Three speed half step Rotary Encoder library for Arduino.
 * \details
 *     Source: https://github.com/Erriez/ErriezRotaryEncoderHalfStep
 */

#if (defined(__AVR__))
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif

#include "RotaryHalfStep.h"

#define DIR_NONE  0x00      //!< No complete step yet
#define DIR_CW    0x10      //!< Clockwise step
#define DIR_CCW   0x20      //!< Counter-clockwise step

// Use the half-step state table (emits a code at 00 and 11)
#define RHS_START         0x00     //!< Rotary half step start
#define RHS_CCW_BEGIN     0x01     //!< Rotary half step counter clock wise begin
#define RHS_CW_BEGIN      0x02     //!< Rotary half step clock wise begin
#define RHS_START_M       0x03     //!< Rotary half step start
#define RHS_CW_BEGIN_M    0x04     //!< Rotary half step clock wise begin
#define RHS_CCW_BEGIN_M   0x05     //!< Rotary half step counter clock wise begin

static const PROGMEM uint8_t halfStepTable[6][4] = {
    // RHS_START (00)
    {RHS_START_M,           RHS_CW_BEGIN,     RHS_CCW_BEGIN,    RHS_START},
    // RHS_CCW_BEGIN
    {RHS_START_M | DIR_CCW, RHS_START,        RHS_CCW_BEGIN,    RHS_START},
    // RHS_CW_BEGIN
    {RHS_START_M | DIR_CW,  RHS_CW_BEGIN,     RHS_START,        RHS_START},
    // RHS_START_M (11)
    {RHS_START_M,           RHS_CCW_BEGIN_M,  RHS_CW_BEGIN_M,   RHS_START},
    // RHS_CW_BEGIN_M
    {RHS_START_M,           RHS_START_M,      RHS_CW_BEGIN_M,   RHS_START | DIR_CW},
    // RHS_CCW_BEGIN_M
    {RHS_START_M,           RHS_CCW_BEGIN_M,  RHS_START_M,      RHS_START | DIR_CCW},
};

/*!
 * \brief
 *     Constructor half step Rotary Encoder
 * \param pin1
 *     Rotary Encoder pin 1
 * \param pin2
 *     Rotary Encoder pin 2
 * \param pullUp
 *     true:  Enable internal pull-up on Rotary Encoder pins [default argument].
 *     false: Disable internal pull-up on Rotary Encoder pins.
 * \param sensitivity
 *     Set sensitivity rotation speed value 0..255.
 *     A higher is more sensitive for rotation speed, a smaller value is less
 *     sensitive or will disable speed detection.
 *     Default is 100.
 */
RotaryHalfStep::RotaryHalfStep(uint8_t pin1, uint8_t pin2, bool pullUp, uint8_t sensitivity) :
    _pin1(pin1), _pin2(pin2), _state(0), _sensitivity(sensitivity)
{
    if (pullUp) {
        // Enable internal pull-up
        pinMode(_pin1, INPUT_PULLUP);
        pinMode(_pin2, INPUT_PULLUP);
    }
}

/*!
 * \brief
 *     Read Rotary Encoder state
 * \details
 *     Call this function as fast as possible to prevent missing pin changes.
 *     This seems to work for most rotary encoders when calling this function
 *     within 10ms in an endless loop.
 *
 *     The sensitivity value is used to calculate three rotation speeds by
 *     measuring the speed of the Rotary Encoder pin changes. The rotation speed
 *     depends on the number of Rotary notches and knob size. The value should
 *     experimentally determined.
 * \return Rotary speed and direction
 *     -3: Counter clockwise turn, multiple notches fast
 *     -2: Counter clockwise turn, multiple notches
 *     -1: Counter clockwise turn, single notch
 *      0:  No change
 *      1:  Clockwise turn, single notch
 *      2:  Clockwise turn, multiple notches
 *      3:  Clockwise turn, multiple notches fast
 */
int RotaryHalfStep::read()
{
    int pinState;
    int rotaryState;
    unsigned long timeStamp;
    unsigned long changeTime;

    // Sample rotary digital pins
    pinState = (digitalRead(_pin1) << 1) | digitalRead(_pin2);

    // Determine new state from the pins and state table.
    _state = pgm_read_byte(&halfStepTable[_state & 0x0f][pinState]);

    // Check rotary state
    switch (_state & 0x30) {
        case DIR_CW:
            rotaryState = 1;
            break;
        case DIR_CCW:
            rotaryState = -1;
            break;
        case DIR_NONE:
        default:
            rotaryState = 0;
    }

    // Check if rotary changed
    if (rotaryState != 0) {
        timeStamp = millis();
        changeTime = timeStamp - _lastChange;
        _lastChange = timeStamp;

        // Check speed change
        if (changeTime < (_sensitivity / 2)) {
            rotaryState *= 3;
        } else if (changeTime < _sensitivity) {
            rotaryState *= 2;
        }
    }

    return rotaryState;
}

/*!
 * \brief
 *     Set sensitivity value.
 * \param sensitivity
 *     Sensitivity value 0..255
 */
void RotaryHalfStep::setSensitivity(uint8_t sensitivity)
{
    _sensitivity = sensitivity;
}

/*!
 * \brief
 *     Get sensitivity value.
 * \return
 *     Sensitivity value 0..255.
 */
uint8_t RotaryHalfStep::getSensitivity()
{
    return _sensitivity;
}
