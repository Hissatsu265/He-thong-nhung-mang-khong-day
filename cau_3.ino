#include <DHT.h>

#define DHTPIN A0       
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);
#include "painlessMesh.h"

#define   MESH_PREFIX     "Nhom06Mesh2"
#define   MESH_PASSWORD   "Nhom06Mesh2"
#define   MESH_PORT       5555

Scheduler userScheduler; 
painlessMesh  mesh;

void sendMessage() ; 

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {

  StaticJsonDocument<2048> data;
  JsonObject sensorData = data.createNestedObject("data");
  data["node"] = "1";
  // float temperature = dht.readTemperature();  
  // float humidity = dht.readHumidity();      
//-------------------------------------------------------------
  float temperature=random(25,27);
  float humidity=random(40,42);
//-------------------------------------------------------------
  sensorData["temp"] = String(temperature);
  sensorData["hum"] = String(humidity) ;
  String message;
  serializeJson(data, message);
  mesh.sendBroadcast( message );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  dht.begin();  
  Serial.begin(115200);
  randomSeed(analogRead(0));
  mesh.setDebugMsgTypes( ERROR | STARTUP );  

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop() {
  mesh.update();
}
