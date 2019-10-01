#include <WiFi.h>
#include <PubSubClient.h>
#define BUILTIN_LED 2

WiFiClient espClient;
PubSubClient client(espClient);

const char *SSID = "DIGI-X_LOUNGE";
const char *PASSWORD = "IT Certified";

const char* mqttServer= "soldier.cloudmqtt.com";
const int mqttPort = 12463;
const char* mqttUser = "kaprvxoy";
const char* mqttPassword = "Ljsv4TpMOYWn";

void connectToHotSpot() {
  WiFi.begin( SSID, PASSWORD );
  Serial.print("Trying to establish connection to WiFi Router");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected! IP: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  delay(1000);
  WiFi.disconnect(true);
  delay(2000);
  connectToHotSpot();
  connectToMqttCloud();
//  toBlink(5);
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
  if (! client.connected() ) {
  Serial.println("Disconnected ...Pls reconnect");
  // we need to write some code to reconnect here
  }
}

void connectToMqttCloud() {
  char* topic = "INIX";
  client.setServer(mqttServer, mqttPort);
  client.setCallback(receiveMessage);
  while ( !client.connected() ) {
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("MQTT Successfull Connected");
      client.subscribe(topic);
    } else {
      Serial.println("Still Try..");
      delay(5000); // coba 5 detik lagi
    }
  }
}

void receiveMessage(char* topic, byte* payload, unsigned int length) {
  int ntimes;
  // hanya tertarik pada byte pertama saja --> payload [0]
  //konversi bytes menjadi integer
  ntimes = (int) ( (char)payload[0] - '0'); // input harus karakter '0' sd '9'
  toBlink(ntimes);
 }

void toBlink(int n) { // blink sebanyak n kali .....
  if (n<0 || n> 9) n= 1; // jika nilai input kacau, maka jadikan n=1
  for (int i=0; i<n; i++) {
    digitalWrite(BUILTIN_LED, HIGH);
    delay(500);
    digitalWrite(BUILTIN_LED, LOW);
    delay(500);
  }
}
