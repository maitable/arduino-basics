const int trig1 = 5;
const int echo1 = 2;
const int trig2 = 4;
const int echo2 = 3;

long duration1, duration2;
int distance1, distance2;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);

  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);

  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);

  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  // Măsoară durata pulsului
  duration1 = pulseIn(echo1, HIGH);
  // Convertește durata în distanță
  distance1 = duration1 * 0.034 / 2; // Convertește timpul în distanță (cm)
  Serial.print("d1= ");
  Serial.print(distance1);
  Serial.print(" cm   ");


  digitalWrite(trig2, LOW);
  delayMicroseconds(2);

  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  // Măsoară durata pulsului
  duration2 = pulseIn(echo2, HIGH);
  // Convertește durata în distanță
  distance2 = duration2 * 0.034 / 2; // Convertește timpul în distanță (cm)
  Serial.print("d2= ");
  Serial.print(distance2);
  Serial.println(" cm");

}
