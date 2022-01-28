#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#define SD_PIN 4
#define DHT_PIN 2
#define DHT_TYPE DHT11
#define R_LED_PIN 10
#define G_LED_PIN 9
#define B_LED_PIN 6
#define ERR 0
#define GOOD 1
#define NOTIF 2
#define MAX_READINGS 100

File dataFile;
const char* filename = "tempdata.txt";
DHT dht(DHT_PIN, DHT_TYPE);
int numReadings = 0;
unsigned long timeDelay = 360000L;

void setup() {

  pinMode(R_LED_PIN, OUTPUT);
  pinMode(G_LED_PIN, OUTPUT);
  pinMode(B_LED_PIN, OUTPUT);

  // Show a notification/initialization status light
  statusLight(NOTIF);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial);

  // Attempt to connect to the SD card module
  if (!SD.begin(SD_PIN)) {
    // Trigger error light if initialization failed
    statusLight(ERR);
    while (1);
  }

  // Attempt to open the data file
  dataFile = SD.open(filename, FILE_WRITE);

  // Trigger an error light if the file failed to open
  if (!dataFile) {
    statusLight(ERR);
    while (1);
  }


  // Begin communications with the temp sensor
  dht.begin();

  // Delay for a second and then show the all good status light
  delay(1000);
  statusLight(GOOD);
}

void loop() {
  // Read the current temp (C)
  float t = dht.readTemperature();

  // Check if the read was successful
  if (isnan(t)) {
    // Trigger error light if not a successful read
    statusLight(ERR);
  }
  else {
    logTempData(t);
  }

  numReadings++;

  if (numReadings >= MAX_READINGS) {
    dataFile.close();
    statusLight(NOTIF);
    while (1);
  }

  // delay for 6 mins
  delay(timeDelay);
//  delay(1000);



}


void logTempData(float temp) {
  if (dataFile) {
    dataFile.println(temp);
    Serial.println(temp);
  }
  else {
    // Something went wrong
    statusLight(ERR);
    while (1);
  }
}

void statusLight(int status) {
  if (status == 0) {
    // Error - red light
    analogWrite(R_LED_PIN, 50);
    analogWrite(G_LED_PIN, 0);
    analogWrite(B_LED_PIN, 0);
  }
  else if (status == 1) {
    // Normal - green light
    analogWrite(R_LED_PIN, 0);
    analogWrite(G_LED_PIN, 50);
    analogWrite(B_LED_PIN, 0);
  }
  else {
    // Notification - blue
    analogWrite(R_LED_PIN, 0);
    analogWrite(G_LED_PIN, 0);
    analogWrite(B_LED_PIN, 50);
  }
}
