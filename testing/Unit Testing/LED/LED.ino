// TESTING LED
const int GREEN_LED = 12;
const int RED_LED = 13;

void setup()
{
  pinMode(GREEN_LED, OUTPUT);  
  pinMode(RED_LED, OUTPUT);
}

void loop()
{
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}