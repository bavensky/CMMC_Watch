void settime () {
  state_push = digitalRead(push);
  if (state_push == 0)  { // ออกตั้งเวลานาฬิกา
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count = 0;
  }

  int stepset = 1;

  state_push = digitalRead(push);
  state_right = digitalRead(right);
  state_left = digitalRead(left);
  while(stepset == 1) {
    
  }
  
//  #define CLOCK_SIZE 23 
//  #define HOUR 21
//  #define MINUTE 18
//  #define SECOND 35
//  #define DAY 18
//  #define MONTH 9
//  #define YEAR 2015
}

