void radioListen(){
  if (rf69.available()) {
    // Should be a message for us now
    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf69.recv(buf, &len)) {
      if (!len) return;
      buf[len] = 0;
      Serial.print("Received [");
      Serial.print(len);
      Serial.print("]: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf69.lastRssi(), DEC);

      if (strstr((char *)buf, "grab")) {
        grabSample();
        // Send a reply!
        uint8_t data[] = "Grabbing sample";
        rf69.send(data, sizeof(data));
        rf69.waitPacketSent();
        Serial.println("Sent a reply");
        Blink(LED, 40, 3); // blink LED 3 times, 40ms between blinks
      }

      if (strstr((char *)buf, "Hello World")) {
        // Send a reply!
        uint8_t data[] = "And hello back to you";
        rf69.send(data, sizeof(data));
        rf69.waitPacketSent();
        Serial.println("Sent a reply");
        Blink(LED, 40, 3); // blink LED 3 times, 40ms between blinks
      }
    } else {
      Serial.println("Receive failed");
    }
  }
}


void report(char message){
const uint8_t* myUint8Ptr = reinterpret_cast<const uint8_t*>(message);
 rf69.send(myUint8Ptr, sizeof(message));
 rf69.waitPacketSent();
}


void reportTimestamp(){
 float time = GPS.secondsSinceDate();
 char charTime = 'T';
 charTime += char(time);
 
 report(charTime);
}


int interval = 5000;
int lastTimeReport = 0;
void isItTimeToReportTimeStamp(){ 
 if ((millis() - lastTimeReport) > interval){
   reportTimestamp();
   lastTimeReport = millis();
 }
}


void Blink(byte pin, byte delay_ms, byte loops) {
  while (loops--) {
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
  }
}
