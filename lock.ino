#define LOCK_PIN 34

void open_lock(){

  //digitalWrite(LED,HIGH);
  //open lock
  digitalWrite( LOCK_PIN, HIGH );
  delay( atoi( doc["unlock_duration"] ) ); //500 sec
  digitalWrite( LOCK_PIN, LOW );
  //digitalWrite(LED,LOW);
  
}
