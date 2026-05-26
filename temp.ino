#include <dht11.h>

const int sensor_pin = 2;

dht11 senzor;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int valoare = senzor.read(sensor_pin);
  Serial.print("H= ");
  Serial.print(senzor.humidity);
   Serial.print("   ");

  Serial.print("T=:");
  Serial.print(senzor.temperature);
  Serial.println();
  delay(2000);
  // put your main code here, to run repeatedly:

}
