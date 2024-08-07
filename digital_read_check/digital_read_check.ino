int buttonPin = 14;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  // put your setup code here, to run once:

}

void loop() {
  Serial.print("Button pin: ");
  Serial.println(digitalRead(buttonPin));
  delay(1000);
  // put your main code here, to run repeatedly:

}
