#include <IRremote.h>
// Include the string library
int RECV_PIN = 3;
int g = 2;
String val = "";
String PWR = "10efd827";
int on = 0;

IRrecv irrecv(RECV_PIN);

decode_results  results;

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  irrecv.enableIRIn();  // Start the receiver
}

void loop() {
  val = String("");
  if (irrecv.decode(&results))  {
   
    val = String(results.value, HEX);
    Serial.println(val);
    irrecv.resume(); // Receive  the next value
  }
  
  if(val == PWR){
    if(on==0){
      digitalWrite(2, HIGH);
      on = 1;
    }
    else{
      digitalWrite(2, LOW);
      on = 0;
    }

  }
  
  delay(150);
}

//