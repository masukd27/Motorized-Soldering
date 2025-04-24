#include <Wire.h>
#include <Adafruit_MLX90640.h>

Adafruit_MLX90640 mlx;
float frame[32 * 24];
const float threshold = 100.0;  // ปรับให้อ่านเห็นผลก่อน
bool alreadyTriggered = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  while (!Serial && millis() < 5000);  // ไม่รอตลอดกาล

  Wire.begin();
  Wire.setClock(1000000);

  if (!mlx.begin()) {
    Serial.println("MLX90640 not found!");
    while (1);
  }

  mlx.setMode(MLX90640_CHESS);
  mlx.setResolution(MLX90640_ADC_16BIT);
  mlx.setRefreshRate(MLX90640_4_HZ);
}

void loop() {
  if (mlx.getFrame(frame) != 0) {
    Serial.println("getFrame failed");
    return;
  }

  float maxTemp = -999;
  String dataLine = "";

  for (int i = 0; i < 768; i++) {
    if (frame[i] > maxTemp) maxTemp = frame[i];
    dataLine += String(frame[i], 2);
    if (i < 767) dataLine += ",";
  }
  
  Serial.println(dataLine);  // ส่ง frame 768 ค่า

  Serial.print("Max Temp: ");
  Serial.println(maxTemp);

  if (!alreadyTriggered && maxTemp > threshold) {
    Serial.println("ON");
    alreadyTriggered = true;
  }

  delay(250);
}
