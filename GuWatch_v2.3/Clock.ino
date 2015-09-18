/********************  Function Clock  ********************************/
void now_aday()  {
  state_push = digitalRead(push);
  if (state_push == 0)  { // ออกนาฬิกา
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count = 0;
  }
  
  drawFace();
    
  static boolean firstDraw = false;
  static unsigned long mSec = millis() + 1000;
  static float degresshour, degressmin, degresssec,
               hourx, houry, minx, miny, secx, secy;
  // If mSec
  if (mSec != (unsigned long)second()) 
  {
    // First time draw requires extra line to set up XOR's:
    if (firstDraw) 
    {
      uView.line(midW, midH, 32 + hourx, 24 + houry, WHITE, XOR);
      uView.line(midW, midH, 32 + minx, 24 + miny, WHITE, XOR);
      uView.line(midW, midH, 32 + secx, 24 + secy, WHITE, XOR);
    }
    
    degresshour = (((hour() * 360) / 12) + 270) * (PI / 180);
    degressmin = (((minute() * 360) / 60) + 270) * (PI / 180);
    degresssec = (((second() * 360) / 60) + 270) * (PI / 180);

    hourx = cos(degresshour) * (CLOCK_SIZE / 2.5);
    houry = sin(degresshour) * (CLOCK_SIZE / 2.5);
    minx = cos(degressmin) * (CLOCK_SIZE / 1.4);
    miny = sin(degressmin) * (CLOCK_SIZE / 1.4);
    secx = cos(degresssec) * (CLOCK_SIZE / 1.1);
    secy = sin(degresssec) * (CLOCK_SIZE / 1.1);

    uView.line(midW, midH, midW+hourx, midH+houry, WHITE, XOR);
    uView.line(midW, midH, midW+minx, midH+miny, WHITE, XOR);
    uView.line(midW, midH, midW+secx, midH+secy, WHITE, XOR);
    
    firstDraw = true;
    uView.display();
  }
}

void drawFace()
{
  uView.setFontType(0); // set font type 0 (Smallest)
  
  uint8_t fontW = uView.getFontWidth();
  uint8_t fontH = uView.getFontHeight();

  uView.setCursor(midW-fontW-1, midH-CLOCK_SIZE+1);
  uView.print(12);  // Print the "12"
  uView.setCursor(midW-(fontW/2)-1, midH+CLOCK_SIZE-fontH-1);
  uView.print(6);  // Print the "6"
  uView.setCursor(midW-CLOCK_SIZE+1, midH-fontH/2);
  uView.print(9);  // Print the "9"
  uView.setCursor(midW+CLOCK_SIZE-fontW-2, midH-fontH/2);
  uView.print(3);  // Print the "3"
  uView.display();
}
