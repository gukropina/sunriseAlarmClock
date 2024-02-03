/*
  Turns on an RGB strip at a set time, then turns it off.
  Displays the time on an OLED screen (using a 24 hour clock)
  test: using Arduino Uno
        started at 6:14:38 on the arduino, and the clock on my computer was 6:14:40. They are about 2 seconds apart
        at that time. They were 9 seconds off by 8:06:18. So in about 2 hours, it drifted to being 7 more seconds slow 
        (the computer clock was 9-10 seconds faster than what the arduino was saying, so the arduino clock runs slower)
        That means that about every day, it would be 84 seconds, or about a minute and a third slower. 
        So, I could try to compensate if I want. Every hour, I could add 3-4 seconds, making the clock run 
        a little faster, and a little closer to real time. (right now, I need to add 3.5 seconds, if my math is right)

*/

#define RGB_LED_Red 6
#define RGB_LED_Green 5
#define RGB_LeD_Blue 3
#define SERIAL_DEBUG 0      //if serial debug is 1, you will send information to the serial port

#define LIGHT_ON_DELAY 200 //this is the delay that the code takes when bringing the lights on from nothing
                           //this delay will happen 765 times when turning on the lights (one for each color,
                           //and each color goes from 1 to 255) With it set to 100, it will take 7.65 seconds to turn
                           //all the way on, going through each color (red, green, then blue)

int SECONDS = 59;
int MINUTES = 29;
int HOURS = 21;

//this is when the alarm turns on
int ALARM_HOURS = 8;
int ALARM_MINUTES = 00;

//this is when the alarm turns off
int ALARM_OFF_HOURS = 8;
int ALARM_OFF_MINUTES = 15;

//things to keep track of time
#define ONE_SECOND 1000
unsigned long TIME_CHECK = 0;
#define SECONDS_TO_ADD_EACH_HOUR 3   //from empirical testing, the ardiuno runs about 3-4 seconds slower per hour than 
                                     //my PC's clock. So, I add 3 seconds every hour to the time to try to be more
                                     //accurate


//OLED stuff
  #include "ssd1306.h"
  #include "nano_gfx.h"


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  ssd1306_128x64_i2c_init();
  pinMode(RGB_LED_Red, OUTPUT);
  pinMode(RGB_LED_Green, OUTPUT);
  pinMode(RGB_LeD_Blue, OUTPUT);
  
  #if SERIAL_DEBUG
  //if you are doing serial debugging, turn on Serial
  Serial.begin(115200);
  Serial.println("Hi");
  #endif
}

// the loop function runs over and over again forever
void loop() {

  if((millis() - TIME_CHECK) > ONE_SECOND){
    //if it's been one second since the last check, add one to seconds
    int update_clock = 0;
    SECONDS++;

    if(SECONDS==60){
      SECONDS = SECONDS - 60;
      MINUTES++;
      update_clock = 1;
    }
    if(MINUTES==60){
      MINUTES=0;
      HOURS++;
      SECONDS = SECONDS_TO_ADD_EACH_HOUR;  //add a few seconds, since the arduino clock runs slow
      }
    if(HOURS==24){
      HOURS=0;
      } 

    //check if you need to send information to Serial port
    #if SERIAL_DEBUG
    Serial.print("Time: ");
    Serial.print(HOURS);
    Serial.print(":");
    Serial.print(MINUTES);
    Serial.print(":");
    Serial.println(SECONDS);
    #endif

    if(update_clock == 1){  
      //now, update the OLED
      //update screen if it's been a second
      ssd1306_clearScreen( );
      ssd1306_normalMode();
      ssd1306_setFixedFont(ssd1306xled_font8x16); //set font
      delay(5);    //give the screen some time to catch up
      if(MINUTES < 10){
        //if minutes are less than 10, add a 0
        String Time_STRING = String(int(HOURS)) + ":0" + String(int(MINUTES));
        ssd1306_printFixed(0,  0, Time_STRING.c_str(), STYLE_BOLD);
      }
      else{
        //if minutes are greater than 10, don't add a 0
        String Time_STRING = String(int(HOURS)) + ":" + String(int(MINUTES));
        ssd1306_printFixed(0,  0, Time_STRING.c_str(), STYLE_BOLD);
      }


      //check the alarm
      if( (ALARM_HOURS == HOURS) && (ALARM_MINUTES == MINUTES) ){
        //if the HOURS and MINUTES are correct, turn on the light!
        turn_on_lights();
      }
      //check to turn the alarm off
      if( (ALARM_OFF_HOURS == HOURS) && (ALARM_OFF_MINUTES == MINUTES) ){
        //turn off the light when it's programmed to turn off
        turn_off_lights();
      }
    }

    //reset your time checker
    TIME_CHECK = TIME_CHECK + ONE_SECOND;
  }
}

/*
 * turn_on_lights f(x)
 * This function turns on the lights
 */

 void turn_on_lights( void ){
  for (int i = 0; i <= 255; i++) {
    analogWrite(RGB_LED_Red, i);
    delay(LIGHT_ON_DELAY);
  }
  for (int i = 0; i <= 255; i++) {
    analogWrite(RGB_LED_Green, i);
    delay(LIGHT_ON_DELAY);
  }
  for (int i = 0; i <= 255; i++) {
    analogWrite(RGB_LeD_Blue, i);
    delay(LIGHT_ON_DELAY);
  }
  
  digitalWrite(RGB_LED_Red, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(RGB_LED_Green, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(RGB_LeD_Blue, HIGH);   // turn the LED on (HIGH is the voltage level) 
 }

 /*
 * turn_off_lights f(x)
 * This function turns off the lights
 */

 void turn_off_lights( void ){
  digitalWrite(RGB_LED_Red, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(RGB_LED_Green, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(RGB_LeD_Blue, LOW);   // turn the LED on (HIGH is the voltage level)   
 }
