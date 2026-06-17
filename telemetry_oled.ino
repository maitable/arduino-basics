#include <Wire.h>
#include <ESP32Encoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

ESP32Encoder encoder;

const int MPU = 0x68;

float gyroZoffset = 0;
float angleZ = 0;
unsigned long lastTime;

double pi = 2 * acos(0.0);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // OLED
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(1);
  oled.setCursor(0, 0);
  oled.println("Initializing...");
  oled.display();

  // MPU6050 Wake-up
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  delay(1000);

  // Gyro calibration
  long sum = 0;
  for (int i = 0; i < 1000; i++) {
    sum += readGyroZRaw();
    delay(2);
  }

  gyroZoffset = sum / 1000.0;

  setupEncoder();

  lastTime = micros();

  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println("Ready!");
  oled.display();
  delay(500);
}

void loop() {

  float ticks = getEncoderCount();
  float dist = get_distance(ticks);

  float target_angle = get_angle(300, 400);
  float target_hyp = get_hyp(300, 400);

  float angle_deg = updateAngleZ();
  float angle_rad = angle_deg * pi / 180.0;

  bool angleFound = abs(target_angle - angle_rad) <= 0.1;
  bool distFound = abs(target_hyp - dist) <= 25;

  oled.clearDisplay();

  oled.setTextSize(1);

  oled.setCursor(0, 0);
  oled.print("Dist:");
  oled.print(dist, 1);
  oled.print(" mm");

  oled.setCursor(0, 16);
  oled.print("Angle:");
  oled.print(angle_rad, 2);
  oled.print(" rad");

  oled.setCursor(0, 32);
  oled.print("T.Ang:");
  oled.print(target_angle, 2);

  oled.setCursor(0, 42);
  oled.print("T.Dst:");
  oled.print(target_hyp, 0);

  oled.setCursor(0, 54);

  if (angleFound)
    oled.print("ANGLE OK ");

  if (distFound)
    oled.print("DIST OK");

  oled.display();

  delay(10);
}

float get_angle(float x, float y) {
  float z = sqrt(x * x + y * y);
  return asin(y / z);
}

float get_hyp(float x, float y) {
  return sqrt(x * x + y * y);
}

int16_t readGyroZRaw() {
  Wire.beginTransmission(MPU);
  Wire.write(0x47);
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

  if (abs(gyroZ) < 0.5)
    gyroZ = 0;

  angleZ += (gyroZ + prevGyroZ) * 0.5 * dt;

  prevGyroZ = gyroZ;

  if (angleZ >= 180)
    angleZ -= 360;

  if (angleZ < -180)
    angleZ += 360;

  return angleZ;
}

void setupEncoder() {
  ESP32Encoder::useInternalWeakPullResistors = puType::up;

  // Encoder A = GPIO18
  // Encoder B = GPIO19
  encoder.attachHalfQuad(19, 18);

  encoder.clearCount();
}

int32_t getEncoderCount() {
  return encoder.getCount();
}

float get_distance(float ticks) {

  float circumferinta = 47 * pi;  // mm

  return (ticks / 100.0) * circumferinta;
}
