// ESP8266 DS18B20 ArduinoIDE Thingspeak IoT Example code
// http://vaasa.hacklab.fi
//
// https://github.com/milesburton/Arduino-Temperature-Control-Library
// https://gist.github.com/jeje/57091acf138a92c4176a


#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D3
//#define THINKSPEAK
#define IFTTT //comment if program is for THINKSPEAK

#ifdef THINKSPEAK
const char* host = "api.thingspeak.com"; // Your domain  
String ApiKey = "CF2F86NC0P9N8A0N";
String path = "/update?key=" + ApiKey + "&field1=";  
#endif

#ifdef IFTTT
const char* host = "maker.ifttt.com"; // Your domain  
String ApiKey = "cY9InbZ8wg11C2wWtqBs68";
String path = "/trigger/NEW_TEMP/with/key/" + ApiKey + "?value1=" ;  
#endif

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

const char* ssid = "KT_GiGA_2G_C583";
const char* pass = "6bz31ed542";

char temperatureString[6];

void setup(void){
  Serial.begin(115200); //start the serial communication to send messages to the computer
  Serial.println("\n");

  /*****WIFI CONNECTION*****/
  WiFi.begin(ssid, pass); //connect to the network
  // Wait for connection (prints dot until WiFi is not connected)
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println("\n");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //sent the IP address of the ESP8266 to the computer

  /*****DS18B20 SETUP COMPLETED*****/
  DS18B20.begin();
}

float getTemperature() {
  float temp;
  do {
    DS18B20.requestTemperatures(); 
    temp = DS18B20.getTempCByIndex(0);

    #ifdef THINKSPEAK
    delay(60000);
    #endif

    #ifdef IFTTT
    delay(5000);
    #endif

  } while (temp == 85.0 || temp == (-127.0));
  return temp;
}


void loop() {

  float temperature = getTemperature();

  dtostrf(temperature, 2, 2, temperatureString);
  // send temperature to the serial console
  Serial.println(temperatureString);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  client.print(String("GET ") + path + temperatureString + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");
  delay(500);

}
