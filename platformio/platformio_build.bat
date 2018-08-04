rem Install Python27 platformio
rem C:\Python27\Scripts\pip.exe install -U platformio

rem Set Python path
set PATH=%PATH%;C:\Python27
set PATH=%PATH%;C:\Python27\Scripts

rem Update library
rem git fetch
rem git pull

rem Build example(s)
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptHalfStepBasic/InterruptHalfStepBasic.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptHalfStepButton/InterruptHalfStepButton.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Interrupt/InterruptHalfStepCounter/InterruptHalfStepCounter.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledHalfStepBasic/PolledHalfStepBasic.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledHalfStepButton/PolledHalfStepButton.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledHalfStepCounter/PolledHalfStepCounter.ino
platformio ci --lib=".." --project-conf=platformio.ini ../examples/Polled/PolledHalfStepMultiple/PolledHalfStepMultiple.ino

@pause
