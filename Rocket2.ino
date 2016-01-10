// MODULE FOR INITIALIZING, STORING, RETRIEVING, OPERATING SENSORS

void initialize()
{
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
 
  accel.getSensor(&sensor); // attaching the accelerometer
  accel.begin();
  accel.setRange(ADXL345_RANGE_16_G); // setting to +- 16 gees
  
  bmp.getSensor(&sensor); // attaching the altimeter
  bmp.begin();
}

// store and retrieve routines
void store(int z, int bytecounter)
// pushes integer into two bytes of FRAM starting at bytecounter
{
  fram.begin();
  fram.write8(bytecounter, highByte(z));
  fram.write8(bytecounter + 1, lowByte(z));
}

int retrieve(int bytecounter)
// retrieves integer from two bytes of FRAM starting at bytecounter
{
  fram.begin();
  byte high = fram.read8(bytecounter);
  byte low = fram.read8(bytecounter + 1);
  int z = (high << 8) + low;
  return(z);
}

//returns height AGL in feet as integer
int getfeet()
{
  int xfeet;
  float height = getaltitude();
  xfeet = ((height * 3.2808) - groundlevel) + 0.5;
  
  return(xfeet);
}

//returns integer that is 100 X actual gees
int getgees()
{
  float xaxis;
  int xgees;
  accel.getSensor(&sensor); // attaching the accelerometer
  accel.getEvent(&event);

  xaxis = event.acceleration.x; // meters per second squared
  xgees = 100.0 * (xaxis / 9.81) + 0.5; // 9.81 meters per second squared is one gee - returning 100 * gees
  
  return(xgees);
}

// returns altitude in meters
float getaltitude()
{
  float y; 
  sensors_event_t event; // get a new sensor event
  
  bmp.getSensor(&sensor); 
  bmp.getEvent(&event);
  
  if (event.pressure)
  {
    float temperature;
    bmp.getTemperature(&temperature);
    // convert the atmospheric pressure, SLP and temp to altitude
    float Altitude =  (bmp.pressureToAltitude(seaLevelPressure, event.pressure, temperature));
    y = Altitude;
  }
  return(y);
}

//sets ground level in feet as float
void setgroundlevel()
{
  int i, intground;
  float floatground, groundacc;
  
  floatground = getaltitude(); // one shot just for grins
 
  // now get groundlevel
  
  groundacc = 0.0;
  for (i = 0; i < 10; i++)
    groundacc += getaltitude();
  
  floatground = groundacc / 10.0; // gets average value
  floatground = 3.2808 * floatground; // converting meters to feet
  groundlevel = floatground;

  intground = floatground + 0.5;
}
