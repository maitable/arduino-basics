#include <Servo.h>

Servo servo;

int val;    // variable to read the value from the analog pin


const int trigPin = 10;
const int echoPin = 11;


long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
servo.attach(9);

Serial.begin(115200);
}
void loop() {
// Trimite semnalul ultrasonic
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Măsoară durata pulsului
duration = pulseIn(echoPin, HIGH);
// Convertește durata în distanță
distance = duration * 0.034 / 2; // Convertește timpul în distanță (cm)
Serial.print("Distanță: ");
Serial.print(distance);
Serial.println(" cm");
if(distance<=50){
  val = map(distance, 0, 50, 0, 180);
  servo.write(val);
  Serial.println("Going to: ");
  Serial.println(val);
  delay(5);
}
else{
  servo.write(0);
  delay(5);
}
//dist 10,50 

}