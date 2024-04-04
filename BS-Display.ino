void display(String text){
  //tft.fillScreen(ST77XX_BLACK);
  tft.print(text);
}

//// MIRRORS THE SERIAL OUTPUT TO THE TFT DISPLAY
// void mobilemonitor(){
//   if (Serial.available()){
//     char ch = Serial.read();
//     tft.print(ch);
//   }
// }