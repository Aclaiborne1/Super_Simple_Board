// CONTROL MODULE, SETS PROGRAM UP, RUNS FLIGHT MODE WHEN flownAdd IS 0
// RUNS MENU MODE WHEN flownAdd IS 1

#include <Wire.h> // needed for i2C
#include <Adafruit_Sensor.h> // needed for sensors
#include <Adafruit_ADXL345_U.h> // for ADXL 345 accelerometer
#include <Adafruit_BMP085_U.h> // for altimeter
#include <Adafruit_FRAM_I2C.h> // for FRAM
#include "Rocket2.h"
#include "Flight.h"
#include "Menu.h"

#define buzzerPin 4
#define redLEDPin 5
#define greenLEDPin 6

// initialize boards and objects
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // for accelerometer
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085); // for altimeter
Adafruit_FRAM_I2C fram = Adafruit_FRAM_I2C(); // for FRAM

sensor_t sensor;
sensors_event_t event;

const int maxBytes = 4000;
const int flownAdd = maxBytes + 2;
const int timeAdd = maxBytes + 4;
const int altStart = 0;
const int geesStart = maxBytes / 2;
const int dataPoints = maxBytes / 4; // two bytes per data point, two sets of data points (alt and acc).
const float seaLevelPressure = 1013.0; // millibars

float groundlevel;
long elapsedtime;
boolean flown;

void setup() 
{
  initialize();
  
  delay(2000);
  Serial.println("started.");
}

void loop()
{
  flown = retrieve(flownAdd);
  if(flown) menu(); // if already flown, go to menu
  else flight();
}
  

