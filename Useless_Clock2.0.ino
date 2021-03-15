#include <DS3231.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <EEPROM.h>
#include <SPI.h>
#include <SD.h>
#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

#define BA  A0
#define BU  A1
#define BD  A2
#define BTS A3


#define Speaker 8

#define SD_ChipSelectPin 3

const int chipSelect = 4;

int hh = 0, mm = 0, ss = 0, dd = 0, set_day;

int Alarm = 0;

int Ahh = 0;

int Amm = 0;

int flag = 0;

int TM = 0;

String Day = "  ";

Time t;

TMRpcm tmrpcm;

DS3231  rtc(SDA, SCL);

LiquidCrystal lcd(8, 2, 3, 5, 6, 7);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
if(!SD.begin(chipSelect))
{
  Serial.println("SD fail");
  return;
  }
if(SD.begin(chipSelect)){
  Serial.println("SD Success");
}
tmrpcm.speakerPin = 9;
rtc.begin();
rtc.setDOW(WEDNESDAY);
rtc.setTime(20,07, 40);  // Set the time to 12:00:00 (24hr format)
rtc.setDate(3, 10, 2021); // Set the date to January 1st, 2014
 pinMode(BA,  INPUT_PULLUP);
 pinMode(BU,  INPUT_PULLUP);
 pinMode(BD,  INPUT_PULLUP);
 pinMode(BTS, INPUT_PULLUP);
lcd.begin(16,2);
lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
t = rtc.getTime();
Day = rtc.getDOWStr(1);

hh = t.hour,DEC;
mm = t.min,DEC;
ss = t.sec,DEC;
dd = t.date,DEC;

if (Alarm == 0 && flag == 0)
{
lcd.setCursor(4,0);
lcd.print(hh);
lcd.setCursor(6,0);
lcd.print(" : ");
lcd.setCursor(9,0);
lcd.print(mm);
digitalRead (BA) && (BTS);
delay(10);
}


if (Alarm == 1 && flag == 0)
{
lcd.clear();
lcd.setCursor(4,0);
lcd.print(hh);
lcd.setCursor(6,0);
lcd.print(" : ");
lcd.setCursor(9,0);
lcd.print(mm);
lcd.setCursor(11,0);
lcd.print("ALRM");
digitalRead (BA) && (BTS);
delay(10);
}

if (Alarm == 1 && Ahh == hh && Amm == mm){
  tmrpcm.setVolume(5);
  tmrpcm.play("Speech.wav");
  Alarm = 0;
}

//Alarm Time Set


if (digitalRead(BA) == 0){
  Alarm = 1;
  flag = 2;
}

while(Alarm == 1 && flag == 2 && TM == 0){
 lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Alarm Set Mode");
  delay(1000);
  lcd.clear();
  TM = 1;
while(flag == 2 && TM == 1){
  delay(100);
  lcd.setCursor(5,0);
  lcd.print(Ahh);
  lcd.setCursor(7,0);
  lcd.print(":");
  delay(50);
  digitalRead (BU) && (BD) && (BA);
  
if(digitalRead (BU) == 0 && flag == 2 && TM == 1){
    Ahh = Ahh+1;
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print(Ahh);
    lcd.setCursor(7,0);
    lcd.print(":");
    delay(50);
  }
  
if(digitalRead (BD) == 0 && flag == 2 && TM == 1){
    Ahh = Ahh-1;
    lcd.setCursor(5,0);
    lcd.print(Ahh);
    delay(50);    
 }
 
if(digitalRead (BA) == 0 && flag == 2 && TM == 1){
    TM = 2;
  }
  
while(flag == 2 && TM == 2){
  delay(100);
  lcd.setCursor(5,0);
  lcd.print(Ahh);
  lcd.setCursor(7,0);
  lcd.print(":");
  lcd.setCursor(9,0);
  lcd.print(Amm);
  delay(50);
  digitalRead (BU) && (BD) && (BA);
  
if(digitalRead (BU) == 0 && flag == 2 && TM == 2){
  lcd.clear();
  Amm = Amm+1;
  lcd.setCursor(9,0);
  lcd.print(Amm);
  delay(50);
  }
  
if(digitalRead (BD) == 0 && flag == 2 && TM == 2){
  Amm = Amm-1;
  lcd.setCursor(9,0);
  lcd.print(Amm);
  delay(50);
  }
  if(digitalRead (BA) ==0 && flag == 2 && TM == 2){
    lcd.setCursor(2,0);
    lcd.print("Time Set");
  flag = 0;
  TM ==0;
  }
}  
}
}


//Time Set


if(digitalRead (BTS) == 0 && flag == 0 && TM == 0)
{
  flag = 1;
  TM = 1;
}

while(flag==1){
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Time Set Mode");
  delay(1000);
  TM = 1;
  if(flag == 1 && TM == 1){
  lcd.clear();
  delay(800);
  lcd.setCursor(2,0);
  lcd.print(hh);
  delay(800);
  
if(digitalRead (BU) == 0 && flag == 1 && TM == 1){
  hh = hh+1;
  }
  
if(digitalRead (BD) == 0 && flag == 1 && TM == 1){
  hh = hh-1;
 }
 
if(digitalRead (BTS) == 0 && flag == 1 && TM == 1){
  lcd.clear();
  delay(800);
  lcd.setCursor(4,0);
  lcd.print(mm);
  delay(800);
  TM = 2;
  }
  
if(digitalRead (BU) == 0 && flag == 1 && TM == 2){
  mm = mm+1;
  }
  
if(digitalRead (BD) == 0 && flag == 1 && TM == 2){
  mm = mm-1;
  }
  
if(digitalRead (BTS) ==0 && flag == 1 && TM == 2){
  flag = 0;
  }
}
}
}
