int trigPIN = 12;
int echoPIN = 11;

long duration, cm, inches;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPIN, OUTPUT);
  pinMode(echoPIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPIN, LOW);
  delay(5);
  digitalWrite(trigPIN, HIGH);
  delay(10);
  digitalWrite(trigPIN, LOW);

  pinMode(echoPIN, INPUT);
  duration = pulseIn(echoPIN, HIGH);

  cm = (duration / 2) / 29.1;
  inches = (duration / 2) / 74;

  Serial.println("Distance: " + String(inches) + "in,  " + String(cm) + "cm");
}
