# ArduinoTempDataLogger
The purpose of this project is to measure temperature data and record it on a microSD card. Temperature is measured and recorded every 6 minutes and 100 measurements are gathered, for a total of 10 hours of temperature data. Time between temperature readings and number of measurements performed can be modified by changing "timeDelay" and "MAX_READINGS" respectively.
## Components Used:
* Arduino Uno R3
* DHT11 Temperature/Humidity Sensor Breakout Board
* RGB LED Breakout Board
* HW-125 MicroSD Breakout Board

## Wiring
* DHT11
  * Signal -> Pin 2
  * VCC -> 5V
  * GND -> GND
* RGB LED
  * R -> Pin 10
  * G -> Pin 9
  * B -> Pin 6
  * GND -> GND
* HW-125
  * CS -> Pin 4
  * MOSI -> Pin 11
  * MISO -> Pin 12
  * VCC -> 5V
  * GND -> GND

## LED Status Lights
* Green: Datalogger is running and taking measurements
* Blue: Datalogger is initializing or has completed running
* Red: Datalogger has run into an error, no measurements performed
