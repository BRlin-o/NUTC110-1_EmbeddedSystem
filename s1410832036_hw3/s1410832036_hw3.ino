// C++ code
//
const int Input_size = 4;
const int Input_list[] = {A2, A3, A4, A5};
const int LED_size = 5;
const int LED[LED_size] = {12, 11, 10, 9, 8};  
const int delayTime = 200;

int input = 0;
int type = -1;
int i=0;

void setup()
{
  Serial.begin(9600);
  Serial.write(27);
  Serial.println("----START----");
  for (int i = 0; i < Input_size; i++) {
    pinMode(Input_list[i], INPUT);
  }
  for (int i = 0; i < LED_size; i++) {
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i], HIGH); 
  }
}

void loop()
{
  for(int t=0;t<Input_size;++t) {
    if((input = analogRead(Input_list[t])) > 512){
      type = (type != -1 && type == t ? -1 : t);
      Serial.println("input: " + String(t) + ", Type: " + String(type));
    }
    delay(delayTime/Input_size);
  }
  if (Serial.available() > 0) {
    input=Serial.read();
    type = input-48;
    Serial.println("input: " + String(input) + ", Type: " + String(type));
  }
  switch(type){
    case 0:
      digitalWrite(LED[i], HIGH); 
        i = (i+1)%LED_size;
        digitalWrite(LED[i], LOW); 
      break;
    case 1:
      digitalWrite(LED[i], HIGH); 
        i = i-1 + (i<1 ? LED_size : 0);
        digitalWrite(LED[i], LOW); 
      break;
    case 2:
      i = (i+1)%LED_size;
      digitalWrite(LED[i], LOW); 
      break;
    case 3:
      i = (i+1)%LED_size;
      digitalWrite(LED[i], HIGH); 
      break;
    default:
      break;
  }
  Serial.println("type: "+String(type)+", i: "+String(i)); 
}
