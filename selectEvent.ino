//event/action, if Select-Button is pressed
void selectEvent() {
  //time and date
  if (page == 0)  {
    page = 1;
    line = 0;
    return;
  }
  
  //menu
  if (page == 1)  {
    switch(line)  {
      case 0: page = 2; break;
      case 1: page = 3; break;
      case 2: page = 4; break;
      case 3: page = 5; break;
      default:  break;
    }
    line = 0;
    return;
  }

  //alarm menu
  if (page == 2)  {
    switch(line)  {
      case 0: page = 6; break;
      case 1: page = 7; break;
      case 2: page = 8; break;
      case 3: page = 9; break;
      default: break;
    }
    line = 0;
    return;
  }
  
  //light
  if (page == 3)  {
    switch(line)  {
      case 0:
        licht = !licht;
        break;
      case 1:
        if (red >= 250)  red = 0;
        else red += 10;
        break;
      case 2:
        if (green >= 250)  green = 0;
        else green += 10;
        break;
      case 3:
        if (blue >= 250)  blue = 0;
        else blue += 10;
        break;
    }
    setLight();
    return;
  }
  
  //music
  if (page == 4)  {
    switch(line)  {
      case 0:
        mp3Player.play(1);  //Play the first mp3
        break;
      case 1:
        mp3Player.pause();  //pause the mp3
        break;
      case 2:
        mp3Player.next();  //Play next mp3
        break;
      case 3:
        if (volume >= 30) volume = 0;
        else  volume += 5;
        mp3Player.volume(volume);  //Set volume. From 0 to 30
        break;
    }
    return;
  }
  
  //Sosnstiges
  if (page == 5)  {
    switch(line)  {
      case 0:
        //turn LCD Backlight on/off
        displayLicht = !displayLicht;
        if(displayLicht) display.backlight();
        if(!displayLicht) display.noBacklight();
        break;
      case 1:
        //start wifi manager to connect with a different wifi
        wifiManager();
        break;
      case 2:
        page = 14;
        line = 0;
        break;
      case 3:
        //restart microcontroller
        ESP.restart();
        break;
      default: break;
    }
    return;
  }
  
  //WeckerMenu 1
  if (page == 6)  {
    switch(line)  {
      case 0:
        wecker1.active = !wecker1.active;
        break;
      case 1:
        page = 10;
        line = 0;
        break;
      case 2:
        if (wecker1.light >= 40) wecker1.light = 20;
        else wecker1.light += 10;
        break;
      case 3:
        if (wecker1.track >= mp3Player.readFileCounts()) wecker1.track = 1;
        else  {
          wecker1.track++;
          //mp3Player.play(wecker1.track);
        }
        break;
    }
    return;
  }
  
  //WeckerMenu 2
  if (page == 7)  {
    switch(line)  {
      case 0:
        wecker2.active = !wecker2.active;
        break;
      case 1:
        page = 11;
        line = 0;
        break;
      case 2:
        if (wecker2.light >= 40) wecker2.light = 20;
        else wecker2.light += 10;
        break;
      case 3:
        if (wecker2.track >= mp3Player.readFileCounts()) wecker2.track = 1;
        else  {
          wecker2.track++;
          //mp3Player.play(wecker2.track);
        }
        break;
    }
    return;
  }
  
  //WeckerMenu 3
  if (page == 8)  {
    switch(line)  {
      case 0:
        wecker3.active = !wecker3.active;
        break;
      case 1:
        page = 12;
        line = 0;
        break;
      case 2:
        if (wecker3.light >= 40) wecker3.light = 20;
        else wecker3.light += 10;
        break;
      case 3:
        if (wecker3.track >= mp3Player.readFileCounts()) wecker3.track = 1;
        else  {
          wecker3.track++;
        }
        break;
    }
    return;
  }
  
  //WeckerMenu 4
  if (page == 9)  {
    switch(line)  {
      case 0:
        wecker4.active = !wecker4.active;
        break;
      case 1:
        page = 13;
        line = 0;
        break;
      case 2:
        if (wecker4.light >= 40) wecker4.light = 20;
        else wecker4.light += 10;
        break;
      case 3:
        if (wecker4.track >= mp3Player.readFileCounts()) wecker4.track = 1;
        else  {
          wecker4.track++;
        }
        break;
    }
    return;
  }
  
  //WeckerTime 1
  if (page == 10)  {
    switch(line)  {
      case 0:
        if (wecker1.hour >= 23) wecker1.hour = 0;
        else wecker1.hour++;
        break;
      case 1:
        if (wecker1.minute >= 59) wecker1.minute = 0;
        else wecker1.minute++;
        break;
      case 2:
        if (wecker1.repeat >= 4) wecker1.repeat = 1;
        else  {
          wecker1.repeat++;
        }
        if (wecker1.repeat == 0 || wecker1.repeat == 2) {
          wecker1.weekday = EEPROM.read(12);
          if (wecker1.weekday == 0) wecker1.weekday = 2;
          for (int i = 0; i < 7; i++) {
            if (i == wecker1.weekday-1) wecker1.weekdays[i] = true;
            else wecker1.weekdays[i] = false;
          }
        }
        if (wecker1.repeat == 1)  {
          wecker1.weekday = 0;
          for (int i = 0; i < 7; i++) wecker1.weekdays[i] = true;
        }
        if (wecker1.repeat == 3)  {
          wecker1.weekday = 0;
          for (int i = 0; i < 7; i++) {
            if (i == 0 || i == 6) wecker1.weekdays[i] = false;
            else wecker1.weekdays[i] = true;
          }
        }
        if (wecker1.repeat == 4)  {
          wecker1.weekday = 0;
          for (int i = 0; i < 7; i++) {
            if (i == 0 || i == 6) wecker1.weekdays[i] = true;
            else wecker1.weekdays[i] = false;
          }
        }
        break;
      case 3:
        if (wecker1.repeat == 0 || wecker1.repeat == 2) {
          for (int i = 0; i < 7; i++) wecker1.weekdays[i] = false;
          if (wecker1.weekday >= 7) wecker1.weekday = 1;
          else  {
            wecker1.weekday++;
          }
          wecker1.weekdays[wecker1.weekday-1] = true;
        }
        break;
    }
    return;
  }
  
  //WeckerTime 2
  if (page == 11)  {
    switch(line)  {
      case 0:
        if (wecker2.hour >= 23) wecker2.hour = 0;
        else wecker2.hour++;
        break;
      case 1:
        if (wecker2.minute >= 59) wecker2.minute = 0;
        else wecker2.minute++;
        break;
      case 2:
        if (wecker2.repeat >= 4) wecker2.repeat = 1;
        else  {
          wecker2.repeat++;
        }
        if (wecker2.repeat == 0 || wecker2.repeat == 2) {
          wecker2.weekday = EEPROM.read(12);
          if (wecker2.weekday == 0) wecker2.weekday = 2;
          for (int i = 0; i < 7; i++) {
            if (i == wecker2.weekday-1) wecker2.weekdays[i] = true;
            else wecker2.weekdays[i] = false;
          }
        }
        if (wecker2.repeat == 1)  {
          wecker2.weekday = 0;
          for (int i = 0; i < 7; i++) wecker2.weekdays[i] = true;
        }
        if (wecker2.repeat == 3)  {
          wecker2.weekday = 0;
          for (int i = 0; i < 7; i++) {
            if (i == 0 || i == 6) wecker2.weekdays[i] = false;
            else wecker2.weekdays[i] = true;
          }
        }
        if (wecker2.repeat == 4)  {
          wecker2.weekday = 0;
          for (int i = 0; i < 7; i++) {
            if (i == 0 || i == 6) wecker2.weekdays[i] = true;
            else wecker2.weekdays[i] = false;
          }
        }
        break;
      case 3:
        if (wecker2.repeat == 0 || wecker2.repeat == 2) {
          for (int i = 0; i < 7; i++) wecker2.weekdays[i] = false;
          if (wecker2.weekday >= 7) wecker2.weekday = 1;
          else  {
            wecker2.weekday++;
          }
          wecker2.weekdays[wecker2.weekday-1] = true;
        }
        break;
    }
    return;
  }
  
  //WeckerTime 3
  if (page == 12)  {
    switch(line)  {
      case 0:
        if (wecker3.hour >= 23) wecker3.hour = 0;
        else wecker3.hour++;
        break;
      case 1:
        if (wecker3.minute >= 59) wecker3.minute = 0;
        else wecker3.minute++;
        break;
      case 2:
        if (wecker3.repeat >= 4) wecker3.repeat = 1;
        else  {
          wecker3.repeat++;
        }
        if (wecker3.repeat == 0 || wecker3.repeat == 2) {
          wecker3.weekday = EEPROM.read(12);
          if (wecker3.weekday == 0) wecker3.weekday = 2;
          for (int i = 0; i < 7; i++) {
            if (i == wecker3.weekday-1) wecker3.weekdays[i] = true;
            else wecker3.weekdays[i] = false;
          }
        }
        if (wecker3.repeat == 1)  {
          wecker3.weekday = 0;
          for (int i = 0; i < 7; i++) wecker3.weekdays[i] = true;
        }
        if (wecker3.repeat == 3)  {
          wecker3.weekday = 0;
          for (int i = 0; i < 7; i++) {
            if (i == 0 || i == 6) wecker3.weekdays[i] = false;
            else wecker3.weekdays[i] = true;
          }
        }
        if (wecker3.repeat == 4)  {
          wecker3.weekday = 0;
          for (int i = 0; i < 7; i++) {
            if (i == 0 || i == 6) wecker2.weekdays[i] = true;
            else wecker2.weekdays[i] = false;
          }
        }
        break;
      case 3:
        if (wecker3.repeat == 0 || wecker3.repeat == 2) {
          for (int i = 0; i < 7; i++) wecker3.weekdays[i] = false;
          if (wecker3.weekday >= 7) wecker3.weekday = 1;
          else  {
            wecker3.weekday++;
          }
          wecker3.weekdays[wecker3.weekday-1] = true;
        }
        break;
    }
    return;
  }
  
  //WeckerTime 4
  if (page == 13)  {
    switch(line)  {
      case 0:
        if (wecker4.hour >= 23) wecker4.hour = 0;
        else wecker4.hour++;
        break;
      case 1:
        if (wecker4.minute >= 59) wecker4.minute = 0;
        else wecker4.minute++;
        break;
      case 2:
        if (wecker4.repeat >= 4) wecker4.repeat = 1;
        else  {
          wecker4.repeat++;
        }
        if (wecker4.repeat == 0 || wecker4.repeat == 2) {
          wecker4.weekday = EEPROM.read(12);
          if (wecker4.weekday == 0) wecker4.weekday = 2;
          for (int i = 0; i < 7; i++) {
            if (i == wecker4.weekday-1) wecker4.weekdays[i] = true;
            else wecker4.weekdays[i] = false;
          }
        }
        if (wecker4.repeat == 1)  {
          wecker4.weekday = 0;
          for (int i = 0; i < 7; i++) wecker4.weekdays[i] = true;
        }
        if (wecker4.repeat == 3)  {
          wecker3.weekday = 0;
          for (int i = 0; i < 7; i++) {
            if (i == 0 || i == 6) wecker4.weekdays[i] = false;
            else wecker4.weekdays[i] = true;
          }
        }
        if (wecker4.repeat == 4)  {
          wecker4.weekday = 0;
          for (int i = 0; i < 7; i++) {
            if (i == 0 || i == 6) wecker4.weekdays[i] = true;
            else wecker4.weekdays[i] = false;
          }
        }
        break;
      case 3:
        if (wecker4.repeat == 0 || wecker4.repeat == 2) {
          for (int i = 0; i < 7; i++) wecker4.weekdays[i] = false;
          if (wecker4.weekday >= 7) wecker4.weekday = 1;
          else  {
            wecker4.weekday++;
          }
          wecker4.weekdays[wecker4.weekday-1] = true;
        }
        break;
    }
    return;
  }
  
  //DATE TIME SETUP
  if (page == 14) {
    switch(line)  {
      case 0:
        page = 15;
        line = 0;
        break;
      case 1:
        page = 16;
        line = 0;
        break;
      case 2:
        setTime(getNtpTime());
        page = 0;
        line = 0;
        break;
      case 3:
        if (timeZone >= 2) timeZone = 1;
        else timeZone++;
        setTime(getNtpTime());
        EEPROM.write(4, timeZone);
        EEPROM.commit();
        break;
      default: break;
    }
    return;
  }
  
  //Uhrzeit einstellen
  if (page == 15) {
    switch(line)  {
      case 0:
        if (hrSetup >= 23) hrSetup = 0;
        else hrSetup++;
        break;
      case 1:
        if (minSetup >= 23) minSetup = 0;
        else minSetup++;
        break;
      case 2:
        setTime(hrSetup, minSetup, 0, day(), month(), year());
        page = 14;   //->Sonstiges
        line = 0;
      default: break;
    }
    return;
  }

  //Datum einstellen
  if (page == 16) {
    switch(line)  {
      case 0:
        if (daySetup >= 31) daySetup = 1;
        else daySetup++;
        break;
      case 1:
        if (monthSetup >= 22) monthSetup = 1;
        else monthSetup++;
        break;
      case 2:
        if (yrSetup >= 2030) yrSetup = 2021;
        else yrSetup++;
        break;
      case 3:
        setTime(hour(), minute(), second(), daySetup, monthSetup, yrSetup);
        page = 14;   //->Sonstiges
        line = 1;
      default: break;
    }
    return;
  }
}
