int analogPin = A0;
int analogVal;
int LED[12] = {4,5,6,7,8,9,10,11,12,13};
int num_of_led = 10;
int chunk = 100; 

void setup(){
pinMode(analogPin, INPUT);
for (int i = 0; i<num_of_led; i++){
pinMode(LED[i], OUTPUT);
}      
Serial.begin(9600);
}
void loop(){
analogVal = analogRead(analogPin);
Serial.println(analogVal);  
int value = analogRead(analogPin);
if(value>170 ){
  digitalWrite(4, HIGH);  
}else{
  digitalWrite(4, LOW);
}
delay(30);
//---------------------------
if(value>175 ){
  digitalWrite(5, HIGH);  
}else{
  digitalWrite(5, LOW);
}
delay(30);
//-------------------------
if(value>180 ){
  digitalWrite(6, HIGH);  
}else{
  digitalWrite(6, LOW);
}
delay(40);
//=---------------------
if(value>190 ){
  digitalWrite(7, HIGH);  
}else{
  digitalWrite(7, LOW);
}
delay(50);
if(value>195 ){
  digitalWrite(8, HIGH);  
}else{
  digitalWrite(8, LOW);
}
delay(50);
//=---------------------
if(value>200 ){
  digitalWrite(9, HIGH);  
}else{
  digitalWrite(9, LOW);
}
delay(50);
//=---------------------
if(value>205 ){
  digitalWrite(10, HIGH);  
}else{
  digitalWrite(10, LOW);
}
delay(50);
//=---------------------
if(value>210 ){
  digitalWrite(11, HIGH);  
}else{
  digitalWrite(11, LOW);
}
delay(50);
//=---------------------
if(value>215 ){
  digitalWrite(12, HIGH);  
}else{
  digitalWrite(12, LOW);
}
delay(60);
//=---------------------
if(value>220 ){
  digitalWrite(13, HIGH);  
}else{
  digitalWrite(13, LOW);
}
delay(60);

}