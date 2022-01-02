#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void setup_oled(){
  
  //OLED
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    //for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  
}
void displaytext( String text_display ) {
  display.clearDisplay();
  display.setTextSize(3); // Draw 10X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(text_display);
  display.display();      // Show initial text
  delay(100);
   
}
