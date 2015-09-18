/********************  Function Clock  ********************************/
void now_aday()  {
  state_push = digitalRead(push);
  if (state_push == 0)  { // ออกนาฬิกา
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count = 0;
  }

  // get the time from the clock chip
  now_datetime();
  printDateTime();
  // convert hms into radians
  radianshour = (((_hour * 360) / 12) + 270) * (PI / 180);
  radiansmin = (((_minute * 360) / 60) + 270) * (PI / 180);
  radianssec = (((_second * 360) / 60) + 270) * (PI / 180);

  // calculate clock hand endpoints
  hourx = cos(radianshour) * (clocksize / 2.5);
  houry = sin(radianshour) * (clocksize / 2.5);

  minx = cos(radiansmin) * (clocksize / 1.4);
  miny = sin(radiansmin) * (clocksize / 1.4);

  secx = cos(radianssec) * (clocksize / 1.1);
  secy = sin(radianssec) * (clocksize / 1.1);

  uView.setFontType(0); 		// set font type 0, please see declaration in MicroView.cpp
  uView.setCursor(27, 0);		// points cursor to x=27 y=0

  // Draw face
  uView.print(12);
  uView.setCursor(30,  uView.getLCDHeight() - uView.getFontHeight());
  uView.print(6);
  uView.setCursor(0,  uView.getLCDHeight() / 2 - (uView.getFontHeight() / 2));
  uView.print(9);
  uView.setCursor(uView.getLCDWidth() - uView.getFontWidth(),  uView.getLCDHeight() / 2 - (uView.getFontHeight() / 2));
  uView.print(3);
  uView.display();			// display the memory buffer drawn

  if (drawnFirst) {
    uView.line(32,  24,  32 + hourx,  24 + houry,  WHITE,  XOR);
    uView.line(32,  24,  32 + minx,  24 + miny,  WHITE,  XOR);
    uView.line(32,  24,  32 + secx,  24 + secy,  WHITE,  XOR);
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
  uView.line(32,  24,  32 + hourx,  24 + houry,  WHITE,  XOR);
  uView.line(32,  24,  32 + minx,  24 + miny,  WHITE,  XOR);
  uView.line(32,  24,  32 + secx,  24 + secy,  WHITE,  XOR);

  drawnFirst  =  true;
  uView.display();

  drawnFirst  =  false;
  uView.clear(PAGE);
}

byte decToBcd(byte val)
{
  // Convert normal decimal numbers to binary coded decimal
  return ( (val / 10 * 16) + (val % 10) );
}

byte bcdToDec(byte val)
{
  // Convert binary coded decimal to normal decimal numbers
  return ( (val / 16 * 10) + (val % 16) );
}

/****** Set Date Time ***********************************/
void setDateTime()
{
  /*******  Config to time *****************************/
  byte set_second =      0;    // Set Second 0-59
  byte set_minute =      0;   // Set Minute 0-59
  byte set_hour =        0;    // Set Hour   0-23
  byte set_weekDay =     1;    // Set Day of Week  1-7
  byte set_monthDay =    11;   // Set Day of Month 1-31
  byte set_month =       9;   // Set Month  1-12
  byte set_year  =       15;   // Set Year   0-99

  /*******************************************************
  * BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0
  * ------------------------------------------------------
  * OUT  |  X   |  X   | SQWE |  X   |  X   | RS1  | RS0
  *  0   |  X   |  X   |  0   |  X   |  X   |  0   |  0
  ********************************************************/
  /* Comment :
      OUT  Mean  Output control level of the SQW out
      SQWE Mean  Square Wave Enable output depends upon the rs1 rs0
      RS   Mean  Rate Select control square wave output when enable
                 |  RS1  RS0  SQWoutput  |
                 |   0    0      1 Hz    |
                 |   0    1   4.096 kHz  |
                 |   1    0   8.192 kHz  |
                 |   1    1  32.768 kHz  |  */
  byte control  =    0b10010011;

  byte  d1;
  byte  d2;

  // Write to address ds1307
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);  //stop Oscillator
  Wire.write(decToBcd(set_second));
  Wire.write(decToBcd(set_minute));
  Wire.write(decToBcd(set_hour));
  Wire.write(decToBcd(set_weekDay));
  Wire.write(decToBcd(set_monthDay));
  Wire.write(decToBcd(set_month));
  Wire.write(decToBcd(set_year));
  Wire.write(control);
  //Wire.write(12);    //data address 08
  //Wire.write(34);    //data address 09
  Wire.write(zero);  //start
  Wire.endTransmission();

}

void now_datetime()
{
  //  Read from address ds1307
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 10);
  _second = bcdToDec(Wire.read());
  _minute = bcdToDec(Wire.read());
  _hour = bcdToDec(Wire.read() & 0b111111); // 24 hour time
  _weekDay = bcdToDec(Wire.read());         // 1-7 ->Sunday - Saturday
  _monthDay = bcdToDec(Wire.read());
  _month = bcdToDec(Wire.read());
  _year = bcdToDec(Wire.read());
  control = Wire.read();
  //d1 = Wire.read();
  //d2 = Wire.read();
}

void printDateTime()
{

  //print the data from DS1307
  Serial.print("Day : ");
  if (_weekDay == 1) Serial.print("Sunday");
  if (_weekDay == 2) Serial.print("Monday");
  if (_weekDay == 3) Serial.print("Tuesday");
  if (_weekDay == 4) Serial.print("Wednesday");
  if (_weekDay == 5) Serial.print("Thursday");
  if (_weekDay == 6) Serial.print("Friday");
  if (_weekDay == 7) Serial.print("Saturay");

  Serial.print(", ");
  Serial.print(_monthDay);
  Serial.print("/");
  Serial.print(_month);
  Serial.print("/20");
  Serial.print(_year);
  Serial.print(", ");
  Serial.print(_hour);
  Serial.print(":");
  Serial.print(_minute);
  Serial.print(":");
  Serial.print(_second);
  Serial.print(", ");
  Serial.print(control, BIN);
  Serial.print(", ");
  Serial.print(d1);
  Serial.print(", ");
  Serial.println(d2);

}
