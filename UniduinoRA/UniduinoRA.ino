void setup() {
  Serial.begin(9600);
}
void loop() {

  Serial.flush();
  
  
    Serial.write(map(analogRead(A0), 0, 1024, 0, 360));
    delay(20);
  
}

