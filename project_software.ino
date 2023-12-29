//  SHIFT REGISTER
cosnt int SR_DATA_PIN = 13;   // SER
cosnt int SR_LATCH_PIN = 12;  // RCLK
cosnt int SR_CLOCK_PIN = 11;  // SRCLK
// BCD
cosnt int BCD_A_PIN = A0;
cosnt int BCD_B_PIN = A1;
cosnt int BCD_C_PIN = A2;
cosnt int BCD_D_PIN = A3;
// ROTARY ENCODER
cosnt int RE_CLK_PIN = 6;
cosnt int RE_A_PIN = 5;
cosnt int RE_B_PIN = 4;

void setup() {
  // SHIFT REGISTER
  pinMode(SR_DATA_PIN, OUTPUT);
  pinMode(SR_LATCH_PIN, OUTPUT);
  pinMode(SR_CLOCK_PIN, OUTPUT);
  // BCD
  pinMode(BCD_A_PIN, OUTPUT);
  pinMode(BCD_B_PIN, OUTPUT);
  pinMode(BCD_C_PIN, OUTPUT);
  pinMode(BCD_D_PIN, OUTPUT);
  // ROTARY ENCODER
  pinMode(RE_CLK_PIN, INPUT);
  pinMode(RE_A_PIN, INPUT);
  pinMode(RE_B_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}
