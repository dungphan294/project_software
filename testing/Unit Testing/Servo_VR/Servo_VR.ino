#include <Servo.h>

Servo SERVO;

int potentiometer = A0;
void setup() {
    Serial.begin(9600);
    SERVO.attach(2);
    pinMode(potentiometer, INPUT);
}

void loop() {
    int potvalue = analogRead(potentiometer);
    Serial.println(potvalue);
    int value= map(potvalue, 0, 1023, 0, 180);
    SERVO.write(value);
    delay(100);
}


