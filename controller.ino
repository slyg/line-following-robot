#define SENSOR_PINS 4

uint8_t pins[SENSOR_PINS] = {2, 3, 4, 5};

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
      Serial.println("stop");
      break;
    case 1:
      Serial.println("full right");
      break;
    case 3:
      Serial.println("normal right");
      break;
    case 2:
      Serial.println("slight right");
      break;
    case 6:
      Serial.println("forward");
      break;
    case 4:
      Serial.println("slight left");
      break;
    case 12:
      Serial.println("normal left");
      break;
    case 8:
      Serial.println("full left");
      break;
    case 15:
      Serial.println("stop");
      break;
    default:
      Serial.println("stop");
  }
}

void setup(void) {
  Serial.begin(9600);
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
