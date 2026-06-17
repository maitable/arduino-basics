// Pins connected to L9110H Motor Driver
#define A_IN1 16  // Motor A INA
#define A_IN2 17  // Motor A INB
#define B_IN1 18
#define B_IN2 19
#include <Bluepad32.h>

// Speed of the motor (PWM)
int motorSpeed = 50; // Range: 0 to 255
ControllerPtr myController = nullptr;

void onConnect(ControllerPtr ctl) {
  Serial.println("Controller conectat");
  myController = ctl;
}
void onDisconnect(ControllerPtr ctl) {
  Serial.println("Controller deconectat");
  if (myController == ctl) myController = nullptr;
}

void setup() {
  // Set the pins as outputs
  pinMode(A_IN1, OUTPUT);
  pinMode(A_IN2, OUTPUT);
  pinMode(B_IN1, OUTPUT);
  pinMode(B_IN2, OUTPUT);

  Serial.begin(115200);
  Serial.println("ESP32 L9110H Motor Driver Example");

  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  BP32.setup(&onConnect, &onDisconnect);
  BP32.forgetBluetoothKeys();
}

void loop() {
  BP32.update();
  if (myController && myController->isConnected() && myController->hasData()) {
    processGamepad(myController);
  }
  delay(50);}

  
void fata(){
  Serial.println("Moving Forward");
  analogWrite(A_IN1, motorSpeed); // Set IN1 to PWM speed
  analogWrite(A_IN2, 0);          // IN2 set to LOW
  analogWrite(B_IN1, motorSpeed); // Set IN1 to PWM speed
  analogWrite(B_IN2, 0);          // IN2 set to LOW
}
  
void stop(){
   // Stop
  Serial.println("Stopping");
  analogWrite(A_IN1, 0);
  analogWrite(A_IN2, 0);
  analogWrite(B_IN1, 0);
  analogWrite(B_IN2, 0);
}

void spate(){
    // Reverse direction
  Serial.println("Moving Reverse");
  analogWrite(A_IN1, 0);          // IN1 set to LOW
  analogWrite(A_IN2, motorSpeed); // Set IN2 to PWM speed
  analogWrite(B_IN1, 0);          // IN1 set to LOW
  analogWrite(B_IN2, motorSpeed); // Set IN2 to PWM speed
}

void processGamepad(ControllerPtr ctl) {
  uint16_t b = ctl->buttons();
  if (b & 0x0001)      fata();   // X
  else if (b & 0x0004) spate();  // patrat
  else                 stop();
}