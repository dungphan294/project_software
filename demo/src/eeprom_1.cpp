/*
 * Comprehensive Workflow of the ELECTRICAL SAFE
 * # SITUATION: FIRST USE
 * -- STATE: SAFE CLOSE
 * 1. Connect to POWER SOURCES
 * 2. Initialize system components
 *    - 3 SEVEN SEGMENTS set up at {0, 0, 0} -> function is_password_correct()
 *    - Initialize LEDs, servos, and buttons
 * 3. Click SERVO_BUTTON -> servo_rotate(90)
 * 4. All number reset to ZERO
 * 5. Click DOOR_BUTTON -> indicate the door of the safe is OPENED
 * -- STATE: SAFE OPEN *
 * 1. Click DOOR_BUTTON again -> indicate the door of the safe is CLOSED -> servo_rotate(0)
 * 2. Enter password to confirm closing, if needed
 * 3. Click SERVO_BUTTON -> STATE: CHANGE PASSWORD -> function change_password()
 * 4. Back to the first 7-segment: DP light up, other DP don't
 * 5. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 6. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 7. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 8. Click SERVO_BUTTON -> END STATE: CHANGE PASSWORD -> function notification()
 * -- STATE: SAFE CLOSE
 * # SITUATION: FROM THE SECOND TIMES
 * -- STATE: SAFE CLOSE
 * 1. Enter current password to unlock, if needed
 * 2. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 3. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 4. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 5. Click SERVO_BUTTON -> servo_rotate(90)
 * 6. All number reset to ZERO
 * 7. Click DOOR_BUTTON -> indicate the door of the safe is OPENED
 * 8. Click DOOR_BUTTON again -> indicate the door of the safe is CLOSED -> servo_rotate(0)
 * -- SITUATION: CHANGE PASSWORD
 * 1. Enter current password to unlock, if needed
 * 2. Click SERVO_BUTTON -> servo_rotate(90)
 * 3. All number reset to ZERO
 * 4. Click DOOR_BUTTON -> indicate the door of the safe is OPENED
 * 5. Click SERVO_BUTTON -> STATE: CHANGE PASSWORD -> function change_password()
 * 6. Back to the first 7-segment: DP light up, other DP don't
 * 7. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 8. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 9. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 10. Click SERVO_BUTTON -> END STATE: CHANGE PASSWORD -> function notification()
 * 11. Click DOOR_BUTTON -> indicate the door of the safe is CLOSED -> servo_rotate(0)
 */
