#include <Wire.h>
const unsigned char relay[] = {0x01, 0x02, 0x03, 0x04};
void setup() {
  Wire.begin();
}

void loop() {
  for (int i = 0; i < 4; i++) {
    Wire.beginTransmission(16);
    Wire.write(relay[i]);
    Wire.write(0xff);
    Wire.endTransmission();
    delay(200);
  }
  delay(500);
  for (int i = 0; i < 4; i++) {
    Wire.beginTransmission(16);
    Wire.write(relay[i]);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(200);
  }
  delay(500);
}
