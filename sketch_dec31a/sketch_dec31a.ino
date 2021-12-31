#include <ArduinoJson.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  StaticJsonDocument<200> doc;
  doc["bt_name"] = "Esp32";
  doc["password"] = "1234";
  delay(1000);
  StaticJsonDocument<200> change;
  change["password"] = "1222";
  merge( doc.as<JsonObject>(), change.as<JsonObjectConst>() );
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
void merge(JsonObject dest, JsonObjectConst src)
{
   for (auto kvp : src)
   {
     auto setting_name = kvp.key();
     
     if (setting_name == "password"){
              Serial.write("change password settings");
              dest[ kvp.key() ] = kvp.value();
              serializeJson(dest, Serial);
     }
   }
}
