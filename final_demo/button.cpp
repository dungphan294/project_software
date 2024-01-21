//
// Created by Dung Phan on 1/18/2024.
//

#include "button.h"

bool is_button_pressed(const int button_pin, const int debounce_time) {
    static unsigned long time_of_last_change = 0;
    static int button_state = HIGH;  // initial state: not pressed
    const unsigned long current_time = millis();
    const int new_state = digitalRead(button_pin);

    if (button_state != new_state && (current_time - time_of_last_change > debounce_time)) {
        // a valid change was detected
        time_of_last_change = current_time;    // save time of this change
        button_state = new_state;              // update the button's known state
        if (button_state == LOW) return true;  // if button was pressed, return true
    }
    return false;
}

