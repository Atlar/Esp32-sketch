
#define EEPROM_SIZE 8
#define PASSWORD_ADDRESS 0
#define PASSWORD_SIZE 4
#define MASTER_PASSWORD_ADDRESS 4
#define MASTER_PASSWORD_SIZE 4

#define ACCEPT_NFC_SETTINGS_ADDRESS 9

#define LOCK_DURATION_SETTINGS_ADDRESS 10
#define LOCK_DURATION_SETTINGS_SIZE 4

#define WRITE_INITIAL_SETTINGS 0

char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";


void settings_setup()
{
  
  doc["password"] = "00000";
  doc["master_password"] = "00000";
  //const char* password = doc["password"];
  //const char* master_password = doc["master_password"];
  doc["accept_NFC"] = 1;
  doc["unlock_duration"] = 700;
  
  if(WRITE_INITIAL_SETTINGS){
    
      save_settings();
    
  }

}


void load_settings(){
  // initialize EEPROM with predefined size
  EEPROM.begin(EEPROM_SIZE);
  char password[5];
  char master_password[5];
  
  read_string( PASSWORD_ADDRESS,PASSWORD_SIZE, password);
  read_string( MASTER_PASSWORD_ADDRESS, MASTER_PASSWORD_SIZE, master_password);

  byte readValue = EEPROM.read(ACCEPT_NFC_SETTINGS_ADDRESS);

  char lock_duration[4];
  read_string( LOCK_DURATION_SETTINGS_ADDRESS, LOCK_DURATION_SETTINGS_SIZE, lock_duration);
  
  doc["password"] = password;
  doc["master_password"] = master_password;
  doc["accept_NFC"] = readValue;
  doc["unlock_duration"] = lock_duration;
  
}


void read_string( int address, int size_string, char* string_buffer ){

    number_n = 0;
    for (int i = 0; i < size_string; i++) {
        byte readValue = EEPROM.read(i + address);

        if (readValue == 0) {
            break;
        }

        string_buffer[i] = char(readValue);
        number_n += 1;
        
    }
    //mark the end of a char array
    string_buffer[size_string]='\0';
    Serial.write("read data: ");
    Serial.write(string_buffer);
    Serial.write(" read: ");
    char cstr[16];
    itoa(number_n, cstr, 10);
    Serial.write( cstr );
    
    
}


void write_string( int address, int size_string, const char* string_write ){


    for (int i = 0; i < size_string; i++) {
        EEPROM.write( address + i, byte( string_write[i] ) );       
    }

}
void merge(JsonObject dest, JsonObjectConst src)
{
   for (auto kvp : src)
   {
     auto setting_name = kvp.key();
     
     if (setting_name == "password"){
              Serial.write("change password settings");
              dest[ kvp.key() ] = kvp.value();
              //serializeJson(dest, Serial);
     }
   }
}

void save_settings()
{
    EEPROM.begin(9);
    Serial.write("FLASH writing initial settings");
    
    write_string( PASSWORD_ADDRESS, PASSWORD_SIZE, doc["password"] );
    write_string( MASTER_PASSWORD_ADDRESS, MASTER_PASSWORD_SIZE, doc["master_password"] );
    EEPROM.write( ACCEPT_NFC_SETTINGS_ADDRESS, doc["accept_NFC"] );
    
    EEPROM.commit();
}
