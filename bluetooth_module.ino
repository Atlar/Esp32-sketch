void setup_bluetooth( BluetoothSerial* SerialBT ){

  //Bluetooth
  if (!SerialBT->begin("ESP32")) {
    Serial.println("An error occurred initializing Bluetooth");
  } else {
    Serial.println("Bluetooth initialized");
  }
  
}
void loop_bluetooth( BluetoothSerial* SerialBT ){

  //BT
  while (SerialBT->available()) {
    Serial.write(SerialBT->read());
  }

  delay(50);
  
}
void return_settings( BluetoothSerial* SerialBT ){

  //BT
  while (SerialBT->available()) {
    Serial.write(SerialBT->read());
    serializeJson(doc, Serial);
  }

  delay(50);
  
}

void process_command( JsonObjectConst command_doc ){

   if( command_doc["command"] == "change_settings" ){
      
      merge( doc.as<JsonObject>() , command_doc["settings"].as<JsonObjectConst>());
      
   }
   if( command_doc["command"] == "save_settings" ){
      save_settings();
   }

}
void process_incoming(){

  while (SerialBT.available()) {
    auto BT_income = SerialBT.read();
    //process_command();
  }
  delay(50);
}
