// MODULE FOR MENU MODE

void menu()
{
  int flightCounter, dataIndex, feet, gees;
  float duration, timeInterval, flightTime;
  
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(redLEDPin, HIGH); // red LED on solid in menu mode
  
  delay(3000);
  
  duration = (retrieve(timeAdd));
  timeInterval = duration / dataPoints; // interval per record
  flightTime = 0;
  
  Serial.println("Flight data");
  Serial.println("time\talt\tacc");
  for (flightCounter=0; flightCounter<dataPoints; flightCounter++)
  {
    dataIndex = flightCounter * 2;
    Serial.print(flightTime); Serial.print("\t");
    Serial.print(retrieve(altStart + dataIndex)); Serial.print("\t");
    Serial.println(retrieve(geesStart + dataIndex));
    flightTime += timeInterval;
  }
  Serial.println(); Serial.print("Total elapsed time: "); Serial.print(retrieve(timeAdd));
  Serial.println(" seconds");
  
  Serial.println(); Serial.print("Type anything and press \"Enter\" to prepare for flight");
  while(Serial.available() <=0) {}
  Serial.read();
  
  flown = false;
  store(flown, flownAdd);
  Serial.println(); Serial.println("Ready to fly.");
  
  // flashing LEDs indicate program will enter flight mode on reset 
  while(true)
  {
    digitalWrite(redLEDPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
    delay(200);
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
    delay(200);
  }
}

