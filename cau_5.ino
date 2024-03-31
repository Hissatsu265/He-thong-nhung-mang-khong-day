#include <DHT.h>

#define DHTPIN 2       
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  
  dht.begin();         
}

void loop() {
  delay(2000); 

  float temperature = dht.readTemperature();  
  float humidity = dht.readHumidity();      

  Serial.print("Nhiệt độ: ");
  Serial.print(temperature);
  Serial.print(" °C, Độ ẩm: ");
  Serial.print(humidity);
  Serial.println(" %");
}