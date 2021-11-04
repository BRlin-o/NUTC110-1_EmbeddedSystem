//全域變數
const int LED_size = 3;
const int LED[LED_size] = {13, 12, 11};  
const int delayTime = 100;

void setup() {
  //設定 Arduino 接腳 為輸出狀態
  for (int i = 0; i < LED_size; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH); 
  }

}

void loop() {
  for (int i = 0; i < LED_size-1; i++) {
    digitalWrite(LED[i], LOW);
    delay(delayTime);
    digitalWrite(LED[i], HIGH);
  }
  for (int i = LED_size-1; i > 0; i--) {
    digitalWrite(LED[i], LOW);
    delay(delayTime);
    digitalWrite(LED[i], HIGH);
  }
} 
