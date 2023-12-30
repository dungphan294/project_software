# project_software
Project Software - Saxion
Testing 

Duy code
Buzzer and led

const int BUZZER_PIN = 12;
const int led_pin = 13;
const int button = 2; 
int INTERVAL = 500;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(BUZZER_PIN,OUTPUT);
}

bool is_button_pressed(int debounce_time) {
    static unsigned long time_of_last_change = 0;
    static int button_state = HIGH;    // initial state: not presset
    const unsigned long current_time = millis();
    const int new_state = digitalRead(button);

    if (button_state != new_state && (current_time - time_of_last_change > debounce_time)) {
        time_of_last_change = current_time;         // save time of this change
        button_state = new_state;                   // update the button's known state
        if (button_state == LOW) return true;       // if button was pressed, return true
    }

    return false;
}

void blink_led(int interval) {
    static bool LED_is_on = false;
    static unsigned long time_of_last_change = 0;
    const unsigned long current_time = millis();
    static float count = 0;
  Serial.print(count);
  if(count < 3) {

    if (current_time - time_of_last_change > interval) {
        time_of_last_change = current_time;
        LED_is_on = !LED_is_on;
      if(LED_is_on){ 
        digitalWrite(led_pin,HIGH);
        tone(BUZZER_PIN, 1000);
      }
      else{ 
        digitalWrite(led_pin,LOW);
        noTone(BUZZER_PIN);
      }
      count = count + 0.5;
   }
  }else digitalWrite(led_pin,LOW);
 }

void loop() {
  static int button_press_count = 0;
  static bool is_led_blinking = false;
  
  if (is_button_pressed(50)) {
    button_press_count++;
    if (button_press_count % 2 == 1) {
     is_led_blinking = true;
    } 
  }
  
  if(is_led_blinking == true) blink_led(INTERVAL);
 }
