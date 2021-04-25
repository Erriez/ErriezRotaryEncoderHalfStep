#/bin/bash

# Automatic build script
#
# To run locally, execute:
# sudo apt install doxygen graphviz texlive-latex-base texlive-latex-recommended texlive-pictures texlive-latex-extra

# Exit immediately if a command exits with a non-zero status.
set -e

echo "Starting auto-build script..."


function autobuild()
{
    # Set environment variables
    BOARDS_AVR="--board uno --board micro --board miniatmega328 --board nanoatmega328new --board pro16MHzatmega328 --board pro8MHzatmega328 --board megaatmega2560 --board leonardo"
    BOARDS_ARM="--board due"
    BOARDS_ESP="--board d1_mini --board nodemcuv2 --board lolin_d32"
    BOARDS_SAMD="--board sparkfun_samd21_mini_usb"
    BOARDS_STM32="--board blackpill_f103c8"

    echo "Building examples..."
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} ${BOARDS_SAMD} ${BOARDS_STM32} examples/Interrupt/InterruptHalfStepBasic/InterruptHalfStepBasic.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} ${BOARDS_SAMD} ${BOARDS_STM32} examples/Interrupt/InterruptHalfStepButton/InterruptHalfStepButton.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} ${BOARDS_SAMD} ${BOARDS_STM32} examples/Interrupt/InterruptHalfStepCounter/InterruptHalfStepCounter.ino

    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} ${BOARDS_SAMD} ${BOARDS_STM32} examples/Polled/PolledHalfStepBasic/PolledHalfStepBasic.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} ${BOARDS_SAMD} ${BOARDS_STM32} examples/Polled/PolledHalfStepButton/PolledHalfStepButton.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} ${BOARDS_SAMD} ${BOARDS_STM32} examples/Polled/PolledHalfStepCounter/PolledHalfStepCounter.ino
    platformio ci --lib="." ${BOARDS_AVR} ${BOARDS_ARM} ${BOARDS_ESP} ${BOARDS_SAMD} ${BOARDS_STM32} examples/Polled/PolledHalfStepMultiple/PolledHalfStepMultiple.ino
}

function generate_doxygen()
{
    echo "Generate Doxygen HTML..."

    DOXYGEN_PDF="ErriezRotaryEncoderHalfStep.pdf"

    # Cleanup
    rm -rf html latex

    # Generate Doxygen HTML and Latex
    doxygen Doxyfile

    # Allow filenames starting with an underscore    
    echo "" > html/.nojekyll

    # Generate PDF when script is not running on Travis-CI
    if [[ -z ${TRAVIS_BUILD_DIR} ]]; then
        # Generate Doxygen PDF
        make -C latex

        # Copy PDF to root directory
        cp latex/refman.pdf ./${DOXYGEN_PDF}
    fi
}

autobuild
generate_doxygen
