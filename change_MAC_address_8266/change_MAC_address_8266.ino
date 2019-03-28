/*
 * Circuits4you.com
 * Change MAC Address of ESP8266 in Arduino IDE
*/
#include <ESP8266WiFi.h>
 
//Call to ESpressif SDK
extern "C" {
  #include <user_interface.h>
}
 
  const char* wifiName = "cu-manual";
  const char* wifiPass = "janaswah8h#ku*rej$n5";
  
  uint8_t mac[6] {0xDE, 0x4F, 0x22, 0x84, 0x4F, 0x3D};    //MAC Address you want to set
  //DE:4F:22:84:4F:3D
 
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  
  Serial.print("OLD ESP8266 MAC: ");
  Serial.println(WiFi.macAddress()); //This will read MAC Address of ESP
  
  
  wifi_set_macaddr(0, const_cast<uint8*>(mac));   //This line changes MAC adderss of ESP8266
 
  Serial.print("NEW ESP8266 MAC: ");
  Serial.println(WiFi.macAddress()); //This will read MAC Address of ESP
  
  Serial.print("Connecting to ");
  Serial.println(wifiName);
 
  WiFi.begin(wifiName, wifiPass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //You can get IP address assigned to ESP
}
 
// the loop function runs over and over again forever
void loop() {
}
