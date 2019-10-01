#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#define DHT_PIN 15
#define DHT_TYPE DHT11
#define LED_BUILTIN 2

DHT dht (DHT_PIN, DHT_TYPE);
float humidity;
float temperature;
float fahrenheit;

int value;
char str_val1[25], str_val2[25], str_val3[25];

const char *SSID = "DIGI-X_LOUNGE";
const char *PASSWORD = "IT Certified";

const char* mqttServer= "soldier.cloudmqtt.com";
const int mqttPort = 12463;
const char* mqttUser = "kaprvxoy";
const char* mqttPassword = "Ljsv4TpMOYWn";

WiFiClient espClient;
PubSubClient client(espClient);

void connectToMqttCloud() {
  client.setServer(mqttServer, mqttPort);
  while ( !client.connected() ) {
    Serial.println("Mencoba koneksi dengan Broker MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("tersambung dengan MQTT ");
    } else {
      Serial.print("Error ");
      delay(5000); // coba 5 detik kemudian
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.disconnect(true);
  delay(2000);
  dht.begin();
  connectToHotSpot();
}

void loop() {
  // put your main code here, to run repeatedly:
  humidity=dht.readHumidity();
  temperature = dht.readTemperature();
  fahrenheit = dht.readTemperature(true);
  if(isnan(humidity) || isnan(temperature) || isnan(fahrenheit)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  connectToMqttCloud();
  sprintf(str_val1, "%f", humidity);
  client.publish("INIX", str_val1);
  delay(5000);
}

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
