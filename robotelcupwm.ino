#include <Wire.h>
#include <ESP32Encoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

ESP32Encoder encoder_lung;
ESP32Encoder encoder_lat;

const uint8_t MPU = 0x68;
float gyroZoffset = 0;
float angleZ = 0;
unsigned long lastTime;
double pi = 2 * acos(0.0);

int motor1Pin1 = 27;
int motor1Pin2 = 26;
int enable1Pin = 14;

int motor2Pin1 = 25;
int motor2Pin2 = 33;
int enable2Pin = 32;

const int freq = 30000;
const int pwmChannel = 0;
const int pwmChannel2 = 1;
const int resolution = 8;

#define MAX_SPEED 255
int vitezaBaza = 255;

const int makerlinepin = 35;

int adcMakerLine = 0;
int adcSetPoint = 0;
int proportional = 0;
int lastProportional = 0;
int derivative = 0;
int powerDifference = 0;
int motorLeft = 0;
int motorRight = 0;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const int interval = 10;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(1);
  oled.setCursor(0, 0);
  oled.println("Initializing...");
  oled.display();

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel);

  ledcSetup(pwmChannel2, freq, resolution);
  ledcAttachPin(enable2Pin, pwmChannel2);

  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  delay(1000);

  long sum = 0;
  for (int i = 0; i < 1000; i++) {
    sum += readGyroZRaw();
    delay(2);
  }
  gyroZoffset = sum / 1000.0;

  setupEncoder();

  lastTime = micros();

  pinMode(makerlinepin, INPUT);
  
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println("Ready!");
  oled.display();

  adcSetPoint = analogRead(makerlinepin);
  delay(2000);
}

void loop() {
  float ticks_lung = getEncoderCount(encoder_lung);
  float dist_lung = get_distance(ticks_lung);
  float ticks_lat = getEncoderCount(encoder_lat);
  float dist_lat = get_distance(ticks_lat);

  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    
    adcMakerLine = analogRead(makerlinepin);
    
    if (adcMakerLine < 200) { 
      robotMove(0, 0);
    }
    else if (adcMakerLine > 3800) { 
      robotMove(MAX_SPEED - 25, MAX_SPEED - 25);
    }
    else {
      proportional = adcMakerLine - adcSetPoint;
      derivative = proportional - lastProportional;
      lastProportional = proportional;
  
      powerDifference = (proportional * 1.5) + (derivative * 5);
  
      if (powerDifference > MAX_SPEED) {
        powerDifference = MAX_SPEED;
      }
      if (powerDifference < -MAX_SPEED) {
        powerDifference = -MAX_SPEED;
      }
  
      if (powerDifference < 0) {
        motorLeft = MAX_SPEED + powerDifference;
        motorRight = MAX_SPEED;
      }
      else {
        motorLeft = MAX_SPEED;
        motorRight = MAX_SPEED - powerDifference;
      }
  
      robotMove(motorLeft, motorRight);
    }

    float angle_deg = updateAngleZ();
    float angle_rad = angle_deg * pi / 180.0;

    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setCursor(0, 0);
    oled.print("Angle:");
    oled.print(angle_rad, 2);
    oled.print(" rad");
    oled.setCursor(0, 16);
    oled.print("D. enc_lung:");
    oled.print(dist_lung, 2);
    oled.print(" mm");
    oled.setCursor(0, 32);
    oled.print("D. enc_lat:");
    oled.print(dist_lat, 2);
    oled.print(" mm");
    oled.setCursor(0, 48);
    oled.print("Line val:");
    oled.print(adcMakerLine);
    oled.display();
  }
}

void robotMove(int speedLeft, int speedRight) {
  speedLeft = constrain(speedLeft, -255, 255);
  speedRight = constrain(speedRight, -255, 255);

  if (speedLeft >= 0) {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    ledcWrite(pwmChannel, speedLeft);
  } else {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    ledcWrite(pwmChannel, -speedLeft);
  }

  if (speedRight >= 0) {
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    ledcWrite(pwmChannel2, speedRight);
  } else {
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    ledcWrite(pwmChannel2, -speedRight);
  }
}

float get_angle(float x, float y) {
  float z = sqrt(x * x + y * y);
  return asin(y / z);
}

int16_t readGyroZRaw() {
  Wire.beginTransmission(MPU);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, (uint8_t)2, true);
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

  if (abs(gyroZ) < 1)
    gyroZ = 0;

  angleZ += (gyroZ + prevGyroZ) * 0.5 * dt;
  prevGyroZ = gyroZ;

  if (angleZ >= 180)
    angleZ -= 360;

  if (angleZ < -180)
    angleZ += 360;

  return angleZ;
}

void opreste() {
  ledcWrite(pwmChannel, 0);
  ledcWrite(pwmChannel2, 0);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void setupEncoder() {
  ESP32Encoder::useInternalWeakPullResistors = puType::up;
  encoder_lung.attachHalfQuad(19, 18);
  encoder_lat.attachHalfQuad(17, 16);
  encoder_lung.clearCount();
  encoder_lat.clearCount();
}

int32_t getEncoderCount(ESP32Encoder& encoder_ok) {
  return encoder_ok.getCount();
}

float get_distance(float ticks) {
  float circumferinta = 47 * pi;
  return (ticks / 100.0) * circumferinta;
}