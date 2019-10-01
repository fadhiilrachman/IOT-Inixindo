#include <WiFi.h>
#include <DHT.h>
#define DHT_PIN 15
#define DHT_TYPE DHT11
#define PORT 8080
#define LED_BUILTIN 2
const char *SSID = "DIGI-X_LOUNGE";
const char *PASSWORD = "IT Certified";

DHT dht (DHT_PIN, DHT_TYPE);
float humidity;
float temperature;
float fahrenheit;

String header="HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
String tailer="</body><html>";
WiFiServer server(PORT);
WiFiClient client;

long randomnumber;

String s;
String cmd;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(SSID, PASSWORD);
  while(WiFi.status()!=WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.print("Web server active: ");
  Serial.println( WiFi.localIP() );
  server.begin();
  dht.begin();
  randomSeed(42);
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
  Serial.printf("\nKelembaban: %f", humidity);
  Serial.printf("\nCelcius: %f", temperature);
  Serial.printf("\nFahrenheit: %f", fahrenheit);
  client=server.available();
  if(client) {
    //Serial.println("got a new client");
    while(client.connected() ) {
      if(client.available()) {
        s=client.readString();
        cmd=getCommand(s);
        if(cmd.equals("")) {
          refresh();
        } else {
          refresh();
          client.stop();
        }
        //Serial.println(cmd);
        delay(100);
      } else {
        client.stop();
      }
    }
  }
  delay(1000);
}

void refresh() {
  client.println(header);
  client.print("<html><head><title>Sensor</title>");
  client.print("<meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\">");
  client.print("</head>");
  client.print("<body><h1>Data Sensor DHT</h1>");
  client.print("<p>Nilai Data dari sensor DHT adalah:");
  client.print("<p>Kelembaban: ");
  client.print(humidity);
  client.print("<br>Celcius: ");
  client.print(temperature);
  client.print("C<br>Fahrenheit: ");
  client.print(fahrenheit);
  client.print("F</p>");
  client.println();
  client.print("<p><form action=\"/?\"><input type=\"submit\" value=\"Refresh\"></form></p>");
  client.println(tailer);
}

String getCommand(String s) {
  int i;
  i=s.indexOf(' ',5);
  return (s.substring(5,i));
}
