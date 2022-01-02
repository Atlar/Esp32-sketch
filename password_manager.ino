String text_display;

bool check_password( const char* password ){

  if( doc["password"] == password ){
  
    return true;
    
  }else{
    
    return false;
    
  }
  
}

void reset_input(){
  text_display = String();
}
void add_input(const char key){
  text_display += String(key);
}
String get_input(){
  return text_display;
}
