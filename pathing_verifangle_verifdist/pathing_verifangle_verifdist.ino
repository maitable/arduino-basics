#include <Wire.h>
#include <ESP32Encoder.h>

ESP32Encoder encoder;

#define BUTTON_PIN 19
const int MPU = 0x68;

float gyroZoffset = 0;
float angleZ = 0;
int lastState;
int currentState=LOW;
unsigned long lastTime;

double pi = 2*acos(0.0);

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

  setupEncoder();

}

void loop() {
  // put your main code here, to run repeatedly:
  float ticks = getEncoderCount();
  //Serial.println("Encoder count = " + String(ticks));
  float dist = get_distance(ticks);

  float target_angle = get_angle(50, 60);
  float target_hyp = get_hyp(50, 60);

  float angle = updateAngleZ();

  currentState = digitalRead(BUTTON_PIN);
  if (lastState == LOW && currentState == HIGH)
    angleZ = 0;
  lastState = currentState;

  float angle_rad = angle * pi / 180;  // doar local, angleZ rămâne în grade

  //serial.print("Angle Z (deg): ");
  //Serial.print(angle);
  //Serial.print(" | rad: ");
  //Serial.println(angle_rad);

  if(abs(target_angle-angle_rad) <= 0.1) Serial.println("Target ANGLE found");
  if(abs(target_hyp-dist)<=25) Serial.println("Target DISTANCE found");
  Serial.println("Distance(mm)= " + String(dist) + " Angle(rad)= " + angle_rad);
  delay(10);
}

float get_angle(float x, float y){
  float z = sqrt(pow(x, 2) + pow(y, 2));
  float angle_rad = asin(y / z) ;
  float angle_degr = angle_rad * 180/pi;
  return angle_rad;
}

float get_hyp(float x, float y){
  float z = sqrt(pow(x, 2) + pow(y, 2));
  return z;
} 

int16_t readGyroZRaw() {
  Wire.beginTransmission(MPU);
  Wire.write(0x47); // Gyro Z high byte register
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 2, true);

  int16_t gz = Wire.read() << 8 | Wire.read();
  return gz;
}

float updateAngleZ() {
  static float prevGyroZ = 0;
  unsigned long now = micros();
  float dt = (now - lastTime) / 1000000.0;
  lastTime = now;

  int16_t gyroZraw = readGyroZRaw();
  float gyroZ = (gyroZraw - gyroZoffset) / 131.0;
  if (abs(gyroZ) < 0.5) gyroZ = 0;

  angleZ += (gyroZ + prevGyroZ) * 0.5 * dt;
  prevGyroZ = gyroZ;

  if (angleZ >= 180) angleZ -= 360;
  if (angleZ < -180) angleZ += 360;

  return angleZ;
}


void setupEncoder() {
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  encoder.attachHalfQuad(16,17);
  encoder.clearCount();
}

int32_t getEncoderCount() {
  return (int32_t)encoder.getCount();
}

float get_distance(float ticks){
  float circumferinta = 47*pi; //mm mama mama
  float dist = (ticks / 100) * circumferinta;
  return dist;
}