#!/bin/sh

# Install Python platformio 
# pip install -U platformio

# Update library
# git fetch
# git pull

# Build example(s)
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptHalfStepBasic/InterruptHalfStepBasic.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptHalfStepButton/InterruptHalfStepButton.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptHalfStepCounter/InterruptHalfStepCounter.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledHalfStepBasic/PolledHalfStepBasic.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledHalfStepButton/PolledHalfStepButton.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledHalfStepCounter/PolledHalfStepCounter.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledHalfStepMultiple/PolledHalfStepMultiple.ino
