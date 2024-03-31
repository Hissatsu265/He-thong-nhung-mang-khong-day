#define USE_ARDUINO_INTERRUPTS true
// Include necessary libraries
#include <PulseSensorPlayground.h>
 
// Constants
const int PULSE_SENSOR_PIN = 0;  // Analog PIN where the PulseSensor is connected
const int LED_PIN = 13;          // On-board LED PIN
const int THRESHOLD = 580;       // Threshold for detecting a heartbeat
const int analogPin = A0; 
// Create PulseSensorPlayground object
PulseSensorPlayground pulseSensor;

void setup() {
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.
  pulseSensor.analogInput(PULSE_SENSOR_PIN);
  pulseSensor.blinkOnPulse(LED_PIN);
  pulseSensor.setThreshold(THRESHOLD);
 
  if (pulseSensor.begin()) 
  {
    Serial.println("PulseSensor object created successfully!");
  }

}

void loop() {#include <Wire.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const int ledPin = 13;
char FIREBASE_AUTH[] = "5c9OZCwDnOrguU1jt380tRY0yLhBBudrY00ohIyt";
char FIREBASE_HOST[] = "yoll-afab3-default-rtdb.firebaseio.com";
int MAX_WIFI_NETWORKS = 0; 
int reallength=0;
char WIFI_SSID[10][20];
char WIFI_PASSWORD[10][20]; 

FirebaseData firebaseData;

const long utcOffsetInSeconds = 7 * 3600; 
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

int isFirsttime=0;
int indexxx=0;
int heart_max=0;
int heart_min=300;
int heart_aver=0;
int timell=0;
String idboard="123t";
String mys2 = "";
float aver;

void setup() {
  Serial.begin(9600);
  MAX_WIFI_NETWORKS = 2; 
  addWiFiCredentials("UiTiOt-E3.1","UiTiOtAP");
  addWiFiCredentials("UiTiOt-E3.1","hiTiOtAP");
  connectToWiFi();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  timeClient.begin();
  timeClient.update();
}

void loop() {
  
  if (WiFi.status() != WL_CONNECTED) {
      connectToWiFi();
  }

  if (Firebase.getString(firebaseData, "/change_id/oldid")) {
    String oldid = firebaseData.stringData();
    if(oldid == idboard){
        Firebase.getString(firebaseData, "/change_id/newid");
        Firebase.setString(firebaseData, "/change_id/oldid","");
        idboard=firebaseData.stringData();
        Firebase.getString(firebaseData, "/change_id/ssid");
        String ssidFromFirebase = firebaseData.stringData();
        char ssid[20];
        ssidFromFirebase.toCharArray(ssid, sizeof(ssid));

        Firebase.getString(firebaseData, "/change_id/pass");
        String passFromFirebase = firebaseData.stringData();
        char pass[20];
        if(ssid!=""){
            passFromFirebase.toCharArray(pass, sizeof(pass));
            Serial.println(pass);
            addWiFiCredentials(ssid, pass);
        }
        
    }
  } 
//-----------------------------------------------------------------------------------------------------------------------
  if (Serial.available() > 0) {
    String data1 = Serial.readStringUntil('\n');
    String data2 = Serial.readStringUntil('\n');
    Serial.print("Received data from Arduino: ");
    Serial.println(data1+" "+data2);
    int n=data1.toInt();
    int m=data2.toInt();

    if(n>heart_max){heart_max=n;}
    if(n<heart_min){heart_min=n;}
    timell=1+timell;
    heart_aver=heart_aver+n;  

    data2=String(m);
    mys2=mys2+"y"+data2;
    indexxx=0;
  }
  else{
    indexxx+=1;
  }
  if(indexxx==100 && mys2.length()>15){
    
    //------------------------------------------------------------
    timeClient.update();

    String currentTime = timeClient.getFormattedTime();
    
    time_t rawTime = timeClient.getEpochTime();
    struct tm *timeinfo;
    timeinfo = localtime(&rawTime);

    int currentDay = timeinfo->tm_mday;
    int currentMonth = timeinfo->tm_mon + 1;  
    int currentYear = timeinfo->tm_year + 1900; 
    String currentDate = String(currentDay) + "/" + String(currentMonth) + "/" + String(currentYear);
    Serial.println("Current time: " + currentTime +"  "+ currentDate );
    Firebase.setString(firebaseData, "/data/time", currentTime +"  "+ currentDate);
    Firebase.setString(firebaseData, "/data/id",idboard);
    float t=heart_aver / timell;
    Firebase.setInt(firebaseData, "/data/heart_max",heart_max);
    Firebase.setInt(firebaseData, "/data/heart_min",heart_min);
    Firebase.setFloat(firebaseData, "/data/heart_aver",t);
    Serial.println(t);
    Firebase.setString(firebaseData, "/data/signal",mys2);
    
    //----------------------------------------------------------------
    mys2="";
    indexxx=0;
    heart_max=0;
    heart_min=300;
    heart_aver=0;
    timell=0;

  }  
//----------------------------------------------------------------------------------------------------------------------  
  delay(20);
}
//----------------------------------------------------------------------------------------
void addWiFiCredentials(const char* ssid, const char* password) {
  if (MAX_WIFI_NETWORKS < 10) { 
    strcpy(WIFI_SSID[MAX_WIFI_NETWORKS], ssid);
    strcpy(WIFI_PASSWORD[MAX_WIFI_NETWORKS], password);
    MAX_WIFI_NETWORKS++;
    Serial.println("WiFi credentials added successfully");
  } else {
    strcpy(WIFI_SSID[reallength], ssid);
    strcpy(WIFI_PASSWORD[reallength], password);
    reallength++;
    if(reallength==10){
      reallength=0;
    }
    Serial.println("WiFi credentials added successfully");
  }
}

void connectToWiFi() {
  for (int i = MAX_WIFI_NETWORKS-1; i >=0; i--) {
    Serial.print("Connecting to WiFi: ");
    Serial.println(WIFI_SSID[i]);
    WiFi.begin(WIFI_SSID[i], WIFI_PASSWORD[i]);

    int attempts = 10;
    while (WiFi.status() != WL_CONNECTED && attempts--) {
      delay(1000);
      Serial.println("Still connecting");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("\nConnected to WiFi Success!");
      Serial.println(WIFI_SSID[i]);
      break; 
    } else 
    {
      WiFi.disconnect();
      Serial.println("\nConnection failed.");
      if (i > 0) {
        Serial.println("Trying the next WiFi network...");
      } else {
        Serial.println("All WiFi networks failed. Waiting for the next attempt...");
        delay(5000); 
        connectToWiFi();
      }
    }
  }
}

  


