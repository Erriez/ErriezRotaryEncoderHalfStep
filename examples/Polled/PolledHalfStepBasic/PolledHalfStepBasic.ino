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

/* Polled Half Step Rotary Encoder basic example
 * Source: https://github.com/Erriez/ErriezRotaryEncoderHalfStep
 */

#include <Arduino.h>
#include <RotaryHalfStep.h>

// Connect rotary pins to the DIGITAL or ANALOG pins of the Arduino board
// Use A0..A7 when using analog pins
#define ROTARY_PIN1   2
#define ROTARY_PIN2   3

// Initialize half step rotary encoder with internal pull-up pins enabled
// and default sensitivity=100
RotaryHalfStep rotary(ROTARY_PIN1, ROTARY_PIN2);

void setup()
{
  // Initialize Serial port
  Serial.begin(115200);
  Serial.println(F("Basic example polled half step Rotary Encoder"));
}

void loop()
{
  int rotaryState;

  // Read rotary state
  rotaryState = rotary.read();

  // Print count value when rotary changed
  if ((rotaryState > 0) || (rotaryState < 0)) {
    Serial.println(rotaryState);
  }
}
