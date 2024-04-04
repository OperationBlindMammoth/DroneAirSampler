// dtostrf(float_value, min_width, num_digits_after_decimal, where_to_store_string)
//https://www.programmingelectronics.com/dtostrf/

void datalog(String data){
  float time = GPS.secondsSinceDate();
  float lat = GPS.latitudeDegrees;
  float lon = GPS.longitudeDegrees;
  float alt = GPS.altitude;
  
  String charTime = String(time);
  String charMillis = String(millis());
  String charLat = String(lat);
  String charLon = String(lon);
  String logString = "";

  // dtostrf(time,7,2,charTime);
  // dtostrf(millis(),8,2,charMillis);

  logString += data;
  logString += ",";
  logString += charMillis;
  logString += ",";
  logString += charTime;
  logString += ",";
  logString += charLat;
  logString += ",";
  logString += charLon;


  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile){
    dataFile.println(logString);
    dataFile.close();
    Serial.print("Logged: ");
    Serial.println(logString);
  }
}





