// C++ code //

#define M1_0 3
#define M1_1 5

int setPWM = 255;

void setup() {
  pinMode(M1_0, OUTPUT);
  pinMode(M1_1, OUTPUT);
}

void loop() {
  analogWrite(M1_0, 0);
  analogWrite(M1_1, setPWM);
  delay(3000);

  analogWrite(M1_0, 0);
  analogWrite(M1_1, 0);
  delay(3000);
}