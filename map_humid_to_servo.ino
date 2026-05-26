#include <dht11.h>
#include <Servo.h>

const int dht_pin = 2;
const int servo_pin = 3;
int val;

dht11 dht;
Servo myservo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(servo_pin);

}

void loop() {
  // put your main code here, to run repeatedly:
  int dhtval = dht.read(dht_pin);
  int h = dht.humidity;
  Serial.println(h);
  val = map(h, 45,90, 0, 160);
  myservo.write(val);
  Serial.print("H = ");
  Serial.print(h);
  Serial.println("   ");
  Serial.print("Val = ");
  Serial.print(val);
  Serial.println("   ");
  delay(2000);


}
