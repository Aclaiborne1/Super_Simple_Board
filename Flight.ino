// MODULE FOR FLIGHT MODE

void flight()
{
  int flightCounter, dataIndex, feet, gees, flightDuration;
  long starttime;
 
 // WAITS A MINUTE AFTER STARTUP
 
  digitalWrite(redLEDPin, HIGH); // both LEDs on solid, indicating flight mode entered
  digitalWrite(greenLEDPin, HIGH);
  setgroundlevel();
  delay(60000);
  digitalWrite(redLEDPin, LOW); // turn off red LED, solo green LED indicates recording
  digitalWrite(buzzerPin, HIGH); // sound buzzer
  delay(1000);
  digitalWrite(buzzerPin, LOW);

// NOW START ACQUIRING DATA
  
  flightCounter = 0;
  
  starttime = millis();
  while(flightCounter < dataPoints)
  {
    dataIndex = flightCounter * 2; // each 'store' takes two bytes
    
    feet = getfeet(); // altitude AGL in feet
    store(feet, altStart + dataIndex);
    delay(10);
     
    gees = getgees(); // acceleration in gees * 100
    store(gees, geesStart + dataIndex);
    delay(10);
    
    flightCounter++;
  }
  
  flown = true;
  store(flown, flownAdd); // will enter menu mode on reset
  elapsedtime = millis() - starttime; // in milliseconds
  flightDuration = elapsedtime / 1000.0; // in seconds
  store(flightDuration, timeAdd);
  digitalWrite(greenLEDPin, LOW); // turn off green LED, recording has ended
  digitalWrite(redLEDPin, HIGH);
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
  
  // flashing red LED indicates recording is completed in flight mode
  while(true)
  {
    digitalWrite(redLEDPin, LOW);
    delay(200);
    digitalWrite(redLEDPin, HIGH);
    delay(200);
  }
}
