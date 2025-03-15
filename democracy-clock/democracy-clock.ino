void setup() {
  Serial.begin(9600);
  Serial.println("Hello, World!");
}

void loop() {
  if (Serial.available() > 0){
    int test = Serial.read();
    Serial.println(test);
  }
  delay(1000);
}
