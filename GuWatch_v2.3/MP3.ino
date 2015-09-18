void mp3() {
  state_push = digitalRead(push);
  if(state_push == 0)  {  //  ออกการฟังเพลง
    delay(DEBOUNCE);
    uView.clear(PAGE);
    wtv020sd16p.stopVoice();
    count = 0;
  }

  state_right = digitalRead(right);
  if(state_right == 0)  {
    delay(DEBOUNCE);
    song_number++;
    stepsong = 1;
  }

  state_left = digitalRead(left);
  if(state_left == 0)  {
    delay(DEBOUNCE);
    song_number--;
    stepsong = 1;
  }

  if(song_number <= 0) song_number = 0;
  if(song_number >= 19) song_number = 19;
    
  while(stepsong == 1)  {
    wtv020sd16p.asyncPlayVoice(song_number);
    stepsong = 0;
  }
  
  uView.clear(PAGE);
  uView.setFontType(1);
  uView.setCursor(0,  0);
  uView.print("  MP3"); 
  uView.setFontType(0); 
  uView.setCursor(0,  20); 
  uView.print("Song No.");
  uView.print(song_number);
  uView.display();
}

