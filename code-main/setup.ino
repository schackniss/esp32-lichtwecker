//configure pins as input and enable the internal pull-up resistor
void input() {
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(SELECT, INPUT_PULLUP);
  pinMode(BACK, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(ALARM, INPUT_PULLUP);
}

//configure pins as output
void output() {
  pinMode(LED, OUTPUT);
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);
}

//configure interrupts
void interrupt() {
  attachInterrupt(DOWN, pressedDOWN, FALLING);
  attachInterrupt(UP, pressedUP, FALLING);
  attachInterrupt(SELECT, pressedSELECT, FALLING);
  attachInterrupt(BACK, pressedBACK, FALLING);
  attachInterrupt(ALARM, pressedALARM, FALLING);
}

//udp connection for ntp
void udp()  {
  Serial.println("Starting UDP...");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(localPort);
}

// initialize the lcd 
void lcd()  {
  display.init();
  display.backlight();
  display.setCursor(0,0);
  display.print("Starting clock...");
}

//connect to WiFi (uses wifi manager)
void wlan() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  WiFiManager wm;

  display.setCursor(0,1);
  display.print("Bei neuem WLAN mit");
  display.setCursor(1,2);
  display.print("AP >Lichtwecker");
  display.setCursor(1,3);
  display.print("Setup< verbinden!");

  //reset settings - wipe credentials for testing
  //wm.resetSettings();

  boolean res;
  res = wm.autoConnect("Lichtwecker Setup");

  if(!res) {
      Serial.println("Failed to connect");
      // ESP.restart();
      page = 14;
      line = 0;
      prevPressed = !pressed;
  } 
  else {
      //if you get here you have connected to the WiFi    
      Serial.println("connected to wifi");
  }
}

//on demand wifi manager (can be called from Sonstiges menu page)
void wifiManager()  {
  WiFiManager wm;    

  //reset settings - for testing
  //wifiManager.resetSettings();

  // set configportal timeout
  wm.setConfigPortalTimeout(120);

  if (!wm.startConfigPortal("Lichtwecker Setup")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected to wifi");
}

//initialize EEPROM
void flash()  {
  EEPROM.begin(EEPROM_SIZE);
}

//initial ntp time synch; set synch interval
void ntp()  {
  timeZone = EEPROM.read(4);
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
  setSyncInterval(10800);  //NTP Sync every 3 hours (time in seconds)
}

//setup mp3 player
void mp3()  {
  if (!mp3Player.begin(Serial2)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }
  Serial.println(F("DFPlayer Mini online."));

  mp3Player.volume(volume);  //Set volume value. From 0 to 30
}

//read light values from EEPROM and set light
void light()  {
  licht = EEPROM.read(0);
  red = EEPROM.read(1);
  green = EEPROM.read(2);
  blue = EEPROM.read(3);
  
  setLight();
}

//read alarm clock values from EEPROM
void initWecker() {
  wecker1.active = EEPROM.read(8);
  wecker1.hour =EEPROM.read(9);
  wecker1.minute =EEPROM.read(10);
  wecker1.repeat =EEPROM.read(11);
  wecker1.weekday =EEPROM.read(12);
  wecker1.light =EEPROM.read(13);
//  wecker1.volume =EEPROM.read(14);
  wecker1.track =EEPROM.read(15);
  intToArray(EEPROM.read(40), wecker1.weekdays);

  wecker2.active = EEPROM.read(16);
  wecker2.hour =EEPROM.read(17);
  wecker2.minute =EEPROM.read(18);
  wecker2.repeat =EEPROM.read(19);
  wecker2.weekday =EEPROM.read(20);
  wecker2.light =EEPROM.read(21);
//  wecker2.volume =EEPROM.read(22);
  wecker2.track =EEPROM.read(23);
  intToArray(EEPROM.read(41), wecker2.weekdays);

  wecker3.active = EEPROM.read(24);
  wecker3.hour =EEPROM.read(25);
  wecker3.minute =EEPROM.read(26);
  wecker3.repeat =EEPROM.read(27);
  wecker3.weekday =EEPROM.read(28);
  wecker3.light =EEPROM.read(29);
//  wecker3.volume =EEPROM.read(30);
  wecker3.track =EEPROM.read(31);
  intToArray(EEPROM.read(42), wecker3.weekdays);

  wecker4.active = EEPROM.read(32);
  wecker4.hour =EEPROM.read(33);
  wecker4.minute =EEPROM.read(34);
  wecker4.repeat =EEPROM.read(35);
  wecker4.weekday =EEPROM.read(36);
  wecker4.light =EEPROM.read(37);
//  wecker4.volume =EEPROM.read(38);
  wecker4.track =EEPROM.read(39);
  intToArray(EEPROM.read(43), wecker4.weekdays);
}
