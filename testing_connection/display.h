//
// Created by Dung Phan on 1/1/2024.
//

#ifndef DEMO_DISPLAY_H
#define DEMO_DISPLAY_H

#include <Arduino.h>

// ## SHIFT REGISTER
const int SR_DATA_PIN = 13;   // SER
const int SR_LATCH_PIN = 12;  // RCLK
const int SR_CLOCK_PIN = 11;  // SRCLK
// ## BCD
const int BCD_A_PIN = A0;  // BCD Input 1
const int BCD_B_PIN = A1;  // BCD Input 2
const int BCD_C_PIN = A2;  // BCD Input 3
const int BCD_D_PIN = A3;  // BCD Input 4
const int BCD_DP_PIN = A4;

/// BCD number 0
static void zero();
/// BCD number 1
static void one();
/// BCD number 2
static void two();
/// BCD number 3
static void three();
/// BCD number 4
static void four();
/// BCD number 5
static void five();
/// BCD number 6
static void six();
/// BCD number 7
static void seven();
/// BCD number 8
static void eight();
/// BCD number 9
static void nine();
/// BCD number 0 without DP
static void zero_dp();

/// Convert number to byte value, display it on specific 7-segment using shift register
/// \param number Number wants to display
/// \return Number in byte form
static byte byte_to_number(const int number);

/// Showing number in specific 7-segment using shift register
/// \param number
/// \param display
void display_number(int number, int display);

#endif  //DEMO_DISPLAY_H
