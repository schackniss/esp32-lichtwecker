#include <Wire.h> //Lib for I2C communication
#include <LiquidCrystal_I2C.h>  //Lib for LCD via I2C https://github.com/johnrickman/LiquidCrystal_I2C
#include <Adafruit_NeoPixel.h>  //Lib for LED Neopixel Matrix Panel https://github.com/adafruit/Adafruit_NeoPixel
#include <WiFiUdp.h>  //Lib for UDP connection
#include <WiFiManager.h> //Lib to setup wifi connection via Smartphone/PC https://github.com/tzapu/WiFiManager
#include <TimeLib.h>  //Time Lib including NTP sync https://github.com/PaulStoffregen/Time
#include <DFRobotDFPlayerMini.h>  //Lib for MP3 Player https://github.com/DFRobot/DFRobotDFPlayerMini
#include <EEPROM.h> //Flash memory lib https://github.com/espressif/arduino-esp32/tree/master/libraries/EEPROM

#define DOWN 26 //define input pin - down button
#define SELECT 23 //define input pin - select button
#define BACK 27 //define input pin - back button
#define UP 25 //define input pin - up button
#define ALARM 18  //define input pin - alarm button
#define LED 19  //define pin to communicate with LED MAtrix Panel
#define SCL 22  //define I2C pin - clock
#define SDA 21  //define I2C pin - data
#define NUMPIXELS 64  //define number of LED pixels
#define EEPROM_SIZE 64  //define number of bytes to access from EEPROM
#define BOUNCE 200  //define debounce time

//datastructure to set different alarm clocks
struct wecker {
  boolean active;
  uint8_t hour; //0...23
  uint8_t minute; //0...59
  uint8_t repeat; //0:einmalig 1:taeglich 2:woechentlich 3:Mo-Fr 4:Wochenende
  uint8_t weekday;  //0:- 1:So 2:Mo ... 7:Sa
  boolean weekdays[7];  //0:So 1:Mo ... 6:Sa
  uint8_t light;  //Lichtvorlaufzeit: 20, 30, 40 min
  uint8_t volume;
  uint8_t track;  //1...Anzahl Tracks
};

//unsigned long stopwatch;  //variable for execution time test

LiquidCrystal_I2C display(0x27,20,4);  //LCD - set the address to 0x27 for a 20 chars and 4 line display
Adafruit_NeoPixel pixels(NUMPIXELS, LED, NEO_GRB + NEO_KHZ800); //LED Neopixel Matrix Panel
WiFiUDP Udp;  //UDP connection
unsigned int localPort = 8888;  // local port to listen for UDP packets

DFRobotDFPlayerMini mp3Player;  //MP3 Player
uint8_t volume = 10;  //MP3 Player Volume 0...30

uint8_t page = 0; //currently display page 0...16
uint8_t line = 0; //current cursor position on page 0...3

uint8_t prevMinute = 0; //value of the previous minute 0...59 -> needed for wakeUpLigt(wecker wecker) and wakeUpTime(wecker wecker)

//Light color
uint8_t red = 0;  //red value of LED Matrix
uint8_t green = 0;  //green value of LED Matrix
uint8_t blue = 0; //blue value of LED Matrix

time_t prevDisplay = 0; //when the digital clock was displayed

