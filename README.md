# project_software
Project Software - Saxion

// Khai báo pin (3 pin : Latchpin, data, clock)
    ENTER NUMBER FROM ROTARY ENCODER
// DISPLAY: 1st 7-segment on :
// TO DO: Choose value for the first 7-segment
  INPUT: Read DATA from Rotary encoder
  PROCESS: Arduino 
  OUTPUT: Display input from Rotary to 7 segments
//TO DO: Click to enter a number (CLICK ROTARY ENCODER BUTTON)
//TO DO: Switch to the second 7-segment
  Click to switch from rotary encoder (BUTTON)
  Display on 7-segments

//DISPLAY: 1st 7-segment on, 2nd 7-segment on :
//TO DO: Choose value for the second 7-segment
  INPUT: Read DATA from Rotary encoder
  PROCESS: Arduino 
  OUTPUT: Display input from Rotary to SHIFT REGISTER
//TO DO: Click to enter a number (CLICK ROTARY ENCODER BUTTON)
//TO DO: Switch to the third 7-segment
  Click to switch from rotary encoder (BUTTON)
  Display on 7-segments

//DISPLAY: 1st 7-segment on, 2nd 7-segment on, 3rd 7-segment on
//TO DO: Choose value for the third 7-segment
  INPUT: Read DATA from Rotary encoder
  PROCESS: Arduino 
  OUTPUT: Display input from Rotary to BCD
//TO DO: Click to enter a number (CLICK ROTARY ENCODER BUTTON)
//TO DO: Set up button(1) 
//TO DO: Click the button(1) to unlock (Servo)
  Click to unlock from Rotary encoder (BUTTON)
  Display on OLED to show notification

    CHECK PASS
//CASE 1: Success
//DISPLAY: LED 1, 2, 3 BLINK BUZZER OK OLED CORRECT =>> END
//Servo Rotate:
//TO DO: Set up button(2)
//TO DO: Click button(2) to rotate servo
//DISPLAY: LED 1, 2, 3 BLINK then OFF 
//DISPLAY: Servo rotating, door open

//CASE 2: Failed (Use EEPROM to save memory from 7 segments)
//Display: LED 1 ON BUZZER FAILED OLED INCORRECT
//TO DO: Turn back to "FIRST SEGMENT ON" steps 
//IF FAILED =>> DISPLAY: LED 2 ON BUZZER FAILED OLED INCORRECT 

//IF 2nd FAILED =>> DISPLAY: LED 3 ON BUZZER FAILED OLED INCORRECT 
//TO DO: Turn back to "FIRST SEGMENT ON" steps 

//IF continue FAILED (After 3 wrong attempts) =>> DISPLAY: Locked for 100s (each 3 wrong attempts) 
//TO DO: Turn back to "FIRST SEGMENT ON" steps
//TO DO: +100s waiting for the next attempt

  Change pass:(After safe open)
//TO DO: Click button to change password mode
//Display: OLED: Old password
//TO DO: Enter current password
//Display: Enter input for 7-segment
//TO DO: Click button to confirm
//IF NO =>> TURN BACK TO enter current password
//IF YES =>> DISPLAY: OLED: New password 
//TO DO: Enter new password
//TO DO: Enter input for 7-segment 
//IF NO: TURN BACK TO enter new password
//IF YES =>> DISPLAY: OLED: Change password successfully


