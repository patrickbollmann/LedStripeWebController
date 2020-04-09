/*********
  author: Patrick Bollmann
  date:   16.02.2020
  email:  pbollman@mail.upb.de
*********/

// Load Wi-Fi library
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <ESP8266WiFi.h>
#include "FastLED.h"

#define NUM_LEDS 250
CRGB leds[NUM_LEDS];
#define DATA_PIN D1

// Replace with your network credentials
const char* ssid     = "your ssid";
const char* password = "your wifi password";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String currentState = "on";
String ledState = "off";

// Assign output variables to GPIO pins
const int output5 = D5;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void changeLeds(int r,int g,int b){
  for(int i = 0; i < NUM_LEDS; i = i + 1) {
    leds[i] = CRGB(r,g,b);
  }
  FastLED.show();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /lampon") >= 0) {
              Serial.println("Lamp on");
              currentState="on";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /lampoff") >= 0) {
              Serial.println("Lamp off");
              currentState="off";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /ledoff") >= 0) {
              Serial.println("LED off");
              ledState="off";
              changeLeds(0,0,0);
            } else if (header.indexOf("GET /ledon") >= 0) {
              Serial.println("LED on");
              ledState="on";
              changeLeds(255,255,255);
            } else if (header.indexOf("GET /farbe/pink") >= 0) {
              Serial.println("LED pink");
              ledState="on";
              changeLeds(255,0,230);
            }else if (header.indexOf("GET /farbe/lila") >= 0) {
              Serial.println("LED lila");
              ledState="on";
              changeLeds(196,0,255);
            }else if (header.indexOf("GET /farbe/blau") >= 0) {
              Serial.println("LED blau");
              ledState="on";
              changeLeds(0,0,255);
            }else if (header.indexOf("GET /farbe/cyan") >= 0) {
              Serial.println("LED cyan");
              ledState="on";
              changeLeds(0,255,255);
            }else if (header.indexOf("GET /farbe/gruen") >= 0) {
              Serial.println("LED gruen");
              ledState="on";
              changeLeds(0,255,0);
            }else if (header.indexOf("GET /farbe/lime") >= 0) {
              Serial.println("LED lime");
              ledState="on";
              changeLeds(50,205,50);
            }
            else if (header.indexOf("GET /farbe/gelb") >= 0) {
              Serial.println("LED gelb");
              ledState="on";
              changeLeds(255,255,0);
            }
            else if (header.indexOf("GET /farbe/orange") >= 0) {
              Serial.println("LED orange");
              ledState="on";
              changeLeds(255,165,50);
            }
            else if (header.indexOf("GET /farbe/rot") >= 0) {
              Serial.println("LED rot");
              ledState="on";
              changeLeds(255,0,0);
            }else if (header.indexOf("GET /farbe/weiss") >= 0) {
              Serial.println("LED weiss");
              ledState="on";
              changeLeds(255,255,255);
            }else if (header.indexOf("GET /helligkeit/10") >= 0) {
              Serial.println("Helligkeit 10");
              FastLED.setBrightness(25);
              FastLED.show();
            }else if (header.indexOf("GET /helligkeit/20") >= 0) {
              Serial.println("Helligkeit 20");
              FastLED.setBrightness(50);
              FastLED.show();
            }else if (header.indexOf("GET /helligkeit/30") >= 0) {
              Serial.println("Helligkeit 30");
              FastLED.setBrightness(75);
              FastLED.show();
            }else if (header.indexOf("GET /helligkeit/40") >= 0) {
              Serial.println("Helligkeit 40");
              FastLED.setBrightness(100);
              FastLED.show();
            }else if (header.indexOf("GET /helligkeit/50") >= 0) {
              Serial.println("Helligkeit 50");
              FastLED.setBrightness(125);
              FastLED.show();
            }else if (header.indexOf("GET /helligkeit/60") >= 0) {
              Serial.println("Helligkeit 60");
              FastLED.setBrightness(150);
              FastLED.show();
            }else if (header.indexOf("GET /helligkeit/70") >= 0) {
              Serial.println("Helligkeit 70");
              FastLED.setBrightness(175);
              FastLED.show();
            }else if (header.indexOf("GET /helligkeit/80") >= 0) {
              Serial.println("Helligkeit 80");
              FastLED.setBrightness(200);
              FastLED.show();
            }else if (header.indexOf("GET /helligkeit/90") >= 0) {
              Serial.println("Helligkeit 90");
              FastLED.setBrightness(225);
              FastLED.show();
            }else if (header.indexOf("GET /helligkeit/max") >= 0) {
              Serial.println("Helligkeit 100");
              FastLED.setBrightness(255);
              FastLED.show();
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the Buttons
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; width: 300px}");
            //client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println("button:hover {box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);}");
            //client.println(".button2 {background-color: #77878A;}");

            //der css bums fürs dropdown
            client.println(".dropbtn {background-color: #4CAF50;color: white;padding: 16px;font-size: 16px;border: none;cursor: pointer;}");
            client.println(".dropdown {position: relative;display: inline-block;}");
            client.println(".dropdown-content {display: none;position: absolute;background-color: #f9f9f9;min-width: 300px;box-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);z-index: 1;}");
            client.println(".dropdown-content a {color: black;padding: 12px 16px;text-decoration: none;display: block;}");
            client.println(".dropdown-content a:hover {background-color: #f1f1f1}");
            client.println(".dropdown:hover .dropdown-content {display: block;}");
            client.println(".dropdown:hover .dropbtn {background-color: #3e8e41;}");
            client.println("</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Bar</h1>");
            
            // Display current state, up down button  
            // If the output5State is off, it displays the ON button       
            if (currentState=="on") {
              client.println("<p><a href=\"/lampoff\"><button class=\"button\">Lampe ausschalten</button></a></p>");
            } else {
              client.println("<p><a href=\"/lampon\"><button class=\"button button2\">Lampe einschalten</button></a></p>");
            }
            if (ledState=="on") {
              client.println("<p><a href=\"/ledoff\"><button class=\"button\">LEDs ausschalten</button></a></p>");
            } else {
              client.println("<p><a href=\"/ledon\"><button class=\"button button2\">LEDs einschalten</button></a></p>");
            }
            //dropdown menue for selectring color
            client.println("<div class='dropdown'><button class='button'>Farbe</button><div class='dropdown-content'><a href=\'/farbe/pink\'>Pink</a><a href=\'/farbe/lila\'>Lila</a><a href=\'/farbe/blau\'>Blau</a><a href=\'/farbe/cyan\'>Cyan</a><a href=\'/farbe/gruen\'>Gruen</a><a href=\'/farbe/lime\'>Lime</a><a href=\'/farbe/gelb\'>Gelb</a><a href=\'/farbe/orange\'>Orange</a><a href=\'/farbe/rot\'>Rot</a><a href=\'/farbe/weiss\'>Weiss</a></div></div>");
            client.println("<p></p>");
            //dropdown menue for selectring brightness
            client.println("<div class='dropdown'><button class='button'>Helligkeit</button><div class='dropdown-content'><a href=\'/helligkeit/10\'>10%</a><a href=\'/helligkeit/20\'>20%</a><a href=\'/helligkeit/30\'>30%</a><a href=\'/helligkeit/40\'>40%</a><a href=\'/helligkeit/50\'>50%</a><a href=\'/helligkeit/60\'>60%</a><a href=\'/helligkeit/70\'>70%</a><a href=\'/helligkeit/80\'>80%</a><a href=\'/helligkeit/90\'>90%</a><a href=\'/helligkeit/max\'>100%</a></div></div>");
            client.println("<p></p>");
            
            
               
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
