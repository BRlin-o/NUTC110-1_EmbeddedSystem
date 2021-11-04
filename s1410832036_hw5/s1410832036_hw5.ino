const int input = A5;
const int LED_PIN[] = {12, 13};
const int LED_LEN = 2;

int val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(input, INPUT);
  for(int i=0;i<LED_LEN;++i) {
    pinMode(LED_PIN[i], OUTPUT);
    digitalWrite(LED_PIN[i], HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(input);
  Serial.println("Input: " + String(val));
  if(val<800){
    Serial.println("0");
    digitalWrite(LED_PIN[0], HIGH);
    digitalWrite(LED_PIN[1], HIGH);
  }else if(val>800 && val < 1000) {
    Serial.println("1");
    digitalWrite(LED_PIN[0], LOW);
    digitalWrite(LED_PIN[1], HIGH);
  }else{
    Serial.println("2");
    digitalWrite(LED_PIN[0], LOW);
    digitalWrite(LED_PIN[1], LOW);
  }
  delay(200);
}
