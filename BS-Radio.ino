void grabSample(){
  //Serial.print("grab sample");
  char radiopacket[12] = "grab";
  itoa(packetnum++, radiopacket+13, 10);
  Serial.print("Sending..."); 
  Serial.println(radiopacket);
  //display("Sending ");
  //display(radiopacket);

  rf69.send((uint8_t *)radiopacket, strlen(radiopacket));
  //rf69.send(radiopacket,sizeof(radiopacket));
  rf69.waitPacketSent();
  Serial.println("Sent");
  delay(1000);  // So you don't send requests too quickly
}

void radioListen(){
  if (rf69.available()) {
    // Should be a message for us now
    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf69.recv(buf, &len)) {
      if (!len) return;
      buf[len] = 0;
      Serial.print("Received [");
      display("Received: ");
      Serial.print(len);
      Serial.print("]: ");
      Serial.println((char*)buf);
      display("Received: ");
      Serial.print("RSSI: ");
      Serial.println(rf69.lastRssi(), DEC);

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

void Blink(byte pin, byte delay_ms, byte loops) {
  while (loops--) {
    digitalWrite(pin, HIGH);
    delay(delay_ms);
    digitalWrite(pin, LOW);
    delay(delay_ms);
  }
}
