//
// Created by Dung Phan on 1/1/2024.
//

#include "display.h"

static void zero() {  // 0000
  digitalWrite(BCD_A_PIN, LOW);
  digitalWrite(BCD_B_PIN, LOW);
  digitalWrite(BCD_C_PIN, LOW);
  digitalWrite(BCD_D_PIN, LOW);
  digitalWrite(BCD_DP_PIN, LOW);
}

static void one() {  // 0001
  digitalWrite(BCD_A_PIN, HIGH);
  digitalWrite(BCD_B_PIN, LOW);
  digitalWrite(BCD_C_PIN, LOW);
  digitalWrite(BCD_D_PIN, LOW);
  digitalWrite(BCD_DP_PIN, LOW);
}

static void two() {  // 0010
  digitalWrite(BCD_A_PIN, LOW);
  digitalWrite(BCD_B_PIN, HIGH);
  digitalWrite(BCD_C_PIN, LOW);
  digitalWrite(BCD_D_PIN, LOW);
  digitalWrite(BCD_DP_PIN, LOW);
}

static void three() {  // 0011
  digitalWrite(BCD_A_PIN, HIGH);
  digitalWrite(BCD_B_PIN, HIGH);
  digitalWrite(BCD_C_PIN, LOW);
  digitalWrite(BCD_D_PIN, LOW);
  digitalWrite(BCD_DP_PIN, LOW);
}

static void four() {  // 0100
  digitalWrite(BCD_A_PIN, LOW);
  digitalWrite(BCD_B_PIN, LOW);
  digitalWrite(BCD_C_PIN, HIGH);
  digitalWrite(BCD_D_PIN, LOW);
  digitalWrite(BCD_DP_PIN, LOW);
}

static void five() {  // 0101
  digitalWrite(BCD_A_PIN, HIGH);
  digitalWrite(BCD_B_PIN, LOW);
  digitalWrite(BCD_C_PIN, HIGH);
  digitalWrite(BCD_D_PIN, LOW);
  digitalWrite(BCD_DP_PIN, LOW);
}

static void six() {  // 0110
  digitalWrite(BCD_A_PIN, LOW);
  digitalWrite(BCD_B_PIN, HIGH);
  digitalWrite(BCD_C_PIN, HIGH);
  digitalWrite(BCD_D_PIN, LOW);
  digitalWrite(BCD_DP_PIN, LOW);
}

static void seven() {  // 0111
  digitalWrite(BCD_A_PIN, HIGH);
  digitalWrite(BCD_B_PIN, HIGH);
  digitalWrite(BCD_C_PIN, HIGH);
  digitalWrite(BCD_D_PIN, LOW);
  digitalWrite(BCD_DP_PIN, LOW);
}

static void eight() {  // 1000
  digitalWrite(BCD_A_PIN, LOW);
  digitalWrite(BCD_B_PIN, LOW);
  digitalWrite(BCD_C_PIN, LOW);
  digitalWrite(BCD_D_PIN, HIGH);
  digitalWrite(BCD_DP_PIN, LOW);
}

static void nine() {  // 1001
  digitalWrite(BCD_A_PIN, HIGH);
  digitalWrite(BCD_B_PIN, LOW);
  digitalWrite(BCD_C_PIN, LOW);
  digitalWrite(BCD_D_PIN, HIGH);
  digitalWrite(BCD_DP_PIN, LOW);
}

static void zero_dp() {
  digitalWrite(BCD_A_PIN, LOW);
  digitalWrite(BCD_B_PIN, LOW);
  digitalWrite(BCD_C_PIN, LOW);
  digitalWrite(BCD_D_PIN, LOW);
  digitalWrite(BCD_DP_PIN, HIGH);
}

static byte byte_to_number(const int number) {
  byte patterns[11] = {
    // Bit DP G F E D C B A
    // 1 = OFF, 0 = ON
    B01000000,  // 0
    B01111001,  // 1
    B00100100,  // 2
    B00110000,  // 3
    B00011001,  // 4
    B00010010,  // 5
    B00000011,  // 6
    B01111000,  // 7
    B00000000,  // 8
    B00011000,  // 9
    B11000000   // 0 without DP
  };
  return patterns[number];
}


void display_number(int number, int display) {
  static int shift_register_1 = 0;
  // TODO: Function to control BCD
  if (display == 0) {  // Choosing value for the first shift register
    digitalWrite(SR_LATCH_PIN, LOW);
    shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, byte_to_number(10));
    shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, byte_to_number(number));  // Shift pattern for the first display
    digitalWrite(SR_LATCH_PIN, HIGH);
    shift_register_1 = number;
  } else if (display == 1) {  // Choosing value for the second shift register
    digitalWrite(SR_LATCH_PIN, LOW);
    shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, byte_to_number(number));            // Save first number
    shiftOut(SR_DATA_PIN, SR_CLOCK_PIN, MSBFIRST, byte_to_number(shift_register_1));  // Save first number
    digitalWrite(SR_LATCH_PIN, HIGH);
  } else if (display == 2) {
    switch (number) {
      case 0:
        zero();
        break;
      case 1:
        one();
        break;
      case 2:
        two();
        break;
      case 3:
        three();
        break;
      case 4:
        four();
        break;
      case 5:
        five();
        break;
      case 6:
        six();
        break;
      case 7:
        seven();
        break;
      case 8:
        eight();
        break;
      case 9:
        nine();
        break;
      case 10:
        zero_dp();
        break;
      default:
        zero();
    }
  }
}