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
double pi = 2*acos(0.0);

int motor1pin1 = 27;
int motor1pin2 = 26;
int motor2pin1 = 25;
int motor2pin2 = 33;

const int freq = 30000;
const int pwmc1 = 0;
const int pwmc2 = 1;
const int pwmc3 = 2;
const int pwmc4 = 3;

const int resolution = 8;

#define MAX_SPEED 255
int vitezaBaza = 255;

const int makerlinepin = 35;

int adcmakerline = 0;
int adcsetpoint = 0;
int proportional = 0;
int lastproportional = 0;
int derivative = 0;
int powerdifference = 0;
int motorleft = 0;
int motorright = 0;


unsigned long currentmillis = 0;
unsigned long previousmillis = 0;
const int interval = 10;

void setup()
{
  pinMode(makerlinepin, INPUT);
  analogReadResolution(10);

  ledcSetup(pwmc1, freq, resolution);
  ledcAttachPin(motor1pin1, pwmc1);

  ledcSetup(pwmc2, freq, resolution);
  ledcAttachPin(motor1pin2, pwmc2);

  ledcSetup(pwmc3, freq, resolution);
  ledcAttachPin(motor2pin1, pwmc3);
  
  ledcSetup(pwmc4, freq, resolution);
  ledcAttachPin(motor2pin2, pwmc4);

  Serial.begin(115200);
  Serial.println("meow");

  adcsetpoint = analogRead(makerlinepin);

  delay(2000);
}

void loop(){
  currentmillis = millis();
  if(currentmillis - previousmillis > interval){
    previousmillis = currentmillis;
    adcmakerline = analogRead(makerlinepin);

    if(adcmakerline<51){
      robotMove(0,0); //de scris aceasta fubctie
    }
    else if(adcmakerline>972){
      robotMove(MAX_SPEED-25, MAX_SPEED-25);
    }
    else{
      proportional = adcmakerline - adcsetpoint;
      derivative = proportional - lastproportional;
      lastproportional = proportional;
      
      powerdifference = (proportional*1.5) + (derivative*5);

      if(powerdifference>MAX_SPEED){
        powerdifference = MAX_SPEED;
      }
      if(powerdifference<-MAX_SPEED){
        powerdifference = -MAX_SPEED;
      }
      if(powerdifference<0){
        motorleft=MAX_SPEED+powerdifference;
        motorright = MAX_SPEED;
      }
      else{
        motorleft=MAX_SPEED;
        motorright=MAX_SPEED-powerdifference;                                
      }
      robotMove(motorleft, motorright);
      
      Serial.print("adc: ");
      Serial.print(adcmakerline);
      Serial.print("motorleft: ");
      Serial.print(motorleft);
      Serial.print("motorright: ");
      Serial.println(motorright);
    }
  }
}


void robotMove(int speedLeft, int speedRight)
{
  speedLeft = constrain(speedLeft, -255, 255);
  speedRight = constrain(speedRight, -255, 255);
  
  if (speedLeft > 0) {
    int speedL = map(speedLeft, 0, 255, 255, 0);
    ledcWrite(pwmc1, speedL);
    ledcWrite(pwmc2, 255);
  }
  else {
    int speedL = map(speedLeft, -255, 0, 0, 255);
    ledcWrite(pwmc1, 255);
    ledcWrite(pwmc2, speedL);
  }

  if (speedRight > 0) {
    int speedR = map(speedRight, 0, 255, 255, 0);
    ledcWrite(pwmc3, speedR);
    ledcWrite(pwmc4, 255);
  }
  else {
    int speedR = map(speedRight, -255, 0, 0, 255);
    ledcWrite(pwmc3, 255);
    ledcWrite(pwmc4, speedR);
  }
}
