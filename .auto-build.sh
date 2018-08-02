#!/bin/sh

################################################################################
# Title         : .auto-build.sh
# Date created  : 2 August 2018
__AUTHOR__="Erriez"
#
# This script will start PlatformIO build.
#
################################################################################

################################################################################
##### Setup this script and get the current gh-pages branch.               #####
echo 'Setting up the script...'

# Exit with nonzero exit code if anything fails
set -e

# Build sources
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Interrupt/InterruptHalfStepBasic/InterruptHalfStepBasic.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Interrupt/InterruptHalfStepButton/InterruptHalfStepButton.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Interrupt/InterruptHalfStepCounter/InterruptHalfStepCounter.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Polled/PolledHalfStepBasic/PolledHalfStepBasic.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Polled/PolledHalfStepButton/PolledHalfStepButton.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Polled/PolledHalfStepCounter/PolledHalfStepCounter.ino
platformio ci --lib="." --project-conf=platformio/platformio.ini examples/Polled/PolledHalfStepMultiple/PolledHalfStepMultiple.ino
