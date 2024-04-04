int millisecondssinceJan24(){
  int milliseconds = 0;
  milliseconds += (GPS.year-2024) * 31536000000;
  //milliseconds += ()
  return 0;
}



void getTime(){
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()));
  }
 
  Serial.print("Seconds since date: ");
  Serial.println(GPS.secondsSinceDate());

  Serial.print("GPS.available: ");
  Serial.println(GPS.available());

  Serial.print("Latitude: ");
  Serial.println(GPS.latitude);
  Serial.print("Longitude: ");
  Serial.println(GPS.longitude);

  Serial.print("Year:");
  Serial.print(GPS.year);
  Serial.print(" Month:");
  Serial.print(GPS.month);
  Serial.print(GPS.day);
  Serial.print(GPS.hour);
  Serial.print(GPS.minute);
  Serial.print(GPS.seconds);
  Serial.println(GPS.milliseconds);

  Serial.println();  

  
}