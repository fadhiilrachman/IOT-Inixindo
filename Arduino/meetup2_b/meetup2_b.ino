#include <DHT.h>
#define DHT_PIN 2
#define DHT_TYPE DHT11
DHT dht (DHT_PIN, DHT_TYPE);
float humidity;
float temperature;
float fahrenheit;
int i;
int j;

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("DHT11 START!");
  delay(3000);
  dht.begin();
  header();
  delay(1000);
}

void header() {
  Serial.println("\nKelembaban \tTemperatur \t Temperatur");
  Serial.println(" % \t\t Celcius \t Fahrenheit");
}

char cetak_suhu(float h, float t, float f) {
  delay(3000);
  float human = dht.readHumidity();
  float tempera = dht.readTemperature();
  float fahren = dht.readTemperature(true);
  if( (h == human) && (t == tempera) && (f == fahren) ){
    if( i<=20 ) {
      Serial.print(".");
    }
    ++i;
  } else {
    i=0;
    ++j;
    if(j<6) {
      Serial.println();
      Serial.print(human);
      Serial.print("\t\t");
      Serial.print(tempera);
      Serial.print("\t\t");
      Serial.print(fahren);
      Serial.println();
    } else {
      header();
      Serial.println();
      Serial.print(human);
      Serial.print("\t\t");
      Serial.print(tempera);
      Serial.print("\t\t");
      Serial.print(fahren);
      Serial.println();
      j=0;
    }
  }
}

void loop() {
  humidity=dht.readHumidity();
  temperature = dht.readTemperature();
  fahrenheit = dht.readTemperature(true);
  if(isnan(humidity) || isnan(temperature) || isnan(fahrenheit)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  delay(3000);
  cetak_suhu(humidity, temperature, fahrenheit);
  delay(5000);
}
