//check, if alarm is due
boolean wakeUpTime(wecker wecker) {
  if (wecker.active && wecker.weekdays[weekday()-1]
      && wecker.hour == hour() && wecker.minute == minute())  return true;
  return false;
}

//check, if wake-up light needs to start; writes values of next due alarm in weckerX
boolean wakeUpLight(wecker wecker) {
  int minutes = (wecker.hour * 60) + wecker.minute - wecker.light;
  if (minutes < 0)  {
    if (wecker.active && wecker.weekdays[weekday()-2]
        && 23 == hour() && (60 + minutes) == minute())  {
          weckerX = wecker;
          return true;
        }
  }
  if (minutes >= 0) {
    if (wecker.active && wecker.weekdays[weekday()-1]
        && (minutes / 60) == hour() && (minutes % 60) == minute())  {
          weckerX = wecker;
          return true;
        }
  }
  return false;
}

//wake-up alarm (light, music)
void wakeUp() {
  fade = false;
  counter = 0;

  setLight(255, 255, 255);
  
  mp3Player.volume(30);
  mp3Player.play(weckerX.track);
}

//wake-up light
void sunrise()  {
  static time_t prevSunrise = 0;
  static uint8_t r = 0;
  static uint8_t g = 0;
  static uint8_t b = 0;
  
  if (((now() - prevSunrise) >= (weckerX.light / 2))) {
    prevSunrise = now();
    Serial.println(now());
  
    if (counter < 120) {
      r += 2;
      if (counter < 5)   g = r * 0.1;
      if (counter >= 5  && counter < 10)  g = r * 0.2;
      if (counter >= 10 && counter < 15)  g = r * 0.3;
      if (counter >= 15 && counter < 20)  g = r * 0.4;
      if (counter >= 20 && counter < 25)  g = r * 0.5;
      if (counter >= 25 && counter < 30)  g = r * 0.6;
      if (counter >= 30 && counter < 35)  g = r * 0.7;
      if (counter >= 35 && counter < 40)  g = r * 0.8;
      if (counter >= 40 && counter < 45)  g = r * 0.9;
      if (counter >= 45) g = r;
      if (counter >= 50 && counter < 100) b += 4;
      if (counter >= 100) b = r;
    }
    
    setLight(r, g, b);
    counter++;
    if (counter >= 120) {
      counter = 0;
      r = 0;
      g = 0;
      b = 0;
      fade = false;
    }
  }
}

//turn alarm off; stops music and sets light to original values
void alarmOff() {
  setLight();
  mp3Player.pause();
}
