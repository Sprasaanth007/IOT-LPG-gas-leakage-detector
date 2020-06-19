#include <Wire.h>
#include <ESP8266WiFi.h>

const int gaspin = A0;
float value;

const char* ssid = "VIT7G";
const char* password = "9445110110";
const char* host = "maker.ifttt.com";

void setup()
{
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
    WiFiClient client; 
    const int httpPort = 80;  
    if (!client.connect(host, httpPort))
    {
      Serial.println("Connection failed");
      return;
    }

    value = analogRead(gaspin);

    if(value>700)                         //Range of measurement of gas concentration in MQ2 gas sensor os 700 to 2000ppm
    {
      Serial.println("Gas leakage detected");
      String url = "/trigger/Fall_detection/with/key/dc5i3Z9nrI--xJ0EQMdga4";
      Serial.print("Requesting URL: ");
      Serial.println(url);
      client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                                    "Host: " + host + "\r\n" +   
                                           "Connection: close\r\n\r\n"); 
    }
}
