void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lightLevel;
  lightLevel=analogRead(A0);
  lightLevel=map(lightLevel, 0, 1023, 0, 255);
  lightLevel=constrain(lightLevel, 0, 255);
  digitalWrite(9, lightLevel);
  Serial.println(lightLevel);
 delay(1000);
 }
