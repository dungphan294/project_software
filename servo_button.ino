#include <Servo.h>

Servo myServo;              // create servo object to control a servo
const int BUTTON_PIN = 1;  // Pin number where the button is connected
const int servoPin = 0;     // Pin number where the servo signal wire is connected
int button_press_count = 0;
int DEBOUNCE_TIME = 50;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  myServo.attach(servoPin);
}

bool isButtonPressed(int BUTTON_PIN) {
  static unsigned long timeOfLastChange = 0;
  static int buttonState = HIGH;
  const unsigned long currentTime = millis();
  const int newState = digitalRead(BUTTON_PIN);

  if (buttonState != newState && (currentTime - timeOfLastChange > DEBOUNCE_TIME)) {
    timeOfLastChange = currentTime;
    buttonState = newState;
    return (buttonState == LOW);
  }
  return false;
}

void rotateServo(bool rotate) {
  if (rotate) {
    myServo.write(90);
    Serial.print("Servo Angle: ");
    Serial.println(90);
  } else {
    myServo.write(0);
    Serial.print("Servo Angle: ");
    Serial.println(0);
  }
}

void handleButtonPress() {
  static bool servo_rotate = false;  // current state of the servo
  if (isButtonPressed(BUTTON_PIN)) {
    servo_rotate = !servo_rotate;
    if (servo_rotate) {
      Serial.println("The button is pressed");
    }
    rotateServo(servo_rotate);
  }
}

void loop() {
  handleButtonPress();
  delay(1000);
}