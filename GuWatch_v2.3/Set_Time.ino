void settime () {
  uView.setFontType(0);
  uView.setCursor(0,  0);
  uView.print("Set Time");
  uView.setCursor(0,  12);    //  set time 
  if(HOUR >= 23) HOUR = 23;       if(HOUR <= 0) HOUR = 0;    
  if(HOUR >= 0 && HOUR <= 9 )     uView.print("0");  
  uView.print(HOUR);
  uView.print(":");
  if(MINUTE >= 59) MINUTE = 59;   if(MINUTE <= 0) MINUTE = 0;
  if(MINUTE >= 0 && MINUTE <= 9 ) uView.print("0");
  uView.print(MINUTE);
  uView.print(":");
  if(SECOND >= 59) SECOND = 59;   if(SECOND <= 0) SECOND = 0;
  if(SECOND >= 0 && SECOND <= 9 ) uView.print("0");
  uView.print(SECOND);
  uView.setCursor(0,  28);    //  set dat
  if(DAY >= 31) DAY = 31;         if(DAY <= 0) DAY = 0;
  if(DAY >= 0 && DAY <= 9 ) uView.print("0");
  uView.print(DAY);
  uView.print("/");
  if(MONTH >= 12) MONTH = 12;     if(MONTH <= 0) MONTH = 0;
  if(MONTH >= 0 && MONTH <= 9 ) uView.print("0");
  uView.print(MONTH);
  uView.print("/");
  uView.print(YEAR);
//  uView.display();

  state_push = digitalRead(push);
  if (state_push == 0)  { // next step
    delay(DEBOUNCE);
    stepset++;
  }
  if(stepset == 7)  {   // when stepset is 6 then out mode set time
    EEPROM.write(ee_hour, HOUR);
    EEPROM.write(ee_minute, MINUTE);
    EEPROM.write(ee_second, SECOND);
    EEPROM.write(ee_day, DAY);
    EEPROM.write(ee_month, MONTH);
    YEAR -= 2000;
    EEPROM.write(ee_year, YEAR);
    delay(100);
    HOUR = EEPROM.read(ee_hour);
    MINUTE = EEPROM.read(ee_minute);
    SECOND = EEPROM.read(ee_second);
    DAY = EEPROM.read(ee_day);
    MONTH = EEPROM.read(ee_month);
    YEAR = EEPROM.read(ee_year);
    
    setTime(HOUR, MINUTE, SECOND, DAY, MONTH, (2000+YEAR));
    stepset = 0;
    count = 0;
  }
  
  if(stepset == 1)  {   //  step set hour
    state_push = digitalRead(push);
    if (state_push == 0)  { 
      delay(DEBOUNCE);
      stepset++;
    }
    state_right = digitalRead(right);
    if(state_right == 0)  {
      delay(DEBOUNCE);
      HOUR--;
    }
    state_left = digitalRead(left);
    if(state_left == 0)  {
      delay(DEBOUNCE);
      HOUR++;
    }
    uView.setCursor(0,  20);
    uView.print(" ^");
    uView.display();
  }

  if(stepset == 2)  {   //  step set minute
    state_push = digitalRead(push);
    if (state_push == 0)  { 
      delay(DEBOUNCE);
      stepset++;
    }
    state_right = digitalRead(right);
    if(state_right == 0)  {
      delay(DEBOUNCE);
      MINUTE--;
    }
    state_left = digitalRead(left);
    if(state_left == 0)  {
      delay(DEBOUNCE);
      MINUTE++;
    }
    uView.setCursor(0,  20);
    uView.print("    ^");
    uView.display();
  }

  if(stepset == 3)  {   //  step set second
    state_push = digitalRead(push);
    if (state_push == 0)  { 
      delay(DEBOUNCE);
      stepset++;
    }
    state_right = digitalRead(right);
    if(state_right == 0)  {
      delay(DEBOUNCE);
      SECOND--;
    }
    state_left = digitalRead(left);
    if(state_left == 0)  {
      delay(DEBOUNCE);
      SECOND++;
    }
    uView.setCursor(0,  20);
    uView.print("       ^");
    uView.display();
  }

  if(stepset == 4)  {   //  step set day
    state_push = digitalRead(push);
    if (state_push == 0)  { 
      delay(DEBOUNCE);
      stepset++;
    }
    state_right = digitalRead(right);
    if(state_right == 0)  {
      delay(DEBOUNCE);
      DAY--;
    }
    state_left = digitalRead(left);
    if(state_left == 0)  {
      delay(DEBOUNCE);
      DAY++;
    }
    uView.setCursor(0,  20);
    uView.print("        ");
    uView.setCursor(0,  37);
    uView.print(" ^");
    uView.display();
  }

  if(stepset == 5)  {   //  step set month
    state_push = digitalRead(push);
    if (state_push == 0)  { 
      delay(DEBOUNCE);
      stepset++;
    }
    state_right = digitalRead(right);
    if(state_right == 0)  {
      delay(DEBOUNCE);
      MONTH--;
    }
    state_left = digitalRead(left);
    if(state_left == 0)  {
      delay(DEBOUNCE);
      MONTH++;
    }
    uView.setCursor(0,  37);
    uView.print("    ^");
    uView.display();
  }

  if(stepset == 6)  {   //  step set year
    state_push = digitalRead(push);
    if (state_push == 0)  { 
      delay(DEBOUNCE);
      stepset++;
    }
    state_right = digitalRead(right);
    if(state_right == 0)  {
      delay(DEBOUNCE);
      YEAR--;
    }
    state_left = digitalRead(left);
    if(state_left == 0)  {
      delay(DEBOUNCE);
      YEAR++;
    }
    uView.setCursor(0,  37);
    uView.print("         ^");
    uView.display();
  }
}