const char* wochentag[]={"-", "So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};  //array of weekday names
const char* wiederholung[]={"einmalig", "taeglich", "woechentlich", "Mo-Fr", "Wochenende"}; //array of alarm clock repeat values

const char ntpServerName[] = "europe.pool.ntp.org"; //NTP server adress
int timeZone = 1; //timezone: Central European Time

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

boolean pressed = false;  //value if a button is pressed
boolean prevPressed = false;  //value if a button was previously pressed
boolean pressedSelect = false;  //value if Select button is pressed
boolean pressedBack = false;  //value if Back button is pressed
boolean pressedAlarm = false; //value if Alarm button is pressed
boolean licht = false;  //value if LED Matrix is on or off
boolean displayLicht = true;  //value if LCD Backlight is on or off

boolean fade = false; //value if wakup light is on or off
uint8_t counter = 0;  //counter for wakeup light 0...120

unsigned long oldTime = millis(); //value in ms since last change of Button input value to debounce buttons

wecker wecker1; //alarm clock 1
wecker wecker2; //alarm clock 2
wecker wecker3; //alarm clock 3
wecker wecker4; //alarm clock 4
wecker weckerX; //values of the due alarm clock

uint8_t hrSetup = 0;  //manual time setup - hour
uint8_t minSetup = 0; //manual time setup - minute
uint8_t daySetup = 1; //manual date setup - day
uint8_t monthSetup = 1; //manual date setup - month
int yrSetup = 2021; //manual date setup - year

//ISR: Down-Button
void IRAM_ATTR pressedDOWN() {
  //following if-statement is debouncing the button
  if(millis()-oldTime > BOUNCE) {
    if (page > 0 && line < 3) line++;
    pressed = !pressed;
    oldTime = millis();
  }
}

//ISR: Up-Button
void IRAM_ATTR pressedUP() {
  //following if-statement is debouncing the button
  if(millis()-oldTime > BOUNCE) {
    if (page > 0 && line > 0)  line--;
    pressed = !pressed;
    oldTime = millis();
  }
}

//ISR: Select-Button
void IRAM_ATTR pressedSELECT() {
  //following if-statement is debouncing the button
  if(millis()-oldTime > BOUNCE) {
    pressedSelect = true;
    pressed = !pressed;
    oldTime = millis();
  }
}

//ISR: Back-Button
void IRAM_ATTR pressedBACK() {
  //following if-statement is debouncing the button
  if(millis()-oldTime > BOUNCE) {
    pressedBack = true;
    pressed = !pressed;
    oldTime = millis();
  }
}

//ISR: Alarm-Button
void IRAM_ATTR pressedALARM() {
  //following if-statement is debouncing the button
  if(millis()-oldTime > BOUNCE) {
    pressedAlarm = true;
    pressed = !pressed;
    oldTime = millis();
  }
}

//setup code to run once
void setup() {
  Serial.begin(115200);   //start serial connection to Serial Monitor
  Serial2.begin(9600);    //start serial connection to MP3 Player
  
  input();  //configure pins as input and enable the internal pull-up resistors
  output(); //configure pins as output
  interrupt();  //configure interrupts
  flash();  // initialize and configure EEPROM
  lcd();  //configure LCD
  light();  //read saved LED matrix values from flash and set light
  wlan(); //connect to WiFi
  udp();  //start UDP connection
  ntp();  //set NTP timesync settings
  mp3();  //start MP3 Player
  initWecker(); //read saved alarm clock values from flash

  display.clear();
}

//main code to run repeatedly
void loop() {
  if (pressed != prevPressed) {
    prevPressed = pressed;
    display.clear();
    
    //Select-Button is pressed
    if (pressedSelect)  {
      selectEvent();  //Event, if Select-Button is pressed
      pressedSelect = false;
    }
    
    //Back-Button is pressed
    if (pressedBack)  {
      backEvent();  //Event, if Back-Button is pressed
      pressedBack = false;
    }

    //display menu on LCD
    switch (page) {
      case 1:
        printMenu();
        break;
      case 2:
        printWecker();
        break;
      case 3:
        printLicht();
        break;
      case 4:
        printMusik();
        break;
      case 5:
        printSonstiges();
        break;
      case 6:
        printWeckerMenu(wecker1);
        break;
      case 7:
        printWeckerMenu(wecker2);
        break;
      case 8:
        printWeckerMenu(wecker3);
        break;
      case 9:
        printWeckerMenu(wecker4);
        break;
      case 10:
        printWeckerTime(wecker1);
        break;
      case 11:
        printWeckerTime(wecker2);
        break;
      case 12:
        printWeckerTime(wecker3);
        break;
      case 13:
        printWeckerTime(wecker4);
        break;
      case 14:
        printTimeDateSetup();
        break;
      case 15:
        printTimeSetup();
        break;
      case 16:
        printDateSetup();
        break;
      default: break;
    }
  }

  //display current time and date on LCD, if the time is set, displayed page is 0 and 1 sec passed since last time-update
  if (timeStatus() != timeNotSet && page == 0) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();
    }
  }

  //Alarm-Button is pressed
  if (pressedAlarm) {
    alarmOff(); //turn off alarm (light and music)
    pressedAlarm = false;
  }

  //wake-up light
  if (fade) {
    sunrise();  //wake-up light as sunrise
  }

  //check, if a alarm or wake-up light is due 
  if (prevMinute != minute()) {
    prevMinute = minute();
    if (wakeUpLight(wecker2) || wakeUpLight(wecker1) || wakeUpLight(wecker3) || wakeUpLight(wecker4))  {
      fade = true;
    }
    
    if (wakeUpTime(wecker1) || wakeUpTime(wecker2) || wakeUpTime(wecker3) || wakeUpTime(wecker4)) {
      wakeUp();
    }
  }

  //execution time test
  //Serial.println(micros()-stopwatch);
  //stopwatch = micros();
}
