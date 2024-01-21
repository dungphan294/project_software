const int SEGMENT_PINS[8] = { 2, 3, 5, 6, 7, 8, 9, 4 };
size_t LENGTH = sizeof(SEGMENT_PINS) / sizeof(SEGMENT_PINS[0]);
void setup() {
  for (int pin : SEGMENT_PINS) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
}

void loop() {
  for (int pin = 0; pin < LENGTH; pin++) {
    digitalWrite(SEGMENT_PINS[pin], HIGH);
    delay(500);
    digitalWrite(SEGMENT_PINS[pin], LOW);
    delay(500);
  }
}
