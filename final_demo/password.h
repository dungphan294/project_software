//
// Created by Dung Phan on 1/15/2024.
//
#ifndef DEMO_PASSWORD_H
#define DEMO_PASSWORD_H

#include "Arduino.h"
#include "EEPROM.h"
#include "variables.h"
// // #include "variables.h"
// typedef struct {
//     int password[3];
//     int attempts;  // How many times did user check password
// } password_t;
// const int EEPROM_USER_MEMORY = 0;
// const int EEPROM_7_SEGMENT = 25;
// const int EEPROM_ATTEMPT_MEMORY = 50;
// const int EEPROM_PASSWORD_MEMORY = 100;

///
/// \param user_input
/// \param segment
void save_user_input(password_t *user_input, int segment);

///
/// \param segment
/// \return
int read_user_input(int segment);

///
void print_password_memory();

///
/// \param password
void print_password_array(password_t *password);

///
/// \param password
/// \return
int *read_password(password_t *password);

///
/// \param user_input
/// \return
bool is_password_correct(password_t *user_input);

///
/// \param user_input
void update_password(password_t *user_input);

///
/// \param attempt
/// \return
int read_attempts(password_t *attempt);

///
/// \param attempt
void update_attempts(password_t *attempt);

void system_locked();

#endif //DEMO_PASSWORD_H
