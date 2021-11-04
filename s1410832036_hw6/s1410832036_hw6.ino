#define PIN 13

void setup() {
    Serial.begin(9600);
    Serial.println("");
    Serial.println("===== Start =====");
    pinMode(PIN,OUTPUT);
    digitalWrite(PIN,HIGH);   //燈滅
}

int maxV = 0, minV = 1024;
int count = 0;
int dd = 0;
bool flag = 0;
int gap = 0;
void loop() {
    int sv = analogRead(A5);
    if(count < 50){
//      maxV = maxV < sv ? sv : maxV;
//      minV = minV > sv ? sv : minV;
        if(sv > maxV){
            maxV = sv;
        }
        if(minV > sv) minV = sv;
        count ++;
    }else{
        Serial.println(String(minV) + " : " + String(sv)+ " : " + String(maxV));
        if((sv > (maxV+gap) || sv < (minV-gap)) && dd > 10){
            flag = !flag;
            Serial.println(flag);
            Serial.println(flag);
            Serial.println(flag);
            if(flag){
                digitalWrite(PIN,LOW);  //燈亮
            }else{
                digitalWrite(PIN,HIGH);   //燈滅
            }
            dd = 0;
        }
        dd++;
    }
    delay(100);
}
