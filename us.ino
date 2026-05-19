const int trigPin = 10;
const int echoPin = 11;
const int red = 7;
const int yellow = 8;
const int green = 9;

long duration;
int distance;
void setup() {
pinMode(red, OUTPUT);
pinMode(yellow, OUTPUT);
pinMode(green, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

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


}


}