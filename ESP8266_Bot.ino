#define ENA   5          // Enable/speed motors Right       GPIO5(D1)
#define ENB   12          // Enable/speed motors Left       GPIO12(D6)
#define IN_1  4         // L298N in1 motors Rightx          GPIO4(D2)
#define IN_2  0          // L298N in2 motors Right          GPIO0(D3)
#define IN_3  2           // L298N in3 motors Left          GPIO2(D4)
#define IN_4  14           // L298N in4 motors Left         GPIO14(D5)
#define backing_led 16 //pin = d0 of esp8266

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "Namai's Robo"; // CUSTOMIZE YOUR BOT NAME HERE 
ESP8266WebServer server(80);

void setup() {
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT); 
pinMode(IN_1, OUTPUT);
pinMode(IN_2, OUTPUT);
pinMode(IN_3, OUTPUT);
pinMode(IN_4, OUTPUT);
pinMode(backing_led, OUTPUT);
  Serial.begin(115200);
 // Connecting WiFi

 WiFi.mode(WIFI_AP);
 WiFi.softAP(ssid);

 IPAddress myIP = WiFi.softAPIP();
 Serial.print("AP IP address: ");
 Serial.println(myIP);
// Starting WEB-server
    server.on ( "/", HTTP_handleRoot );
    server.onNotFound ( HTTP_handleRoot );
    server.begin();   
}
void goAhead(){

     digitalWrite(IN_1, LOW);
     digitalWrite(IN_2, HIGH);
     analogWrite(ENA, speedCar);

     digitalWrite(IN_3, LOW);
     digitalWrite(IN_4, HIGH);
     analogWrite(ENB, speedCar);
     digitalWrite(backing_led, LOW);
 }

void goBack(){

     digitalWrite(IN_1, HIGH);
     digitalWrite(IN_2, LOW);
     analogWrite(ENA, speedCar);

     digitalWrite(IN_3, HIGH);
     digitalWrite(IN_4, LOW);
     analogWrite(ENB, speedCar);
     digitalWrite(backing_led, HIGH);
 }

void goRight(){

     digitalWrite(IN_1, HIGH);
     digitalWrite(IN_2, LOW);
     analogWrite(ENA, speedCar);

     digitalWrite(IN_3, LOW);
     digitalWrite(IN_4, HIGH);
     analogWrite(ENB, speedCar);
     digitalWrite(backing_led, LOW);
 }

void goLeft(){

     digitalWrite(IN_1, LOW);
     digitalWrite(IN_2, HIGH);
     analogWrite(ENA, speedCar);

     digitalWrite(IN_3, HIGH);
     digitalWrite(IN_4, LOW);
     analogWrite(ENB, speedCar);
     digitalWrite(backing_led, LOW);
 }

void stopRobot(){ 

     digitalWrite(IN_1, LOW);
     digitalWrite(IN_2, LOW);
     analogWrite(ENA, speedCar);

     digitalWrite(IN_3, LOW);
     digitalWrite(IN_4, LOW);
     analogWrite(ENB, speedCar);
     digitalWrite(backing_led, LOW);
}

void loop() {
   server.handleClient();
     command = server.arg("State");
     if (command == "F") goAhead();
     else if (command == "B") goBack();
     else if (command == "L") goLeft();
     else if (command == "R") goRight();
     else if (command == "I") goAheadRight();
     else if (command == "G") goAheadLeft();
     else if (command == "J") goBackRight();
     else if (command == "H") goBackLeft();
     else if (command == "0") speedCar = 400;
     else if (command == "1") speedCar = 470;
     else if (command == "2") speedCar = 540;
     else if (command == "3") speedCar = 610;
     else if (command == "4") speedCar = 680;
     else if (command == "5") speedCar = 750;
     else if (command == "6") speedCar = 820;
     else if (command == "7") speedCar = 890;
     else if (command == "8") speedCar = 960;
     else if (command == "9") speedCar = 1023;
     else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
      Serial.println(server.arg("State"));
 }
 server.send ( 200, "text/html", "" );
 delay(1);
}



