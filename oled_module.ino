void setup_oled(){

  
  
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
