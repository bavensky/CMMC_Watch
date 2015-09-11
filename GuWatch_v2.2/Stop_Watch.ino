void stop_watch() {
  int timeout = 0;
  
  state_push = digitalRead(push );
  if(state_push == 0)  {  //  ออกนาฬิกาจับเวลา
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count = 0;
  }

  state_left = digitalRead(left);
  if(state_left == 0)  {
    delay(DEBOUNCE);
    digit6 = 0;
    digit5 = 0;
    digit4 = 0;
    digit2 = 0;
    digit3 = 0;
    digit1 = 0;
  }
  state_right = digitalRead(right);
  if(state_right == 0)  {
    delay(DEBOUNCE);
    timeout = 1;
  }

  while(timeout == 1) {
    state_right = digitalRead(right);
    if(state_right == 0)  {
      delay(DEBOUNCE);
      timeout = 0;
    }

    if(digit1 > 9)  {
      digit1 = 0;
      digit2++;
    }
    if(digit2 > 9)  {
      digit2 = 0;
    }
    if(digit3 > 9)  {
      digit3 = 0;
      digit4++;   
    }
    if(digit4 > 5)  {
      digit4 = 0;
      digit5++;   
    }
    if(digit5 > 6)  {
      digit5 = 0;
      digit6++;   
    }
    if(digit6 > 5)  {
      digit6 = 0;
      digit5 = 0;
      digit4 = 0;
      digit2 = 0;
      digit3 = 0;
      digit1 = 0;
    }
    
    uView.clear(PAGE);
    uView.setFontType(1);
    uView.setCursor(0,  0);
    uView.print(">>");  
    uView.setCursor(0,  20); 
    uView.print(digit6);
    uView.print(digit5);
    uView.print(":");
    uView.print(digit4);     
    uView.print(digit3);
    uView.setCursor(44,  24); 
    uView.setFontType(0); 
    uView.print(".");
    uView.print(digit2);     
    uView.print(digit1);
    uView.display();

    unsigned long now_time = millis();  // เวลาปัจจุบัน
    if(now_time - pre_time >= time_count)  {
      digit3++;
      pre_time = now_time;
    }
    digit1++;
  }

  uView.clear(PAGE);
  uView.setFontType(1); 
  uView.setCursor(0,  0);
  uView.print("||"); 
  uView.setCursor(0,  20); 
  uView.print(digit6);
  uView.print(digit5);
  uView.print(":");
  uView.print(digit4);     
  uView.print(digit3);
  uView.setCursor(44,  24); 
  uView.setFontType(0); 
  uView.print(".");
  uView.print(digit2);     
  uView.print(digit1);
  uView.display();

}

