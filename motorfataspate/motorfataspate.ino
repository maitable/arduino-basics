const int M1A = 9;  // define pin 12 for A-1A 
const int M1B = 10;  // define pin 14 for A-1B 
const int M2A = 3;  // define pin 12 for A-1A 
const int M2B = 5;  // define pin 14 for A-1B 
int speedM1=200;
int speedM2=200;

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
spate();
delay(2000);
fata();
delay(2000);
stanga();
delay(2000);
dreapta();
delay(2000);

}
void fata() {
 for(int i=180;i<255;i=i+10)
{ speedM1=i;
 speedM2=i;
  digitalWrite(M1A, speedM1);   
  digitalWrite(M1B, LOW);
	digitalWrite(M2A, speedM2);   
  digitalWrite(M2B, LOW);}

}
void spate() {
  for(int i=180;i<255;i=i+10){
 speedM1=i;
 speedM2=i;
  digitalWrite(M1A, LOW);   
  digitalWrite(M1B, speedM1);
	digitalWrite(M2A, LOW);   
  digitalWrite(M2B, speedM2);
  }
}
void stanga() {
  for( int i=180;i<255;i=i+10){
 speedM1=i;
 speedM2=180;
digitalWrite(M1A, LOW);   
digitalWrite(M1B, speedM1);
digitalWrite(M2A, LOW);   
digitalWrite(M2B, speedM2);}
}
void dreapta() {
 for(int  i=180;i<255;i=i+10){
 speedM2=i;
 speedM1=180;
digitalWrite(M1A, speedM1);   
digitalWrite(M1B, LOW);
digitalWrite(M2A, speedM2);   
digitalWrite(M2B, LOW);
}}
void stop() 
{ digitalWrite(M1A, LOW);   
digitalWrite(M1B, LOW);
digitalWrite(M2A, LOW);   
digitalWrite(M2B, LOW); 
}


