#define MERAH 13                                                                        
#define KUNING 27
#define HIJAU 32

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Traffic Light");
  pinMode(MERAH, OUTPUT);
  pinMode(KUNING, OUTPUT);
  pinMode(HIJAU, OUTPUT);
}

void activateLed(int which, int how_long) {
  digitalWrite(which, HIGH);
  delay(how_long);
  digitalWrite(which, LOW);
}

void loop() {
  activateLed(MERAH, 5000);
  activateLed(KUNING, 3000);
  activateLed(HIJAU, 6000);
}
