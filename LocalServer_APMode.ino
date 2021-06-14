#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <Arduino.h>


 
const char* wifi_network_ssid = "Samsung";
const char* wifi_network_password =  "lamv9350";
 
const char *soft_ap_ssid = "MyESP32";
const char *soft_ap_password = "123456789";
volatile int ledPin = 17; 
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
String message="hello from esp";
String cloudmsg="hello from cloud esp";

int flag=0,ack=200;

AsyncWebServer server(80);
 
 
void setup() {
 pinMode(ledPin, OUTPUT);
 Serial.begin(115200);
 WiFi.mode(WIFI_MODE_APSTA);
 WiFi.softAP(soft_ap_ssid, soft_ap_password);
 
  WiFi.begin(wifi_network_ssid, wifi_network_password);
 
 
  while (WiFi.status() != WL_CONNECTED) {
    if(flag==40){break;}
    delay(500);
    Serial.println("Connecting to WiFi..");
    flag++;
  }
  if(flag>=40){WiFi.disconnect();
  ack =0;}

 
 Serial.print("ESP32 IP as soft AP: ");
 Serial.println(WiFi.softAPIP());
 
  Serial.print("ESP32 IP on the WiFi network: ");
  Serial.println(WiFi.localIP());
  
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", message);  
  } );

  server.on(
    "/post",HTTP_POST | HTTP_GET,[](AsyncWebServerRequest * request){},NULL,
    [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) 
    {
      message = (char*)data;
      message=message.substring(0,len);
      Serial.println(message);
      ack=0;
      Serial.println();
      if(message=="ON")
      {digitalWrite(17,HIGH);}
      else if(message=="OFF")
      {digitalWrite(17,LOW);}
      request->send(200, "text/plain", message);
      ack=httpPost("http://gradprojcomm.pythonanywhere.com/face",message);
  });
  server.begin();
 
}
 
void loop() {

if(flag<40 && ack==200)  
{
message=httpGet("http://gradprojcomm.pythonanywhere.com/face");
{
if(message=="b\'ON\'" && ack==200)
{digitalWrite(17,HIGH);}
else if(message=="b\'OFF\'" && ack==200)
{digitalWrite(17,LOW);}
}
}
}

 /* 
server.on("/hello", HTTP_GET, [](AsyncWebServerRequest * request) {
 
    if (ON_STA_FILTER(request)) {
      request->send(200, "text/plain", "Hello from STA");
      return;
 
    } else if (ON_AP_FILTER(request)) {
      request->send(200, "text/plain", "Hello from AP");
      return;
    }
 
    request->send(200, "text/plain", "Hello from undefined");
  } );
 */
