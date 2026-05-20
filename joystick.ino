#define xpin A0
#define ypin A1
const int buttonpress = 2;
const int g = 3;
const int r = 4;

int xval = 0;
int yval = 0;
int is_pressed = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonpress , INPUT_PULLUP);
  pinMode(g, OUTPUT);
  Serial.begin(115200); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(g, LOW);
  digitalWrite(r, LOW);
  xval = analogRead(xpin);
  yval = analogRead(ypin);
  is_pressed = digitalRead(buttonpress);
  Serial.print("x: ");
  Serial.print(xval);
  Serial.print(" ");

  Serial.print("y: ");
  Serial.println(yval);

  //rosu pe y
  if(yval<450 || yval>475){
    Serial.println("Rosu aprins");
    digitalWrite(r, HIGH);
  }

  //verde pe x
  if(xval<510 || xval>520){
    Serial.println("Verde aprins");
    digitalWrite(g, HIGH);
  }
  
  if(is_pressed == LOW){
    Serial.println("Button pressed");
    digitalWrite(g, LOW);
    digitalWrite(r, LOW);}

  delay(500);
  //se inchid toate
}
