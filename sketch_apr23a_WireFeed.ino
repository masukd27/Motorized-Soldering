bool alreadyTriggered = false;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);         // relay NO, HIGH = ปิด, LOW = เปิด
  digitalWrite(3, HIGH);      // เริ่มต้นปิดไว้
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (!alreadyTriggered && cmd == "ON") {
      digitalWrite(3, LOW);       // เปิดจ่ายลวด
      delay(80);                  // แค่ 50 มิลลิวินาที
      digitalWrite(3, HIGH);      // ปิดจ่ายลวด
      alreadyTriggered = true;    // ไม่ให้ทำซ้ำอีก
    }
  }
}
