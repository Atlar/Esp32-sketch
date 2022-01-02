#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pin_rows[ROW_NUM] = {12, 14, 27, 26 }; // GIOP18, GIOP5, GIOP17, GIOP16 connect to the row pins NEW GIOP21, GIOP19, GIOP18, GIOP05 connect to the row pins
byte pin_column[COLUMN_NUM] = {25, 33, 32};  // GIOP4, GIOP0, GIOP2 connect to the column pins NEW GIOP17, GIOP16, GIOP04 connect to the column pins

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void tick_keypad(){

  char key = keypad.getKey();
  if (key){
    if( key == '*' ){
      //text_display = String();
      //testscrolltext( text_display );
      //pass = false;
      reset_input();
    }else if( key ){
      if( key=='9'){
        open_lock();  
      }
      add_input(key);
      //text_display += String(key);
      //compare returns 0 if equal
      //pass = !text_display.compareTo( "1234" );
      //testscrolltext( text_display );
      if( get_input().length() == 4 ){
        manage_password_check( get_input() );
      }
      // too big password
      if ( get_input().length() > 4 ){
        //text_display = String();
        //testscrolltext( text_display );
        //pass = false;
        reset_input();
      }
    }else{
      reset_input();
    }
    Serial.println(key);
    displaytext( get_input() );
  }
  
}
