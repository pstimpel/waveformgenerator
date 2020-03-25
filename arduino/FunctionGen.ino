//SCULLCOM HOBBY ELECTRONICS
//FUNCTION GENERATOR
//Software Version 2
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <FreqCounter.h>    //Frequency Counter Library

/*
 * D3 low medium range
 * D4 low frequence range
 * D5 is input for frequency
 * D6 SIN/SQU/TRI/PWM Pin 1 SQU ON=1
 * D7 SIN/SQU/TRI/PWM Pin 2 PWM ON=1
 * D8 SIN/SQU/TRI/PWM Pin 3 SIN/TRI ON ON=SIN ON
 * D9 Relay on/off ON=TRI OFF=SIN
 * D10 Range switch button
 * D11 Form switch button
 * D12 PWM on/off button
 * A4 Display I2C SDA
 * A5 Display I2C SCL

*/

LiquidCrystal_I2C lc(0x27,20,4);

unsigned long frq=0;
volatile bool frqrangetriggerInUse=false;
volatile bool waveformtriggerInUse=false;
volatile bool pwmtriggerInUse=false;

volatile int frqrange=-1;
volatile int waveform=-1;
volatile bool startup=true;
volatile bool dot=false;

volatile bool pwmenabled=false;

int lowrangepin=1;
int belowmediumrangepin=2;
int mediumrangepin=3;
int abovemediumrangepin=4;


int rangebuttonpin=10;

int waveformbuttonpin = 11;
int pwmbuttonpin = 12;

int squareswitch = 6;
int pwmswitch = 7;
int sintrivssquswitch = 8;
int sinvstriswitch = 9;

volatile bool pwmchanged=false;

void setup()
{
  lc.init();
  // Print a message to the LCD.
  lc.backlight();
  lc.setCursor(0,0);
  lc.print("Function Gen");
  lc.setCursor(0,1);
  lc.print("HW: 1.0  SW: 1.0");

  pinMode(lowrangepin, OUTPUT); //
  pinMode(belowmediumrangepin, OUTPUT); //
  pinMode(mediumrangepin, OUTPUT); //
  pinMode(abovemediumrangepin, OUTPUT); //
    
  pinMode(rangebuttonpin, INPUT_PULLUP);
  pinMode(waveformbuttonpin, INPUT_PULLUP);
  pinMode(pwmbuttonpin, INPUT_PULLUP);

  pinMode(squareswitch, OUTPUT);
  pinMode(pwmswitch, OUTPUT);
  pinMode(sintrivssquswitch, OUTPUT);
  pinMode(sinvstriswitch, OUTPUT);

  
  lc.setCursor(0,0);
  delay(2000);
  lc.print("                ");
  lc.setCursor(0,1);
  lc.print("                ");

  //init
  frqrange=1; //start medium, so medium-1
  waveform=0; //Start triangle, to unload the relay at start
  pwmenabled=false; //PWM off
}

void printNumber(unsigned long v) {
    unsigned long ones;
    unsigned long tens;
    unsigned long hundreds;
    unsigned long thousands;
    unsigned long tenthousands;
    unsigned long hundredthousands;

    ones=v%10;
    v=v/10;
    tens=v%10;
    v=v/10;
    hundreds=v%10;
    v=v/10;
    thousands=v%10;
    v=v/10;
    tenthousands=v%10;
    v=v/10;
    hundredthousands=v;

    lc.setCursor(0,0);
    lc.print("Hz       ");
    lc.setCursor(3,0);
    lc.print(frq);
    

    if(frq<100000)
    {
    //lc.setRow(0,7,B00000000);
    }
    else
    {
      //lc.setDigit(0,7,(byte)hundredthousands,false);
    }
    
    
    if(frq<10000)
    {
    //lc.setRow(0,6,B00000000);
    }
    else
    {
      //lc.setDigit(0,6,(byte)tenthousands,false);
    }

    
    if(frq<1000)
    {
    //lc.setRow(0,5,B00000000);
    }
    else
    {
      //lc.setDigit(0,5,(byte)thousands,false);
    }   

 if(frq<100)
    {
    //lc.setRow(0,4,B00000000);
    }
    else
    {
      //lc.setDigit(0,4,(byte)hundreds,false);
    }

if(frq<10)
    {
    //lc.setRow(0,3,B00000000);
    }
    else
    {
      //lc.setDigit(0,3,(byte)tens,false);
    }
    
    //lc.setDigit(0,2,(byte)ones,false);
    
    //lc.setRow(0,0,B00110111); //print letter H for Hertz
}

