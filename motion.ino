// motor right
const byte MOTOR_RIGHT_1_PIN = 12;
const byte MOTOR_RIGHT_2_PIN = 11;
const byte MOTOR_RIGHT_MAX = 225; // specific to assembly
// motor left
const byte MOTOR_LEFT_1_PIN = 10;
const byte MOTOR_LEFT_2_PIN = 9;
const byte MOTOR_LEFT_MAX = 255;


void right_go(byte speed) {
  digitalWrite(MOTOR_RIGHT_1_PIN, LOW);
  analogWrite(MOTOR_RIGHT_2_PIN, speed);
}

void right_stop() {
  digitalWrite(MOTOR_RIGHT_1_PIN, LOW);
  digitalWrite(MOTOR_RIGHT_2_PIN, LOW);
}

void left_go(byte speed) {
  digitalWrite(MOTOR_LEFT_1_PIN, LOW);
  analogWrite(MOTOR_LEFT_2_PIN, speed);
}

void left_stop() {
  digitalWrite(MOTOR_LEFT_1_PIN, LOW);
  digitalWrite(MOTOR_LEFT_2_PIN, LOW);
}

void go_forward() {
  right_go(MOTOR_RIGHT_MAX);
  left_go(MOTOR_LEFT_MAX);
}

void go_left(double diff_ratio) {
  right_go(MOTOR_RIGHT_MAX);
  left_go((byte) (MOTOR_LEFT_MAX * (1 - diff_ratio)));
}

void go_right(double diff_ratio) {
  left_go(MOTOR_LEFT_MAX);
  right_go((byte) (MOTOR_RIGHT_MAX * (1 - diff_ratio)));
}

void full_stop() {
  right_stop();
  left_stop();
}

void setup() {
  pinMode(MOTOR_LEFT_1_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_2_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_1_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_2_PIN, OUTPUT);

  // Test sequence

  delay(1000);
  go_forward();

  delay(1000);
  go_left(0.8);

  delay(1000);
  go_right(0.8);

  delay(1000);
  go_forward();

  delay(1000);
  full_stop();
}

void loop() {

}
