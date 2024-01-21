//
// Created by Dung Phan on 1/18/2024.
//

#ifndef DEMO_FUNCTIONS_H
#define DEMO_FUNCTIONS_H
#include "Arduino.h"
#include "variables.h"
// // # COMPONENTS & VARIABLES
// // ## ROTARY ENCODER
// const int RE_BUTTON_PIN = 10;  // SW
// const int RE_CLK_PIN = 9;      // A
// const int RE_DATA_PIN = 8;     // B

// // ## BUTTON
// const int BUTTON_DOOR_PIN = 4;   // BUTTON OPEN DOOR
// const int BUTTON_SERVO_PIN = 3;  // BUTTON Check pass

///
/// \param button_pin
/// \param debounce_time
/// \return
bool is_button_pressed(const int button_pin, const int debounce_time);

#endif //DEMO_FUNCTIONS_H
