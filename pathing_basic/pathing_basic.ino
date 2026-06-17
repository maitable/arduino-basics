double pi = 2*acos(0.0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(get_angle(5, 6));
  Serial.print("  ");
  Serial.println(get_hyp(5, 6));
}

float get_angle(float x, float y){
  float z = sqrt(pow(x, 2) + pow(y, 2));
  float angle_rad = asin(y / z) ;
  float angle_degr = angle_rad * 180/pi;
  return angle_rad;
}

float get_hyp(float x, float y){
  float z = sqrt(pow(x, 2) + pow(y, 2));
  return z;
} 