void loop() { 

  if(digitalRead(rangebuttonpin) == LOW or startup==true) {
    if(frqrangetriggerInUse==false) {  
      frqrange++;
      if (frqrange>4) {
        frqrange=0;  
      }
      frqrangetriggerInUse=true;
      lc.setCursor(0,1);
      lc.print("                ");

      if(frqrange==0) {
        digitalWrite(lowrangepin, HIGH);
        digitalWrite(belowmediumrangepin, LOW);
        digitalWrite(mediumrangepin, LOW);
        digitalWrite(abovemediumrangepin, LOW);
        lc.setCursor(0,1);
        lc.print("Range: 1-10");
      }
      if(frqrange==1) {
        digitalWrite(lowrangepin, LOW);
        digitalWrite(belowmediumrangepin, HIGH);
        digitalWrite(mediumrangepin, LOW);
        digitalWrite(abovemediumrangepin, LOW);
        lc.setCursor(0,1);
        lc.print("Range: 10-100");
      }
      if(frqrange==2) {
        digitalWrite(lowrangepin, LOW);
        digitalWrite(belowmediumrangepin, LOW);
        digitalWrite(mediumrangepin, HIGH);
        digitalWrite(abovemediumrangepin, LOW);
        lc.setCursor(0,1);
        lc.print("Range: 100-1k");
      }
      if(frqrange==3) {
        digitalWrite(lowrangepin, LOW);
        digitalWrite(belowmediumrangepin, LOW);
        digitalWrite(mediumrangepin, LOW);
        digitalWrite(abovemediumrangepin, HIGH);
        lc.setCursor(0,1);
        lc.print("Range: 1-10k");
      }
      if(frqrange==4) {
        digitalWrite(lowrangepin, LOW);
        digitalWrite(belowmediumrangepin, LOW);
        digitalWrite(mediumrangepin, LOW);
        digitalWrite(abovemediumrangepin, LOW);
        lc.setCursor(0,1);
        lc.print("Range: 10-100k");
      }
      
    }
      
  } else {
    if(frqrangetriggerInUse==true) {
      frqrangetriggerInUse=false;
    }
  }

  if(digitalRead(pwmbuttonpin) == LOW) {
    if(pwmtriggerInUse==false) {  
      if(pwmenabled==false) {
        pwmenabled=true;
        waveform=waveform+3;
      } else {
        pwmenabled=false;
        waveform=waveform-3;
      }
      //lc.setCursor(15,0);
      //lc.print("x");
      pwmtriggerInUse=true;
      pwmchanged=true;
      
    }
      
  } else {
    if(pwmtriggerInUse==true) {
      pwmtriggerInUse=false;
    }
  }


  if(digitalRead(waveformbuttonpin) == LOW or startup==true or pwmchanged==true) {
    
    if(waveformtriggerInUse==false) {  
      if(pwmchanged==false) {
        waveform++;
      }
      
      if(pwmenabled==true) {
        if(waveform>5){
          waveform=3; 
        }
      } else {
        if(waveform>2){
          waveform=0; 
        } 
      }
         
      waveformtriggerInUse=true;
      lc.setCursor(10,0);
      lc.print("------");
      
      //lc.setCursor(15,0);
      //lc.print(waveform);

      
      
      if(waveform==0) {
        digitalWrite(squareswitch, LOW);
        digitalWrite(pwmswitch, LOW);
        digitalWrite(sintrivssquswitch, HIGH);
        digitalWrite(sinvstriswitch, HIGH);
        lc.setCursor(10,0);
        lc.print("   SIN");
      }
      if(waveform==1) {
        digitalWrite(squareswitch, LOW);
        digitalWrite(pwmswitch, LOW);
        digitalWrite(sintrivssquswitch, HIGH);
        digitalWrite(sinvstriswitch, LOW);
        lc.setCursor(10,0);
        lc.print("   TRI");
      }
      if(waveform==2) {
        digitalWrite(squareswitch, HIGH);
        digitalWrite(pwmswitch, LOW);
        digitalWrite(sintrivssquswitch, LOW);
        digitalWrite(sinvstriswitch, LOW);
        lc.setCursor(10,0);
        lc.print("   SQU");
      }
      
      if(waveform==3) {
        digitalWrite(squareswitch, LOW);
        digitalWrite(pwmswitch, HIGH);
        digitalWrite(sintrivssquswitch, HIGH);
        digitalWrite(sinvstriswitch, HIGH);
        lc.setCursor(10,0);
        lc.print("SINRMP");
      }
      if(waveform==4) {
        digitalWrite(squareswitch, LOW);
        digitalWrite(pwmswitch, HIGH);
        digitalWrite(sintrivssquswitch, HIGH);
        digitalWrite(sinvstriswitch, LOW);
        lc.setCursor(10,0);
        lc.print("TRIRMP");
      }
      if(waveform==5) {
        digitalWrite(squareswitch, HIGH);
        digitalWrite(pwmswitch, HIGH);
        digitalWrite(sintrivssquswitch, LOW);
        digitalWrite(sinvstriswitch, LOW);
        lc.setCursor(10,0);
        lc.print("   PWM");
      }
      
    }
      
  } else {
    if(waveformtriggerInUse==true) {
      waveformtriggerInUse=false;
    }
  }

  pwmchanged=false;
 
  //#######################################################
  startup=false;
  
  // wait if any serial is going on
  FreqCounter::f_comp=140;      // Calibation Value of 140 - change value to calibrate with professional Frequency Counter if one available.
  FreqCounter::start(1000);     // 1000 mSec Gate Time

  while (FreqCounter::f_ready == 0) 
  frq=FreqCounter::f_freq;
  printNumber(frq);

  if(dot==false) {
    dot=true;  
    lc.setCursor(15,1);
    lc.print(".");
  } else {
    dot=false;
    lc.setCursor(15,1);
    lc.print(" ");
  }
  
  delay(20);
}
