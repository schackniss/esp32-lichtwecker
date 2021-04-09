//event/action, if Back-Button is pressed
void backEvent()  {
  switch (page) {
    case 0:       //time and date
      break;
    case 1:       //menu
      page = 0;   //->time and date
      break;
    case 2:       //alarm menu
      page = 1;   //->menu
      line = 0;
      break;
    case 3:       //light
      EEPROM.write(0, licht); //save licht (on/off) to EEPROM
      EEPROM.write(1, red); //save red value to EEPROM
      EEPROM.write(2, green); //save green value to EEPROM
      EEPROM.write(3, blue);  //save blue value to EEPROM
      EEPROM.commit();
      page = 1;   //->menu
      line = 1;
      break;
    case 4:       //Musik
      page = 1;   //->menu
      line = 2;
      break;
    case 5:       //Sonstiges
      page = 1;   //->menu
      line = 3;
      break;
    case 6:       //WeckerMenu 1
      //save alarm values to EEPROM
      EEPROM.write(8, wecker1.active);
      EEPROM.write(13, wecker1.light);
      EEPROM.write(15, wecker1.track);
      EEPROM.commit();
      page = 2;   //->Wecker
      line = 0;
      break;
    case 7:       //WeckerMenu 2
      //save alarm values to EEPROM
      EEPROM.write(16, wecker2.active);
      EEPROM.write(21, wecker2.light);
      EEPROM.write(23, wecker2.track);
      EEPROM.commit();
      page = 2;   //->Wecker
      line = 1;
      break;
    case 8:       //WeckerMenu 3
      //save alarm values to EEPROM
      EEPROM.write(24, wecker3.active);
      EEPROM.write(29, wecker3.light);
      EEPROM.write(31, wecker3.track);
      EEPROM.commit();
      page = 2;   //->Wecker
      line = 2;
      break;
    case 9:       //WeckerMenu 4
      //save alarm values to EEPROM
      EEPROM.write(32, wecker4.active);
      EEPROM.write(37, wecker4.light);
      EEPROM.write(39, wecker4.track);
      EEPROM.commit();
      page = 2;   //->Wecker
      line = 3;
      break;
    case 10:      //WeckerTime 1
      //save alarm values to EEPROM
      EEPROM.write(9, wecker1.hour);
      EEPROM.write(10, wecker1.minute);
      EEPROM.write(11, wecker1.repeat);
      EEPROM.write(12, wecker1.weekday);
      EEPROM.write(40, arrayToInt(wecker1.weekdays)); //convert array to int and save value to EEPROM
      EEPROM.commit();
      page = 6;   //->WeckerMenu 1
      line = 1;
      break;
    case 11:      //WeckerTime 2
      //save alarm values to EEPROM
      EEPROM.write(17, wecker2.hour);
      EEPROM.write(18, wecker2.minute);
      EEPROM.write(19, wecker2.repeat);
      EEPROM.write(20, wecker2.weekday);
      EEPROM.write(41, arrayToInt(wecker2.weekdays)); //convert array to int and save value to EEPROM
      EEPROM.commit();
      page = 7;   //->WeckerMenu 2
      line = 1;
      break;
    case 12:      //WeckerTime 3
      //save alarm values to EEPROM
      EEPROM.write(25, wecker3.hour);
      EEPROM.write(26, wecker3.minute);
      EEPROM.write(27, wecker3.repeat);
      EEPROM.write(28, wecker3.weekday);
      EEPROM.write(42, arrayToInt(wecker3.weekdays)); //convert array to int and save value to EEPROM
      EEPROM.commit();
      page = 8;   //->WeckerMenu 3
      line = 1;
      break;
    case 13:      //WeckerTime 4
      //save alarm values to EEPROM
      EEPROM.write(33, wecker4.hour);
      EEPROM.write(34, wecker4.minute);
      EEPROM.write(35, wecker4.repeat);
      EEPROM.write(36, wecker4.weekday);
      EEPROM.write(43, arrayToInt(wecker4.weekdays)); //convert array to int and save value to EEPROM
      EEPROM.commit();
      page = 9;   //->WeckerMenu 4
      line = 1;
      break;
    case 14:      //TIME DATE SETUP
      page = 5;   //->Sonstiges
      line = 2;
      break;
    case 15:      //Uhrzeit einstellen
      page = 14;   //->Sonstiges
      line = 0;
      break;
    case 16:      //Datum einstellen
      page = 14;   //->Sonstiges
      line = 1;
      break;
    default: break;
  }
}
