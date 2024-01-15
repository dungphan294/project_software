/*
 * Workflow of the ELECTRICAL SAFE
 * # SITUATION: FIRST USE
 * -- STATE: SAFE CLOSE
 * 1. Connect to POWER SOURCES
 * 2. 3 SEVEN SEGMENTS set up at {0, 0, 0} -> function is_password_correct()
 * 3. Click SERVO_BUTTON -> servo_rotate(90)
 * 4. All number reset to ZERO
 * 5. Click DOOR_BUTTON -> indicate the door of the safe is OPENED
 * -- STATE: SAFE OPEN 
 * 1. Click SERVO_BUTTON again-> STATE: CHANGE PASSWORD -> function change_password()
 * 2. Back to the first 7-segment: DP light up, other DP don't
 * 3. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 4. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 5. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 6. Click SERVO_BUTTON -> END STATE: CHANGE PASSWORD -> function notification()
 * 7. Click DOOR_BUTTON -> indicate the door of the safe is CLOSED -> servo_rotate(0)
 * -- STATE: SAFE CLOSE
 * # SITUATION: FROM THE SECOND TIMES
 * -- STATE: SAFE CLOSE
 * 1. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 2. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 3. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 4. Click SERVO_BUTTON -> servo_rotate(90)
 * 5. All number reset to ZERO
 * 6. Click DOOR_BUTTON -> indicate the door of the safe is OPENED
 * 7. Click DOOR_BUTTON again -> indicate the door of the safe is CLOSED -> servo_rotate(0)
 * -- SITUATION: CHANGE PASSWORD
 * 1. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 2. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 3. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 4. Click SERVO_BUTTON -> servo_rotate(90)
 * 5. All number reset to ZERO
 * 6. Click DOOR_BUTTON -> indicate the door of the safe is OPENED
 * -- STATE: SAFE OPEN *
 * 1. Click SERVO_BUTTON -> STATE: CHANGE PASSWORD -> function change_password()
 * 2. Back to the first 7-segment: DP light up, other DP don't
 * 3. Choose the number for the 1st segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 4. Choose the number for the 2nd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 5. Choose the number for the 3rd segment -> Click the ROTARY_BUTTON -> Save it into EEPROM
 * 6. Click SERVO_BUTTON -> END STATE: CHANGE PASSWORD -> function notification()
 * 7. Click DOOR_BUTTON -> indicate the door of the safe is CLOSED -> servo_rotate(0)
 */