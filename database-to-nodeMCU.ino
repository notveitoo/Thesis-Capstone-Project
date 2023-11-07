#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define ON_Board_LED D4  // Defining an On Board LED D4, used for indicators when the process of connecting and connected to internet

const int relay = D1; // Defines a relay Pin (D1)

//SSID and Password of your WiFi router.
const char* ssid = ""; //--> wifi SSID.
const char* password = ""; //--> wifi password.

//Web Server address / IPv4 ipconfig
String host_or_IPv4 = "";

String Destination = "";
String URL_Server = "";
String getData = "";
String payloadGet = "";

//If webhost server is using https instead of http. Use the codes "webhost with ssl.txt"
HTTPClient http; // Declare object of class HTTPClient
WiFiClient client;
//----------------------------------------

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); // Connect to WiFi router
    
  pinMode(ON_Board_LED,OUTPUT); // On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); // Turn off Led On Board

  pinMode(relay,OUTPUT); // Door lock port Direction output

  //Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //
  }
  digitalWrite(ON_Board_LED, LOW); // Turn on the On Board LED when it is connected to the wifi router.
}

void loop() {
  //The first run of this program will not connect immediately it will take a few seconds for the nodeMCU to connect tpo the WiFi but after that the code will run smoothly
  //Getting Data from MySQL Database
  int id = 0; // ID in Database 
  getData = "ID=" + String(id);
  Destination = "system-cea/GetData.php";
  URL_Server = host_or_IPv4 + Destination;
  http.begin(client, URL_Server); // Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  int httpCodeGet = http.POST(getData); // Send the request
  payloadGet = http.getString();
  Serial.println(payloadGet); // Print request response payload

  if (payloadGet == "0") {//if false door will lock
    digitalWrite(relay, LOW); //--> Turn on realay
  }
  if (payloadGet == "1") {//if true door will unlock
    digitalWrite(relay, HIGH); //--> Turn off relay
  }
    http.end(); //--> Close connection
}
