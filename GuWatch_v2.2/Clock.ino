/********************  Function Clock  ********************************/
void now_aday()  {
  state_push = digitalRead(push);
  if(state_push == 0)  {  // ออกนาฬิกา
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count = 0;
  }
 
  // get the time from the clock chip
  DateTime now = RTC.now();
  
  // convert hms into radians
  radianshour = (((now.hour() * 360) / 12) + 270) * (PI / 180);
  radiansmin = (((now.minute() * 360) / 60) + 270) * (PI / 180);
  radianssec = (((now.second() * 360) / 60) + 270) * (PI / 180);
  
  // calculate clock hand endpoints		
  hourx = cos(radianshour) * (clocksize / 2.5);
  houry = sin(radianshour) * (clocksize / 2.5);
  
  minx = cos(radiansmin) * (clocksize / 1.4);
  miny = sin(radiansmin) * (clocksize / 1.4);
  
  secx = cos(radianssec) * (clocksize / 1.1);
  secy = sin(radianssec) * (clocksize / 1.1);
  
  uView.setFontType(0); 		// set font type 0, please see declaration in MicroView.cpp
  uView.setCursor(27,0);		// points cursor to x=27 y=0
  	
  // Draw face
  uView.print(12);			
  uView.setCursor(30,  uView.getLCDHeight()-uView.getFontHeight());
  uView.print(6);
  uView.setCursor(0,  uView.getLCDHeight() /2-(uView.getFontHeight()/2));
  uView.print(9);
  uView.setCursor(uView.getLCDWidth()-uView.getFontWidth(),  uView.getLCDHeight()/2-(uView.getFontHeight()/2));
  uView.print(3);
  uView.display();			// display the memory buffer drawn
	
  if (drawnFirst) {
    uView.line(32,  24,  32+hourx,  24+houry,  WHITE,  XOR);
    uView.line(32,  24,  32+minx,  24+miny,  WHITE,  XOR);
    uView.line(32,  24,  32+secx,  24+secy,  WHITE,  XOR);
  } 
  	
//  // get the time from the clock chip
//  DateTime now = RTC.now();
//  
//  // convert hms into radians
//  radianshour = (((now.hour() * 360) / 12) + 270) * (PI / 180);
//  radiansmin = (((now.minute() * 360) / 60) + 270) * (PI / 180);
//  radianssec = (((now.second() * 360) / 60) + 270) * (PI / 180);
  		
//  // calculate clock hand endpoints		
//  hourx = cos(radianshour) * (clocksize / 2.5);
//  houry = sin(radianshour) * (clocksize / 2.5);
//  
//  minx = cos(radiansmin) * (clocksize / 1.4);
//  miny = sin(radiansmin) * (clocksize / 1.4);
//  
//  secx = cos(radianssec) * (clocksize / 1.1);
//  secy = sin(radianssec) * (clocksize / 1.1);
  			
  // draw the clock face	
  uView.line(32,  24,  32+hourx,  24+houry,  WHITE,  XOR);
  uView.line(32,  24,  32+minx,  24+miny,  WHITE,  XOR);
  uView.line(32,  24,  32+secx,  24+secy,  WHITE,  XOR);
  	
  drawnFirst  =  true;
  uView.display();
  	
  drawnFirst  =  false;
  uView.clear(PAGE);
}
