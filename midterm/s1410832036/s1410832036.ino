// HW4
#include <LiquidCrystal_PCF8574.h> // LiquidCrystal_PCF8574
#include <DHT.h> // DHT sensor library

// HW8
#include "pitches.h"

// -------------------Define Value---------------------
#define DHT_PIN 10
#define DHT_TYPE DHT11
#define LDR_PIN A1
#define KY_PIN A0
#define ECHO_PIN 11
#define TRIG_PIN 12
//#define RECV_PIN 10
#define BZR_PIN 9

int LED_length();
int ORDER_length();
void buzzer(int, int, double);

const int LED_PIN[] = {2, 3, 4};
const int ORDER_PIN[] = {5, 6, 7};
const int ORDER[] = {KY_PIN, LDR_PIN};

int ORDER_SIZE = 0;
int LED_SIZE = 0;

int TYPE = -1;
unsigned int i=0, lp_t = 0;

// ------------Value, Object---------------
// HW4
  // 超音波
LiquidCrystal_PCF8574 lcd(0x27);
  // 溫度
DHT dht(DHT_PIN, DHT_TYPE);
float h = 0;
float t = 0;
float f = 0;

// HW5
int LDR_value = 0;
int value = 0;

// HW6
double maxV = 0, minV = 1024, tol = 1.1;
double stand = -1;
int stand_time = 50;
int KY_status = 0;

// HW7
long duration, cm, inches;

// HW8
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
{ // rickroll
  "(56)1(6)332",
  "(56)1(6)221(6)",
  "(56)1(6)12(765)21"
};
//
const double melody_time[MelodySize][20] = {
  {0.5, 0.5, 0.5, 0.5, 1, 1, 4},
  {0.5, 0.5, 0.5, 0.5, 1, 1, 3, 1},
  {0.5, 0.5, 0.5, 0.5, 1.5, 0.5, 1, 1, 1, 2.5, 2.5}
};


