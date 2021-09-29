
#include "index.h"
#include "conditions.h"


#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <WiFiClient.h>

WebServer server(80);


#include "FirebaseESP32.h"
FirebaseData firebasedata;

const int trigPin=5;
const int echoPin=18;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distance;
#define LED 2
int flag=0;
int visibility;
String timestamp;


double get_distance(){
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  

  // Calculate the distance
  distance = duration * SOUND_SPEED/2;
  // Prints the distance in the Serial Monitor
  //Serial.print("Ciao");
  Serial.print("Distance (cm): ");
  Serial.println(distance);
  Serial.print("\n");
  return distance;
}

int timezone=2;
int dst=0;

String get_timestamp(){
  String timestamp="";
  time_t now= time(nullptr);
  timestamp=String(ctime(&now));
  timestamp.remove(24);

  if (timestamp.endsWith("1970")){
    return"";
  }
  else{
    return timestamp;
  }
}

int get_visibility(){
  int visibility = 0;

  if (Firebase.getInt(firebasedata, "visibility")) {

    if (firebasedata.dataType() == "int") {
      visibility = firebasedata.intData();
      return visibility;
    }

  } else {
    //Failed, then print out the error detail
    Serial.println(firebasedata.errorReason());
  }}



 int mytimer(int timer1){
  static unsigned long t1,dt;
  int ret=0;
  dt=millis()-t1;
  if(dt>=500){
    t1=millis();
    ret=1;
    }
  return ret;
  }



   int mytimer2(int timer2){
  static unsigned long t1,dt;
  int ret=0;
  dt=millis()-t1;
  if(dt>=500){
    t1=millis();
    ret=1;
    }
  return ret;
  }

   int mytimer3(int timer){
  static unsigned long t1,dt;
  int ret=0;
  dt=millis()-t1;
  if(dt>=300){
    t1=millis();
    ret=1;
    }
  return ret;
  }
  
//Threshold for visibility
const int VISIBILITY_THRESHOLD=5000;

//Threshold for time
const int HOUR_THRESHOLD=17;

//Threshold for distance
const float DISTANCE_THRESHOLD=20;


//Webserver handle
void handle_index(){
  Serial.println("GET/index");
  server.send(200, "text/html", index_html_page());
}


void handle_conditions(){
  Serial.println("GET/conditions");
  server.send(200, "text/html", conditions_html_page(String(timestamp), String(visibility), String(distance), flag));
}

void handle_not_found(){
  server.send(404, "text/plain","404:Page not found!");
}


void setup() {
  
    Serial.begin(9600);
  //Wi-Fi connection setup
  WiFi.begin("Telecom-66766493", "cWSBQXDRzi92WlpXeZ2D6Nqy");
  Serial.println("");
  Serial.print("Connecting to "); Serial.print("Telecom-66766493");
  
  while (WiFi.status() != WL_CONNECTED) {
    if(mytimer(500)){
    Serial.print(".");
  }}
  //Serial.println("");
  Serial.print("Connected to ");  Serial.println("Telecom-66766493 ");
  //Serial.print("IP address: ");   Serial.println(WiFi.localIP());
  
   Serial.println("");

 //Firebase initialization
  Firebase.begin("https://provaled-5b6de-default-rtdb.firebaseio.com", "PFsA2WiSPzwKdBMRkRrwjwQMcNrgE75H31pXu4Or");
   Serial.println("");

    //Configuring timestamp function 
  configTime(timezone * 3600, dst * 0, "pool.ntp.org", "time.nist.gov");
  Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
     if(mytimer2(500)){
       Serial.print(".");
  }
  }
  Serial.print("Timestamp: "); Serial.println(get_timestamp());

  pinMode(LED,OUTPUT);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);

 //Server setup
  server.on("/", handle_index);
  server.on("/conditions.html", handle_conditions);
  server.onNotFound(handle_not_found);

  server.begin();
  Serial.print("HTTP server started at "); Serial.println(WiFi.localIP());
  
}

void loop(void) {

  //if(mytimer2(500)){
    server.handleClient();
    WiFiClient wifi_client;
  HTTPClient http_client;
  Serial.print("[HTTP] begin...\n");

  String timestamp=get_timestamp();
  String http_request = "http://api.openweathermap.org/data/2.5/weather?q=Firenze,it&appid=84bd5e5de7476ab4920522cb8bb41ccd";
  Serial.print("HTTP Request: "); Serial.println(http_request);
  if (http_client.begin(wifi_client, http_request)) {
    Serial.print("[HTTP] GET...\n");
    int http_code = http_client.GET();
    if (http_code > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", http_code);
      if (http_code == HTTP_CODE_OK || http_code == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload_resp = http_client.getString();
        Serial.println(payload_resp);
        payload_resp.remove(payload_resp.length()-1);
        
        
        //Serial.println(get_timestamp());
        String payload_to_Firebase = payload_resp + ",\"nave\":{\"time\":" + '"'+ timestamp.substring(11,19)+'"' + ",\"distance\":"+String(get_distance()) + "}}";  
        payload_to_Firebase.replace("[","");
        payload_to_Firebase.replace("]","");
        Serial.println("Payload for Firebase:"); Serial.println(payload_to_Firebase);
        FirebaseJson updateData;
        
        updateData.setJsonData(payload_to_Firebase);
        
        if(Firebase.updateNode(firebasedata, "/", updateData)){

          Serial.println("Correct update data");    
        }
        else { Serial.println(firebasedata.errorReason()); }
        
      }       
    }else{
      Serial.printf("[HTTP] GET... failed, error: %s\n", http_client.errorToString(http_code).c_str());
    }
    http_client.end();
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }

  visibility=get_visibility();
  int hour=timestamp.substring(11,13).toInt();
  
  
     if (distance<=DISTANCE_THRESHOLD) {
       if ((VISIBILITY_THRESHOLD>visibility || HOUR_THRESHOLD<hour)){
         digitalWrite(LED, HIGH); 
         delay(200); 
         digitalWrite(LED, LOW); 
         
     flag=2;
     }
     else{
      digitalWrite(LED,HIGH);
      flag=1;
      if (flag=!1){
        digitalWrite(LED,HIGH);
        flag=1;
      }
     }
     }
  if (distance>DISTANCE_THRESHOLD & (flag=!0)){
    digitalWrite(LED, LOW);
    flag=0;
  }
  server.send(200, "text/html", index_html_page());
  server.send(303);
  
  //}
  }
