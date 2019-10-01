#define BT_MERAH 13                                                                        
#define BT_KUNING 27
#define BT_HIJAU 32
#define SU_MERAH 2
#define SU_KUNING 4
#define SU_HIJAU 18

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Traffic Light");
  pinMode(BT_MERAH, OUTPUT);
  pinMode(BT_KUNING, OUTPUT);
  pinMode(BT_HIJAU, OUTPUT);
  
  pinMode(SU_MERAH, OUTPUT);
  pinMode(SU_KUNING, OUTPUT);
  pinMode(SU_HIJAU, OUTPUT);
}

void loop() {
  digitalWrite(BT_MERAH, HIGH);
  digitalWrite(SU_HIJAU, HIGH);
  delay(3000);
  digitalWrite(SU_HIJAU, LOW);
  digitalWrite(SU_KUNING, HIGH);
  delay(1000);
  digitalWrite(BT_MERAH, LOW);
  digitalWrite(BT_HIJAU, HIGH);
  digitalWrite(SU_KUNING, LOW);
  digitalWrite(SU_MERAH, HIGH);
  delay(5000);
  digitalWrite(BT_HIJAU, LOW);
  digitalWrite(BT_KUNING, HIGH);
  delay(1000);
  digitalWrite(BT_KUNING, LOW);
  digitalWrite(SU_MERAH, LOW);
}
