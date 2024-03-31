const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};  
const int potPin = A0;  

void setup() {
  Serial.begin(9600);  // Bắt đầu giao tiếp Serial
  for (int i = 0; i < 12; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(potPin, INPUT);
}

void loop() {
  int potValue = analogRead(potPin);  
  Serial.print("Giá trị biến trở: ");
  Serial.println(potValue);  

  int numLeds = map(potValue, 0, 1023, 0, 12);  

  for (int i = 0; i < 12; i++) {
    if (i < numLeds) {
      digitalWrite(ledPins[i], HIGH);  // Bật đèn
    } else {
      digitalWrite(ledPins[i], LOW);  
    }
  }

  delay(100);
}