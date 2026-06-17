const int M1A = 18;  // define pin 12 for A-1A 
const int M1B = 19;  // define pin 14 for A-1B 
const int M2A = 16;  // define pin 12 for A-1A 
const int M2B = 17;  // define pin 14 for A-1B 
int speedM1=2;
int speedM2=255;

void setup() {
  pinMode(M1A, OUTPUT);     // specify these pins as outputs
  pinMode(M1B, OUTPUT);
  digitalWrite(M1A, LOW);   // start with the motors off 
  digitalWrite(M1B, LOW);
	 pinMode(M2A, OUTPUT);     // specify these pins as outputs
  pinMode(M2B, OUTPUT);
  digitalWrite(M2A, LOW);   // start with the motors off 
  digitalWrite(M2B, LOW);
}
void loop() 
{
fata();
delay(2000);

}
void fata() {
  digitalWrite(M1A, speedM1);   
  digitalWrite(M1B, LOW);
	digitalWrite(M2A, speedM2);   
  digitalWrite(M2B, LOW);

}
void spate() {
  digitalWrite(M1A, LOW);   
  digitalWrite(M1B, speedM1);
	digitalWrite(M2A, LOW);   
  digitalWrite(M2B, speedM2);

}
void stanga() {
digitalWrite(M1A, LOW);   
digitalWrite(M1B, speedM1);
digitalWrite(M2A, LOW);   
digitalWrite(M2B, speedM2);
}
void dreapta() {

digitalWrite(M1A, speedM1);   
digitalWrite(M1B, LOW);
digitalWrite(M2A, speedM2);   
digitalWrite(M2B, LOW);
}
void stop() 
{ digitalWrite(M1A, LOW);   
digitalWrite(M1B, LOW);
digitalWrite(M2A, LOW);   
digitalWrite(M2B, LOW); 
}


