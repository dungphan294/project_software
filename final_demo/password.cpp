// #include "password.h"
// #include "notification.h"

// void save_user_input(password_t *user_input, int segment) {
//   Serial.print("Save USER_INPUT at MEMORY ADDRESS: ");
//   Serial.print(EEPROM_USER_MEMORY + segment);
//   Serial.print(" With VALUE: ");
//   Serial.println(user_input->password[segment]);
//   EEPROM.update(EEPROM_USER_MEMORY + segment, user_input->password[segment]);
// }

// int read_user_input(int segment) {
//   EEPROM.read(EEPROM_USER_MEMORY + segment);
// }

// void print_password_memory() {
//   Serial.print("{ ");
//   for (int i = 0; i < 3; i++) {
//     Serial.print(EEPROM.read(EEPROM_PASSWORD_MEMORY + i));
//     Serial.print(" ");
//   }
//   Serial.println(" }");
// }

// void print_password_array(password_t *password) {
//   Serial.print("{ ");
//   for (int i = 0; i < 3; i++) {
//     Serial.print(password->password[i]);
//     Serial.print(" ");
//   }
//   Serial.println(" }");
// }

// int *read_password(password_t *password) {
//   int password_length = sizeof(password->password) / sizeof(password->password[0]);
//   // Serial.print("{ ");
//   for (int i = 0; i < password_length; ++i) {
//     password->password[i] = EEPROM.read(EEPROM_PASSWORD_MEMORY + i);
//     // Serial.print(password->password[i]);
//     // Serial.print(" ");
//   }
//   // Serial.println("}");
//   return password->password;
// }


// bool is_password_correct(password_t *user_input) {
//   password_t *password;
//   read_password(password);
//   int password_length = sizeof(password->password) / sizeof(password->password[0]);
//   for (int i = 0; i < password_length; ++i) {
//     if (password->password[i] != user_input->password[i]) return false;
//   }
//   return true;
// }

// void update_password(password_t *user_input) {
//   int password_length = sizeof(user_input->password) / sizeof(user_input->password[0]);
//   if (is_password_correct(user_input)) {
//     Serial.println("This password is existed! Please try again!");
//     notification_system(EXISTED_PASSWORD);
//   } else {
//     for (int i = 0; i < password_length; ++i) {
//       EEPROM.update(EEPROM_PASSWORD_MEMORY + i, user_input->password[i]);
//     }
//     Serial.println("Change password successfully!");
//     notification_system(SUCCEEDED);
//   }
// }


// int read_attempts(password_t *attempt) {
//   attempt->attempts = EEPROM.read(EEPROM_ATTEMPT_MEMORY);
//   return attempt->attempts;
// }

// void update_attempts(password_t *attempt) {
//   EEPROM.update(EEPROM_ATTEMPT_MEMORY, attempt->attempts++);
// }

// void system_locked() {
//   password_t *attempt;
//   read_attempts(attempt);
// }