#include <Bluepad32.h>

const int LED1_PIN = 22;   // GPIO2
const int LED2_PIN = 23;   // GPIO4

ControllerPtr myController = nullptr;

void onConnect(ControllerPtr ctl) {
  Serial.println("Controller conectat");
  myController = ctl;
}

void onDisconnect(ControllerPtr ctl) {
  Serial.println("Controller deconectat");
  if (myController == ctl) myController = nullptr;
}

void processGamepad(ControllerPtr ctl) {
  // butoanele de actiune sunt un bitmask
  uint16_t b = ctl->buttons();

  if (b & 0x0001) digitalWrite(LED1_PIN, HIGH);  // X / cross  -> LED1 on
  if (b & 0x0004) digitalWrite(LED1_PIN, LOW);   // square     -> LED1 off
  if (b & 0x0008) digitalWrite(LED2_PIN, HIGH);  // triangle   -> LED2 on
  if (b & 0x0002) digitalWrite(LED2_PIN, LOW);   // circle     -> LED2 off
}

void setup() {
  Serial.begin(115200);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  BP32.setup(&onConnect, &onDisconnect);

  // sterge cheile BT salvate ca sa poti face pairing nou
  BP32.forgetBluetoothKeys();
}

void loop() {
  BP32.update();
  if (myController && myController->isConnected() && myController->hasData()) {
    processGamepad(myController);
  }
  delay(50);
}