#include <LiquidCrystal_PCF8574.h>
#include "DHT.h"
#define DHT_PIN 3
#define DHT_TYPE DHT11

LiquidCrystal_PCF8574 lcd(0x3F);
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(String(DHT_TYPE)+" test!");
  dht.begin();

  
  lcd.begin(16, 2); // 初始化LCD
  
  lcd.setBacklight(255);
  lcd.clear();
  lcd.setCursor(0, 0);  //設定游標位置 (字,行)
  lcd.print("*~ first line.");
  lcd.setCursor(0, 1);
  lcd.print("~* second line.");
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  Serial.println("Humidity: "+String(h)+" %\t");
  Serial.print("Temperature: "+String(t)+" *C "+String(f)+" *F\t");

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
}
