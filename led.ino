
void setup() {
  pinMode(7, OUTPUT); // rosu
  pinMode(8, OUTPUT); // galben
  pinMode(9, OUTPUT); // verde
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(7, HIGH);  
  delay(2000);
  digitalWrite(8, HIGH);
  delay(500);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(2000);
  for(int i=1;i<=15; i++){
    digitalWrite(9, HIGH);
    delay(200);
    digitalWrite(9, LOW);
    delay(200);
  }                   
  digitalWrite(8, HIGH);   
  delay(500);
  digitalWrite(8, LOW);
}