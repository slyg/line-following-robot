#define SENSOR_PINS 4

uint8_t pins[SENSOR_PINS] = {2, 3, 4, 5};

// motor right
const byte MOTOR_RIGHT_1_PIN = 12;
const byte MOTOR_RIGHT_2_PIN = 11;
const byte MOTOR_RIGHT_MAX = 225; // specific to assembly
// motor left
const byte MOTOR_LEFT_1_PIN = 10;
const byte MOTOR_LEFT_2_PIN = 9;
const byte MOTOR_LEFT_MAX = 255;

// differentials used for turns
const double SMALL_RATIO = 0.7;
const double MEDIUM_RATIO = 0.8;
const double LARGE_RATIO = 1;

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

/*
 * 0000 -> 0  -> stop
 * 0001 -> 1  -> full right
 * 0011 -> 3  -> normal right
 * 0010 -> 2  -> slight rigth
 * 0110 -> 6  -> forward
 * 0100 -> 4  -> slight left
 * 1100 -> 12 -> normal left
 * 1000 -> 8  -> full left
 * 1111 -> 15 -> stop
 *
 */
void controller(uint8_t data) {
  switch (data) {
    case 0:
      // Serial.println("stop");
      full_stop();
      break;
    case 1:
      // Serial.println("full right");
      go_right(LARGE_RATIO);
      break;
    case 3:
      // Serial.println("normal right");
      go_right(MEDIUM_RATIO);
      break;
    case 2:
      // Serial.println("slight right");
      go_right(SMALL_RATIO);
      break;
    case 6:
      // Serial.println("forward");
      go_forward();
      break;
    case 4:
      // Serial.println("slight left");
      go_left(SMALL_RATIO);
      break;
    case 12:
      // Serial.println("normal left");
      go_left(MEDIUM_RATIO);
      break;
    case 8:
      // Serial.println("full left");
      go_left(LARGE_RATIO);
      break;
    case 15:
      // Serial.println("stop");
      full_stop();
      break;
    default:
      // Serial.println("stop");
      full_stop();
  }
}

void setup(void) {
  // Serial.begin(9600);

  pinMode(MOTOR_LEFT_1_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_2_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_1_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_2_PIN, OUTPUT);

  for (uint8_t i = 0; i < SENSOR_PINS; i++)
    pinMode(pins[i], INPUT);
}

void loop(void) {
  uint8_t inputs = 0;

  for (uint8_t i = 0; i < SENSOR_PINS; i++) {
    inputs = inputs << 1;
    inputs |= digitalRead(pins[i]);
  }

  controller(inputs);
}
