//radar that lights up
const int trigPin = 10;
const int echoPin = 11;
const int red = 7;
const int yellow = 8;
const int green = 9;

long duration;
int distance;
void setup() {
myservo.attach(12);
pinMode(red, OUTPUT);
pinMode(yellow, OUTPUT);
pinMode(green, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

Serial.begin(115200);
}
void loop() {
myservo.write(0);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration * 0.034 / 2; 
Serial.print(distance);
Serial.println(" cm");

for (pos = i; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  delay(15);
  
  if(distance<=10)
{
  Serial.println("red");
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

}
if(distance>10 && distance <=30)
{
  Serial.println("yellow");
  digitalWrite(yellow, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);


}
if(distance>30)
{
  Serial.println("green");
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
                         // waits 15 ms for the servo to reach the position
}
for (pos = 180; pos >= 0; pos -= 1) { 
  if(distance<=10)
{
  Serial.println("red");
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

}
if(distance>10 && distance <=30)
{
  Serial.println("yellow");
  digitalWrite(yellow, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);


}
if(distance>30)
{
  Serial.println("green");
  digitalWrite(green, HIGH);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);// goes from 180 degrees to 0 degrees
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15 ms for the servo to reach the position
}




}


}
