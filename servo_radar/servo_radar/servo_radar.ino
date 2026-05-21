// radar that lights up
#include <Servo.h>

Servo myservo;

const int trigPin = 10;
const int echoPin = 11;
const int red = 7;
const int yellow = 8;
const int green = 9;

long duration;
int distance;
int pos;

void setup() {
    myservo.attach(13);
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(115200);
    delay(1000);
    myservo.write(0);
    delay(1000);
    myservo.write(90);
    delay(1000);
    myservo.write(180);
}

void measureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout ← THIS
    
    if (duration == 0) {
        distance = 999; // nothing detected, out of range
    } else {
        distance = duration * 0.034 / 2;
    }
    
    Serial.print(distance);
    Serial.println(" cm");
}

void updateLEDs() {
    if (distance == 999) {
        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(green, HIGH);} // nothing nearby = green
    if (distance <= 10) {
        Serial.println("red");
        digitalWrite(red, HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);
    } else if (distance > 10 && distance <= 30) {
        Serial.println("yellow");
        digitalWrite(yellow, HIGH);
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
    } else {
        Serial.println("green");
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
    }
}

void loop() {
    // Sweep 0 180
    for (pos = 0; pos <= 180; pos += 1) {
        myservo.write(pos);
        measureDistance();
        updateLEDs();
        delay(15);
    }

    // Sweep 180 0
    for (pos = 180; pos >= 0; pos -= 1) {
        myservo.write(pos);
        measureDistance();
        updateLEDs();
        delay(15);
    }
}