/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

*/

#define RGB_LED_Red 6
#define RGB_LED_Green 5
#define RGB_LeD_Blue 3


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RGB_LED_Red, OUTPUT);
  pinMode(RGB_LED_Green, OUTPUT);
  pinMode(RGB_LeD_Blue, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(RGB_LED_Red, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(RGB_LED_Green, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(RGB_LeD_Blue, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(RGB_LED_Red, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(RGB_LED_Green, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(RGB_LeD_Blue, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
}
