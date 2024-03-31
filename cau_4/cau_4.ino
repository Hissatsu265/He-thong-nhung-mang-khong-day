#define trigPin 3
#define echoPin 2
int LED[10] = {4,5,6,7,8,9,10,11,12,13};
int num_of_led = 10;

void setup() 
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int i = 0; i<num_of_led; i++){
    pinMode(LED[i], OUTPUT);
  }

}
void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 100)
  {
    Serial.println("OK !");
  }
  else
  {
    Serial.print(distance);
    Serial.println(" cm");
    int t=10 - distance / 10;
    if (distance < 1){
      for (int i = 0; i<num_of_led; i++){
        digitalWrite(LED[i], HIGH);
      } 
    } 
    else
    {
      for (int i = 0; i<t; i++){
        digitalWrite(LED[i], HIGH);
      } 
      for (int i = t; i<10; i++){
        digitalWrite(LED[i], LOW);
      }
    } 

  }
  delay(100);
}
