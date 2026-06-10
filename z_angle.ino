#include <Wire.h>
#define BUTTON_PIN 19
const int servo_pin = 13;
const int MPU = 0x68;

float gyroZoffset = 0;
float angleZ = 0;
int lastState;
int currentState=LOW;
unsigned long lastTime;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  delay(1000);

  // Calibrate gyro Z offset
  long sum = 0;
  for (int i = 0; i < 1000; i++) {
    int16_t gz = readGyroZRaw();
    sum += gz;
    delay(2);
  }

  gyroZoffset = sum / 1000.0;

  lastTime = micros();
}

void loop() {
   

  static float prevGyroZ = 0;
  unsigned long now = micros();
  float dt = (now - lastTime) / 1000000.0;
  lastTime = now;

  int16_t gyroZraw = readGyroZRaw();

  // MPU6050 default gyro range is ±250 deg/s
  // sensitivity = 131 LSB per deg/s
  float gyroZ = (gyroZraw - gyroZoffset) / 131.0;

  if(abs(gyroZ)<0.5) gyroZ=0;
  angleZ += (gyroZ + prevGyroZ) * 0.5 * dt;
  prevGyroZ = gyroZ;
 
  // Keep angle between 0 and 360
  if (angleZ >= 360) angleZ -= 360;
  if (angleZ < 0) angleZ += 360;
  if(angleZ>180) angleZ -= 360;

  Serial.print("Gyro Z deg/s: ");

  currentState = digitalRead(BUTTON_PIN);
  if(lastState == LOW && currentState == HIGH)
      angleZ = 0;
  lastState = currentState;

  Serial.print(gyroZ);
  Serial.print(" | Angle Z: ");
  Serial.println(angleZ);

  delay(10);
 

}

int16_t readGyroZRaw() {
  Wire.beginTransmission(MPU);
  Wire.write(0x47); // Gyro Z high byte register
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 2, true);

  int16_t gz = Wire.read() << 8 | Wire.read();
  return gz;
}