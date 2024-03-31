const int ledPin[] = {A0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; 
const int buttonPin = A1;
int currentLed = 0; 
int score = 0; 
int speed = 500; 
int flag = 0;
bool isButtonPressed = false;

void setup() {
  for (int i = 0; i < 13; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
    checkButtonPress();
    moveLED();
}
void checkButtonPress() {
  int check = 0;
  int count = 50;
  while (count-- && check == 0){
    if (digitalRead(buttonPin) == LOW){
      check = 1;
    }
    delay(10);
  }
if (check) {
    if (currentLed == 5) { 
      score++;
      Serial.println("+1 điểm ");
      speed -= 100; 
    } else {
      score--;
      Serial.println("-1 điêmr ");
      speed += 100; 
    } 
    Serial.print("Score: ");
    Serial.println(score);
  }
}
void moveLED() {
  if (currentLed == 0) flag = 1;
  else if (currentLed == 12) flag = 0;
  if (flag) {
    currentLed++;
  } else {
    currentLed--;
  }
  for (int i = 12; i >= 0; i--) {
    digitalWrite(ledPin[i], (i == currentLed) ? HIGH : LOW);
  }
  delay(speed);
}

