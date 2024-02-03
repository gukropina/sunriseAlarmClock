/*
  Turns on an RGB strip at a set time, then turns it off.
  Displays the time on an OLED screen (using a 24 hour clock)

*/

#define RGB_LED_Red 6
#define RGB_LED_Green 5
#define RGB_LeD_Blue 3

int SECONDS = 55;
int MINUTES = 29;
int HOURS = 7;

//this is when the alarm turns on
int ALARM_HOURS = 7;
int ALARM_MINUTES = 30;

//this is when the alarm turns off
int ALARM_OFF_HOURS = 7;
int ALARM_OFF_MINUTES = 50;

int LIGHTS_ON = 0;  //lights start off


//things to keep track of time
#define ONE_SECOND 1000
unsigned long TIME_CHECK = 0;


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
      }
    if(HOURS==24){
      HOURS=1;
      } 

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
        //if the HOURS, MINUTES, and AM/PM are correct, turn on the light!
        turn_on_lights();
      }
      if( (ALARM_OFF_HOURS == HOURS) && (ALARM_OFF_MINUTES == MINUTES) ){
        //turn off the light an hour later
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
