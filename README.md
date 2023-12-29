# project_software
Project Software - Saxion

// Khai báo pin (3 pin : Latchpin, data, clock)
    ENTER NUMBER FROM ROTARY ENCODER
// DISPLAY: 1st 7-segment on :
// TO DO: Choose value for the first 7-segment
  INPUT: Read DATA from Rotary encoder
  PROCESS: Arduino 
  OUTPUT: Display input from Rotary to 7 segments
// TO DO: Click to enter a number (CLICK ROTARY ENCODER BUTTON)
// TO DO: Switch to the second 7-segment
  Click to switch from rotary encoder (BUTTON)
  Display on 7-segments

//DISPLAY: 1st 7-segment on, 2nd 7-segment on :
//TO DO: Choose value for the second 7-segment
  INPUT: Read DATA from Rotary encoder
  PROCESS: Arduino 
  OUTPUT: Display input from Rotary to 7 segments
//TO DO: Click to enter a number (CLICK ROTARY ENCODER BUTTON)
//TO DO: Switch to the third 7-segment
  Click to switch from rotary encoder (BUTTON)
  Display on 7-segments

//DISPLAY: 1st 7-segment on, 2nd 7-segment on, 3rd 7-segment on
//TO DO: Choose value for the third 7-segment
  INPUT: Read DATA from Rotary encoder
  PROCESS: Arduino 
  OUTPUT: Display input from Rotary to 7 segments
//TO DO: Click to enter a number (CLICK ROTARY ENCODER BUTTON)
//TO DO: Click the button to unlock (Servo)
  Click to unlock from Rotary encoder (BUTTON)
  Display on OLED to show notification

    There are 2 cases:
//CASE 1: Successful
//DISPLAY: Notification from LED, Buzzer, OLED

//CASE 2: Failed (Use EEPROM to save memory from 7 segments)
//TO DO: Save to memory +1 failed attempt
//TO DO: Try again to open 
//IF SUCCESSFUL =>> DISPLAY: Notification from LED, Buzzer, OLED
//IF FAILED (AFTER 3 WRONG ATTEMPTS) =>> Set a time (100s) to wait for next attempt
//TURN BACK TO DO: Save to memory +1 failed attempt
//TO DO: Try again to open 

    Open/Close safe (SERVO)
//Servo Rotate:
//
