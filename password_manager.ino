bool check_password( const char* password ){

  if( doc["password"] == password ){
  
    return true;
    
  }else{
    
    return false;
    
  }
  
}
