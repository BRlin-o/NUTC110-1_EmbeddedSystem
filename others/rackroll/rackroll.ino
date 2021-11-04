#include <stdlib.h>
#include "pitches.h"

//音階頻率
//int freq[7][12] = {
//{NOTE_C1,NOTE_CS1,NOTE_D1,NOTE_DS1,NOTE_E1,NOTE_F1,NOTE_FS1,NOTE_G1,NOTE_GS1,NOTE_A1,NOTE_AS1,NOTE_B1,},
//{NOTE_C2,NOTE_CS2,NOTE_D2,NOTE_DS2,NOTE_E2,NOTE_F2,NOTE_FS2,NOTE_G2,NOTE_GS2,NOTE_A2,NOTE_AS2,NOTE_B2,},
//{NOTE_C3,NOTE_CS3,NOTE_D3,NOTE_DS3,NOTE_E3,NOTE_F3,NOTE_FS3,NOTE_G3,NOTE_GS3,NOTE_A3,NOTE_AS3,NOTE_B3,},
//{NOTE_C4,NOTE_CS4,NOTE_D4,NOTE_DS4,NOTE_E4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_GS4,NOTE_A4,NOTE_AS4,NOTE_B4,},
//{NOTE_C5,NOTE_CS5,NOTE_D5,NOTE_DS5,NOTE_E5,NOTE_F5,NOTE_FS5,NOTE_G5,NOTE_GS5,NOTE_A5,NOTE_AS5,NOTE_B5,},
//{NOTE_C6,NOTE_CS6,NOTE_D6,NOTE_DS6,NOTE_E6,NOTE_F6,NOTE_FS6,NOTE_G6,NOTE_GS6,NOTE_A6,NOTE_AS6,NOTE_B6,},
//{NOTE_C7,NOTE_CS7,NOTE_D7,NOTE_DS7,NOTE_E7,NOTE_F7,NOTE_FS7,NOTE_G7,NOTE_GS7,NOTE_A7,NOTE_AS7,NOTE_B7,},
//};

const int freq[7][7] = {
  {NOTE_C1,NOTE_D1,NOTE_E1,NOTE_F1,NOTE_G1,NOTE_A1,NOTE_B1},
  {NOTE_C2,NOTE_D2,NOTE_E2,NOTE_F2,NOTE_G2,NOTE_A2,NOTE_B2},
  {NOTE_C3,NOTE_D3,NOTE_E3,NOTE_F3,NOTE_G3,NOTE_A3,NOTE_B3},
  {NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4},
  {NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5,NOTE_B5},
  {NOTE_C6,NOTE_D6,NOTE_E6,NOTE_F6,NOTE_G6,NOTE_A6,NOTE_B6},
  {NOTE_C7,NOTE_D7,NOTE_E7,NOTE_F7,NOTE_G7,NOTE_A7,NOTE_B7}
};

const int MelodySize = 4;

const String melody[MelodySize] = 
//{ // rickroll
//  "(56)1(6)3 3 2   ",
//  "(56)1(6)2 2 1 (6)",
//  "(56)1(6)1 2(7 6 5)2 1 "
//};
{
  "356  4  3 2 1 2 6 5 63 2 1   0 ",
  "356  4  3 2 7 6 5 5 6 7 )1   (3 2 1 ",
};

const int buzzer_PIN = 3;

void setup() {
  pinMode(buzzer_PIN,OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("melody size" + String( MelodySize));
  Serial.println(melody[0].length());
}

void loop() {
  int l = 4;
  // put your main code here, to run repeatedly:
  for(int i=0;i<MelodySize;++i){
    for(int j=0;j<melody[i].length();++j){
      if(melody[i][j] == '(')l--;
      if(melody[i][j] == ')')l++;
      if(melody[i][j] == 48){
        int dly = 1;
        while(j+1<melody[i].length() && melody[i][j+1]==' ')j++,dly++;
        delay(d*100+50); 
      }
      if(!(melody[i][j] > 48 && melody[i][j] < 58))continue;
      int m = (int)(melody[i][j]-48);
      int dly = 1;
      while(j+1<melody[i].length() && melody[i][j+1]==' ')j++,dly++;
      buzzer(l, m, dly);
      Serial.print(String(l) + ":" + String(m)+"("+String(dly*250)+"ms)"+", ");
    }
    Serial.println();
  }
  delay(100000000);
}

void buzzer(int l, int f, int d) {
  tone(buzzer_PIN, freq[l-1][f-1]);
  delay(d*100); 
  noTone(buzzer_PIN);
  delay(50);
}
