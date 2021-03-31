//methods to display menu on LCD

void printTimeSetup() {
  display.setCursor(1,0);
  display.print("Stunde: ");
  printDigits(hrSetup);
  display.setCursor(1,1);
  display.print("Minute: ");
  printDigits(minSetup);
  display.setCursor(1,2);
  display.print("SPEICHERN");
  display.setCursor(0,line);
  display.print(">"); 
}

void printDateSetup() {
  display.setCursor(1,0);
  display.print("Tag: ");
  printDigits(daySetup);
  display.setCursor(1,1);
  display.print("Monat: ");
  printDigits(monthSetup);
  display.setCursor(1,2);
  display.print("Jahr: ");
  display.print(yrSetup);
  display.setCursor(1,3);
  display.print("SPEICHERN");
  display.setCursor(0,line);
  display.print(">");
}

void printTimeDateSetup() {
  display.setCursor(1,0);
  display.print("Uhrzeit einstellen");
  display.setCursor(1,1);
  display.print("Datum einstellen");
  display.setCursor(1,2);
  display.print("NTP Synchronisation");
  display.setCursor(1,3);
  display.print("Zeitzone: UTC+");
  display.print(timeZone);
  display.setCursor(0,line);
  display.print(">");
}

void printWeckerTime(wecker wecker) {
  display.setCursor(1,0);
  display.print("Stunde: ");
  printDigits(wecker.hour);
  display.setCursor(1,1);
  display.print("Minute: ");
  printDigits(wecker.minute);
  display.setCursor(1,2);
  display.print("Wdh: ");
  display.print(wiederholung[wecker.repeat]);
  display.setCursor(1,3);
  display.print("Wochentag: ");
  display.print(wochentag[wecker.weekday]);
  display.setCursor(0,line);
  display.print(">");
}

void printWeckerMenu(wecker wecker) {
  display.setCursor(1,0);
  display.print("Status: ");
  display.print(wecker.active ? "Ein" : "Aus");
  display.setCursor(1,1);
  display.print("Uhrzeit & Tag");
  display.setCursor(1,2);
  display.print("Lichtvorlauf: ");
  display.print(wecker.light);
  display.print("min");
  display.setCursor(1,3);
  display.print("Wecksound: ");
  display.print(wecker.track);
  display.setCursor(0,line);
  display.print(">");
}

void printSonstiges() {
  display.setCursor(1,0);
  display.print("Display: ");
  display.print(displayLicht ? "Ein" : "Aus");
  display.setCursor(1,1);
  display.print("Start WiFi Manager");
  display.setCursor(1,2);
  display.print("Zeit einstellen");
  display.setCursor(1,3);
  display.print("Neustarten");
  display.setCursor(0,line);
  display.print(">");
}

void printMusik() {
  display.setCursor(1,0);
  display.print("Play");
  display.setCursor(1,1);
  display.print("Stop");
  display.setCursor(1,2);
  display.print("Next");
  display.setCursor(1,3);
  display.print("Volume: ");
  display.print(volume);
  display.setCursor(0,line);
  display.print(">");
}

void printLicht() {
  display.setCursor(1,0);
  display.print("Licht: ");
  display.setCursor(8,0);
  display.print(licht ? "Ein" : "Aus");
  display.setCursor(1,1);
  display.print("Rot: ");
  display.setCursor(8,1);
  display.print(red);
  display.setCursor(1,2);
  display.print("Gruen: ");
  display.setCursor(8,2);
  display.print(green);
  display.setCursor(1,3);
  display.print("Blau: ");
  display.setCursor(8,3);
  display.print(blue);
  display.setCursor(0,line);
  display.print(">");
}

void printWecker() {
  display.setCursor(1,0);
  display.print("Wecker 1 |");
  display.print(wecker1.active ? "Ein|" : "Aus|");
  printDigits(wecker1.hour);
  display.print(":");
  printDigits(wecker1.minute);
  display.setCursor(1,1);
  display.print("Wecker 2 |");
  display.print(wecker2.active ? "Ein|" : "Aus|");
  printDigits(wecker2.hour);
  display.print(":");
  printDigits(wecker2.minute);
  display.setCursor(1,2);
  display.print("Wecker 3 |");
  display.print(wecker3.active ? "Ein|" : "Aus|");
  printDigits(wecker3.hour);
  display.print(":");
  printDigits(wecker3.minute);
  display.setCursor(1,3);
  display.print("Wecker 4 |");
  display.print(wecker4.active ? "Ein|" : "Aus|");
  printDigits(wecker4.hour);
  display.print(":");
  printDigits(wecker4.minute);
  display.setCursor(0,line);
  display.print(">");
}

void printMenu()  {
  display.setCursor(1,0);
  display.print("Wecker");
  display.setCursor(1,1);
  display.print("Licht");
  display.setCursor(1,2);
  display.print("Musik");
  display.setCursor(1,3);
  display.print("Sonstiges");
  display.setCursor(0,line);
  display.print(">");
}

void digitalClockDisplay()  {
  //time
  display.setCursor(6,0);
  printDigits(hour());
  display.print(":");
  printDigits(minute());
  display.print(":");
  printDigits(second());
  //line
  display.setCursor(0,1);
  display.print("--------------------");
  //date
  display.setCursor(3,2);
  display.print(wochentag[weekday()]);
  display.print(", ");
  printDigits(day());
  display.print(".");
  printDigits(month());
  display.print(".");
  display.print(year());
}

//utility for digital clock display; prints 0 if needed
void printDigits(int digits)  {
  if (digits < 10) display.print("0");
  display.print(digits);
}
