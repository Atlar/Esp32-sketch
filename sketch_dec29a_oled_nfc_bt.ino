//Time
//#include <time.h>
#include <SPI.h>
#include <Wire.h> //iic interface
#define DEBUG_SERIAL 1
#define PN532DEBUG
//NFC
#include <Adafruit_PN532.h>
//#define PN532_SCK (16) //GPIO16 = Rx2 on esp32
//#define PN532_MISO (04) //GPIO4 = D4 on esp32
//#define PN532_MOSI (02) //GRPIO2 = D2 on esp32
//#define PN532_SS (15) //GPIO15 = D15 on esp32
//Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
//from https://habr.com/ru/post/543446/
//GPIO18 - SKC
//GPIO19 - MSO
//GPIO23 - MOSI
//GPIO5 - SS
#define PN532_SCK  (18)
#define PN532_MOSI (23)
#define PN532_SS   (05)
#define PN532_MISO (19)
//Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
//Adafruit_PN532 nfc( PN532_SS );//D5 chip select
//I2C
#define PN532_IRQ (19)//GPIO01
#define PN532_RST (18)

const int DELAY_BETWEEN_CARDS = 500;
long timeLastCardRead = 0;
boolean readerDisabled = false;
int irqCurr;
int irqPrev;

Adafruit_PN532 nfc(PN532_IRQ, PN532_RST);

//#include <PN532_SPI.h>
//PN532_SPI nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS );
//Small OLED

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define fontX 7
#define fontY 12
#define gfxWidth 128
#define gfxHeight 32

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//
//test logic
int i = 0;
char time_string[20];

//Bluetooth
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

//settings
#include <ArduinoJson.h>
StaticJsonDocument<256> doc;

//Flash
// include library to read and write from flash memory
#include <EEPROM.h>

int number_n = 0;

void setup() {
  

  
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(100);
  //SPI.begin();
  SPI.begin();
  
  //settings
  settings_setup();
  
  setup_NFC();
  
  load_settings();
  
  //OLED initialization
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Wire.begin();
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  
  // Clear the buffer
  display.clearDisplay();

  //bluetooth
  setup_bluetooth(&SerialBT);

  
}

void loop() {
  
  return_settings(&SerialBT);
  NFC_loop();  
  tick_keypad();
}

void manage_password_check( String try_password){
  char buffer_password[4];
  try_password.toCharArray(buffer_password, 4 );
  if( check_password( buffer_password ) ){
     open_lock();
     Serial.write("Open");
  }else{
     Serial.write("Wrong password");  
  }
  reset_input();

}
