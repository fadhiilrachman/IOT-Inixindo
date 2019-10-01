#define trigPin 19
#define echoPin 22

#define BT_MERAH 13
#define BT_KUNING 12
#define BT_HIJAU 14
#define SU_MERAH 27
#define SU_KUNING 26
#define SU_HIJAU 25

float duration, distance, jarak;

float cek_sensor(int out, int in) {
  digitalWrite(out, LOW);
  delayMicroseconds(2);
  digitalWrite(out, HIGH);
  delayMicroseconds(10);
  digitalWrite(out, LOW);
  duration = pulseIn(in, HIGH);
  distance = (duration/29)/2;
  Serial.print("Jarak:");
  Serial.print(distance);
  Serial.print(" cm\n");
  return distance;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(BT_MERAH, OUTPUT);
  pinMode(BT_KUNING, OUTPUT);
  pinMode(BT_HIJAU, OUTPUT);
  
  pinMode(SU_MERAH, OUTPUT);
  pinMode(SU_KUNING, OUTPUT);
  pinMode(SU_HIJAU, OUTPUT);
  
  Serial.begin(115200);
}

void SU_active() {
  digitalWrite(BT_HIJAU, LOW);
  digitalWrite(BT_KUNING, HIGH);
  delay(1000);
  digitalWrite(BT_KUNING, LOW);
  digitalWrite(BT_MERAH, HIGH);
  digitalWrite(SU_MERAH, LOW);
  digitalWrite(SU_HIJAU, HIGH);
  delay(3000);
  digitalWrite(SU_HIJAU, LOW);
  digitalWrite(SU_KUNING, HIGH);
  delay(1000);
  digitalWrite(SU_KUNING, LOW);
  digitalWrite(SU_MERAH, HIGH);
  digitalWrite(BT_MERAH, LOW);
  digitalWrite(BT_HIJAU, HIGH);
}

void loop() {
  digitalWrite(BT_HIJAU, HIGH);
  digitalWrite(SU_MERAH, HIGH);
  // BT sesi 1
  Serial.print("BT sesi 1\n");
  delay(3000);
  jarak = cek_sensor(trigPin, echoPin);
  if((jarak >= 5) && (jarak <= 20)) {
    SU_active();
    return;
  }
  // BT sesi 2
  Serial.print("BT sesi 2\n");
  delay(3000);
  jarak = cek_sensor(trigPin, echoPin);
  if((jarak >= 5) && (jarak <= 20)) {
    SU_active();
    return;
  }
  // BT sesi 3
  Serial.print("BT sesi 3\n");
  delay(3000);
  jarak = cek_sensor(trigPin, echoPin);
  if((jarak >= 5) && (jarak <= 20)) {
    SU_active();
    return;
  }
  // BT sesi 4
  Serial.print("BT sesi 4\n");
  delay(3000);
  SU_active();
}
