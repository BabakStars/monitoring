#include"DHT.h"
#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<ESP8266HTTPClient.h>

ESP8266WebServer server(80);
IPAddress local_IP(192,168,1,150);
IPAddress subnet(255,255,255,0);

#define DHT_PIN D3
#define DHT_TYPE DHT11

int localTemp, localHum;

DHT dht(DHT_PIN,DHT_TYPE);

  
  
void setup() {
  
  delay(2000);
  Serial.begin(9600);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP,local_IP,subnet);
  WiFi.softAP("BabakStars","123456789");
  server.on("/",Root);
  server.begin();

}
void Root() {
   localTemp = dht.readTemperature();
   localHum =  dht.readHumidity();
   String TempS = String(localTemp);
   String HumS = String(localHum);
   
  server.send(200,"text/html","<meta http-equiv=\"refresh\" content=\"4\"> <h1>Babak Stars</h1><h2>Temperature and humidity monitoring of the DHT11 sensor</h2><h2>"+ TempS +"*C</h2> <h2>"+HumS+" %</h2>");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();


}
