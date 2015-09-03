/******************************************************************************
* Project  : Gu Watch                                                         *
* Compiler : Arduino 1.5.5                                                    *
* Board    : Micro view                                                       *
* Shield   : -                                                                *
* Device   : RTC DS1307                                                       *
*          : 3 Button                                                         *
*          : wtv020m01 Audio module                                           *
* Author   : Bavensky :3                                                      *
* E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
* Date     : 03/09/2015 [dd/mm/yyyy]                                          *
*******************************************************************************/

#include <MicroView.h>
#include <Wtv020sd16p.h>
#include <Wire.h>
#include "RTClib.h"

//Instantiate objects from class definitions
RTC_DS1307 RTC;
/**************  Variable  ***************************/
int mode=0;
byte push = A1;
byte left = A0;
byte right = A2;

int state_left;
int state_right;
int state_push;

#define DEBOUNCE 200

/**************  Clock  ******************************/
int count=0;
int clocksize = 24;

static uint8_t x0,  y0,  x1,  y1;
static float radianshour,  radiansmin,  radianssec,  hourx,  houry,  minx,  miny,  secx,  secy;
static boolean drawnFirst  =  false;

/**************  Game  ******************************/
float y  =  5;
float v  =  0;
float r  =  0;

/**************  Stop Watch  ************************/
int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int digit4 = 0;
int digit5 = 0;
int digit6 = 0;

int time_count = 1000; //  หน่วงเวลา
unsigned long pre_time = 0;

/*************  Music  ******************************/
int resetPin = 2;  // The pin number of the reset pin.
int clockPin = 3;  // The pin number of the clock pin.
int dataPin = 5;  // The pin number of the data pin.
int busyPin = 6;  // The pin number of the busy pin.

int song_number = 0;
int stepsong = 0;

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);


void setup () {
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);

  pinMode(push, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  
  wtv020sd16p.reset();
  
//  RTC.adjust(DateTime(__DATE__, __TIME__));
  
  uView.begin();		// init and start MicroView
  uView.clear(PAGE);	// erase the display memory buffer

//  wtv020sd16p.playVoice(4);
  
}
 
void loop()  {
  state_push = digitalRead(push);
  state_right = digitalRead(right);
  state_left = digitalRead(left);
  
// Select mode
  if(state_right == 0)  {
    delay(DEBOUNCE);
    mode++;
  }
  if(state_left == 0)  {
    delay(DEBOUNCE);
    mode--;
  }  
  if(mode <= 0)  {
    mode = 0;
  }
  if(mode >= 4)  {
    mode = 4;
  }

// Display
  if(mode == 0) {
    display_main();
    }
  if(state_push == 1 && mode == 1) {
    display_clock();
    }  
  if(state_push == 1 && mode == 2) {
    display_game();
    }
  if(state_push == 1 && mode == 3) {
    display_count();
    }
  if(state_push == 1 && mode == 4) {
    display_mp3();
    }    

//Function    
  if(state_push == 0 && mode == 1)  {
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count = 1;
  }
  while(count == 1)  {
    now_aday();
  }

  if(state_push == 0 && mode == 2)  {
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count = 2;
  }
  while(count == 2)  {
    lander_game();
  }
  
  if(state_push == 0 && mode == 3)  {
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count = 3;
  }
  while(count == 3)  {
    stop_watch();
  }
  
  if(state_push == 0 && mode == 4)  {
    delay(DEBOUNCE);
    uView.clear(PAGE);
    count = 4;
  }
  while(count == 4)  {
    mp3();
  }
  
}   //  End loop

void display_main() {
  uView.clear(PAGE);
  uView.setFontType(1); 
  uView.setCursor(0, 7);   
  uView.print(" Watch");
  uView.setFontType(0); 
  uView.setCursor(0,  30);      
  uView.print("Chiang Mai");  
  uView.setCursor(0,  40);      
  uView.print("Maker Club");
  uView.display();
}

void display_clock()  {
  uView.clear(PAGE);
  uView.setFontType(0); 
  uView.setCursor(0,  0);      
  uView.print("Mode : 1");
  uView.setFontType(1);  
  uView.setCursor(0,  15);      
  uView.print(" Clock");
  uView.display();  
}

void display_game()  {
  uView.clear(PAGE);
  uView.setFontType(0); 
  uView.setCursor(0,  0);      
  uView.print("Mode : 2");
  uView.setFontType(1);  
  uView.setCursor(0,  15);      
  uView.print(" Lander");
  uView.setCursor(0,  30);   
  uView.print("  Game");
  uView.display();  
}

void display_count()  {
  uView.clear(PAGE);
  uView.setFontType(0); 
  uView.setCursor(0,  0);      
  uView.print("Mode : 3");
  uView.setFontType(1);  
  uView.setCursor(0,  15);      
  uView.print(" Stop");
  uView.setCursor(0,  30);   
  uView.print("  Watch");
  uView.display();  
}

void display_mp3()  {
  uView.clear(PAGE);
  uView.setFontType(0); 
  uView.setCursor(0,  0);      
  uView.print("Mode : 4");
  uView.setFontType(1);  
  uView.setCursor(0,  15);      
  uView.print(" MP3");
  uView.display();  
}


