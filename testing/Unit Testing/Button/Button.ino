#define LED_PIN 13
#define BUTTON 2
void setup()
{
   pinMode(LED_PIN, OUTPUT);
   pinMode(BUTTON,INPUT_PULLUP);
   Serial.begin(9600);
}

void loop()
{
  if(digitalRead(BUTTON) == LOW){
   Serial.println("Press Button!");
   digitalWrite(LED_PIN, HIGH);
   delay(500); // Wait for 1000 millisecond(s)
  }
  else{
   Serial.println("Not press button");
   digitalWrite(LED_PIN,LOW);
   delay(500);
  }
}