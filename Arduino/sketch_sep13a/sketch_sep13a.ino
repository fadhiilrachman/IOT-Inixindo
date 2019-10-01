#include <WiFi.h>
const char *SSID = "DIGI-X_LOUNGE";
const char *PASSWORD = "IT Certified";

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.disconnect(true);
  connectToHotSpot();
}

void connectToHotSpot() {

  WiFi.begin(SSID, PASSWORD);
  Serial.print("Trying to establish connection to WiFi router");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected! IP: ");
  Serial.println(WiFi.localIP());

  Serial.println();
  Serial.println("Mac Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  // nothing
}
