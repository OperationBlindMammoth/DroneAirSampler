//////// TFT Display ///////////////////////
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
  #define TFT_CS        0   // Originally PIN 10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         5 // Oringially PIN 6
  #define TFT_MOSI 11  // Data out
#define TFT_SCLK 13  // Clock out
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
/////////////////////////////////////////////


const int chipSelect = 4;  // SD

#include <SPI.h>  // SD
#include <SD.h>  // SD

//////// Radio ///////////////////////
#include <RH_RF69.h>
#define RF69_FREQ 915.0
#define RFM69_CS      10   // "B"
#define RFM69_RST     11   // "A"
#define RFM69_IRQ     6    // "D"
#define RFM69_IRQN    digitalPinToInterrupt(RFM69_IRQ )
#define LED 13
/////////////////////////////////////////////

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_IRQ);
int16_t packetnum = 0;

/*
  If the pin is configured as an INPUT, writing a HIGH value with digitalWrite() will enable 
  an internal 20K pullup resistor (see the tutorial on digital pins). Writing LOW will disable 
  the pullup. 
*/
int pushButton = 12;

void setup() {
    Serial.begin(115200);
  while(!Serial) delay(10);

    Serial.println();
  Serial.println("/////////////////////////////////////////");
  Serial.println("          BASESTATION");

  Serial.println("Serial is Go");
  pinMode(pushButton,INPUT);
  digitalWrite(pushButton,HIGH);  // This enables the built-in pull-up resistor. Therefore, button-push = 0
  pinMode(LED_BUILTIN, OUTPUT);

  ////// TFT DISPLAY SETUP
  Serial.print(F("Initializing TFT Display..."));
  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
  Serial.println(F("TFT Display is Go"));
  tft.fillScreen(ST77XX_BLACK);
  tft.println("hello");

  ////// RADIO SETUP
  pinMode(LED,OUTPUT);
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);
   Serial.println("Feather RFM69 RX Test!");
  Serial.println();
    // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);
    if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    //while (1);
  }
  Serial.println("Radio is Go");
    if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
    }

     rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);

  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
  



}


//000000000000000000000000000000000000000000000000000000000000000000000000
void loop() {
  int reading = 1- digitalRead(pushButton);
  digitalWrite(LED_BUILTIN,reading);
  debounce(reading);
 // mobilemonitor();
}
//000000000000000000000000000000000000000000000000000000000000000000000000






const int debounceDelay = 1500;    /// How long of a button press should trigger the grab?
int lastButtonState = 0;
int buttonState = 0;

unsigned long lastDebounceTime = 0;

void debounce(int reading){
  //Serial.println(reading);
//display(" // Debounce // ");
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Reset the debounce timer
  }

  if ((millis() - lastDebounceTime) >= debounceDelay) {
    // If the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

// If the button is pressed:
      if (buttonState == HIGH) {
        Serial.println("Button pressed");
        String buttonmessage = "Button pressed";
        //display(buttonmessage);
        grabSample();
        lastDebounceTime = millis();
        lastButtonState = 0;
        buttonState = 0;
      }
    }
  }

  lastButtonState = reading; // Store the current button state
}