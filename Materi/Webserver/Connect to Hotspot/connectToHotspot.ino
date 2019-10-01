
#include <WiFi.h>
const char *SSID = "inixindo";
const char *PASSWORD = "270755";

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.disconnect(true);
  connectToHotSpot();
}
void connectToHotSpot() {

  WiFi.begin( SSID, PASSWORD );
  Serial.print("Trying to establish connection to WiFi Router");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  // nothing here
}