// -------------SETUP---------------
void setup() {
  LED_SIZE = LED_length();
  ORDER_SIZE = ORDER_length();
  
  Serial.begin(9600);

//  IrReceiver.begin(RECV_PIN,ENABLE_LED_FEEDBACK);

  for(i=0;i<ORDER_SIZE;++i){
    pinMode(ORDER_PIN[i], INPUT_PULLUP);
  }

  pinMode(DHT_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(ECHO_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);

  for (int i=0;i<LED_SIZE;++i){
    pinMode(LED_PIN[i], OUTPUT);
    digitalWrite(LED_PIN[i], HIGH);
  }

  dht.begin();  //初始化DHT
  lcd.begin(16, 2); // 初始化LCD
  
  lcd.setBacklight(255);
  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("*~ first line.");
  lcd.setCursor(0, 1);
  lcd.print("~* second line.");
  
  Serial.println("[SETUP] Starting");
}

// -------------LOOP---------------
void loop() {
  int last_Type = TYPE;
  TYPE = 0;
  for(i=0;i<ORDER_SIZE;++i){
//    Serial.print("i" + String(i) + "= " + String((digitalRead(ORDER_PIN[i]) == LOW)) + "\t");
    TYPE = TYPE*2+(digitalRead(ORDER_PIN[i]) == LOW);
  }

  if(last_Type != TYPE){ // Init
    lp_t = 0;
    switch(TYPE){
      case 5:
        stand = 0;
        break;
    }
  }
  Serial.print("TYPE= " + String(TYPE) + "\t");
  
  switch(TYPE){ // Run
    case 3: //HW4
      h = dht.readHumidity();   //取得濕度
      t = dht.readTemperature();  //取得溫度C
      f = dht.readTemperature(true);
      Serial.print("Humidity: "+String(h)+" %\t");
      Serial.print("Temperature: "+String(t)+" *C "+String(f)+" *F");
      
      lcd.clear();
      lcd.setCursor(0, 0);  //設定游標位置 (字,行)
      lcd.print("RH  :");  //Relative Humidity 相對濕度簡寫
      lcd.setCursor(7, 0);  
      lcd.print(h);
      lcd.setCursor(14, 0);
      lcd.print("%");
    
      lcd.setCursor(0, 1);  //設定游標位置 (字,行)
      lcd.print("Temp:");
      lcd.setCursor(7, 1);  
      lcd.print(t);
      lcd.setCursor(13, 1);
      lcd.print((char)223); //用特殊字元顯示符號的"度"
      lcd.setCursor(14, 1);
      lcd.print("C");
      delay(1000);
      break;
    case 4: //HW5
      value = analogRead(LDR_PIN);
      Serial.print("LDR_value: " + String(value));
      if(value < 40) { // 太黑
        Serial.print("\t 太黑");
        for( i=0;i<LED_SIZE;++i){
          Serial.print(String(LED_PIN[i]) + "-開");
          digitalWrite(LED_PIN[i], LOW);
        }
      }else if(value > 40 && value < 100){ // 正常
        Serial.print("\t 正常");
        int i=0;
        for(i=0;i<1;++i){
          Serial.print(String(LED_PIN[i]) + "-開");
          digitalWrite(LED_PIN[i], LOW);
        }
        for(;i<LED_SIZE;++i) {
          Serial.print(String(LED_PIN[i]) + "-關");
          digitalWrite(LED_PIN[i], HIGH);
        }
      }else{// 太亮
        Serial.print("\t 太亮\t");
        for(i=0;i<LED_SIZE;++i){
          Serial.print(String(LED_PIN[i]) + "-關");
          digitalWrite(LED_PIN[i], HIGH);
        }
      }
      break;
    case 5:// HW6
      value = analogRead(KY_PIN);
      Serial.print("KY_value: " + String(value));
      if(lp_t < 50){
        Serial.print("min and max 計算中");
        stand+=value;
      }else{
        Serial.print("\t Standard: " + String(stand/stand_time));
        if((value > (stand/stand_time+tol)) || (value < (stand/stand_time-tol))){
          KY_status = !KY_status;
          digitalWrite(LED_PIN[0], KY_status ? LOW : HIGH);
        }
        Serial.print("\t Status: " + String(KY_status));
      }
      delay(50);
      break;
    case 6: //HW7
      digitalWrite(TRIG_PIN, LOW);
      delay(5);
      digitalWrite(TRIG_PIN, HIGH);
      delay(10);
      digitalWrite(TRIG_PIN, LOW);
      pinMode(ECHO_PIN, INPUT);
      duration = pulseIn(ECHO_PIN, HIGH);
    
      cm = (duration / 2) / 29.1;
      inches = (duration / 2) / 74;
    
      Serial.print("Distance: " + String(inches) + "in,  " + String(cm) + "cm");
      break;
    case 7: //HW8
      // todo Homeword 8: Music
      if(lp_t > 0)break;
      int l = 4;
      for(i=0;i<MelodySize;++i){
        int t_j = 0;
        for(int j=0;j<melody[i].length();++j) {
          if(melody[i][j] == '(')l--;
          if(melody[i][j] == ')')l++;
          if(melody[i][j] == 48){
            int dly = 1;
            while(j+1<melody[i].length() && melody[i][j+1]==' ')j++,dly++;
            delay(dly*100+50); 
          }
          if(!(melody[i][j] > 48 && melody[i][j] < 58))continue;
          int m = (int)(melody[i][j]-48);
//          int buz_t = 1;
//          while(j+1<melody[i].length() && melody[i][j+1]==' ')j++,buz_t++;
          double buz_t = melody_time[i][t_j++];
          buzzer(l, m, buz_t);
          Serial.print(String(l) + ":" + String(m)+"("+String(buz_t*250)+"ms)"+", ");
        }
      }
      break;
  }
  
  Serial.print("\t." + String(lp_t) + "\n");
  lp_t++;
}

int ORDER_length() {
  return sizeof(ORDER_PIN)/sizeof(int);
}

int LED_length() {
  return sizeof(LED_PIN)/sizeof(int);
}


// @params
//// l: 音高
//// 2: 音色
//// 3: 持續時間
void buzzer(int l, int f, double t) {
  tone(BZR_PIN, freq[l-1][f-1]);
  delay(t*100); 
  noTone(BZR_PIN);
  delay(50);
}
