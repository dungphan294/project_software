// Define the control pins
int latchPin = 9;   // RCLK
int clockPin = 10;  // SRCLK
int dataPin = 8;   // SER

void setup() {
  // Set the control pins as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // Display numbers 0 to 9 on the 7-segment display
  for (int i = 0; i < 10; ++i) {
    displayNumber(i);
    delay(1000);  // 1 second delay
  }
}

void displayNumber(int number) {
  // Define the common cathode 7-segment display patterns
  byte patterns[10] = {
    // Bit DP G F E D C B A
    // 1 = OFF, 0 = ON
    B01000000,  // 0
   	B01111001,  // 1
    B00100100,  // 2
    B00110000,  // 3
    B00011001,  // 4
    B00010010,  // 5
    B00000011,  // 6
    B11111000,  // 7
    B00000000,  // 8
    B00011000   // 9
  };

  // Shift out the pattern to the 74HC595
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, patterns[number]);
  digitalWrite(latchPin, HIGH);
}
