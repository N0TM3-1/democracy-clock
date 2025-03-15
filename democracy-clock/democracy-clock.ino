#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "questions.h"

#define SENS A0

const char* ssid = "Alarm";
const char* password = "getAlarmedLol";

ESP8266WebServer server(80); // Create a web server on port 80

void handleRoot() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Simple Question Page</title>
    <style>
        /* Global styles */
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
            background-color: #F5F7FA;
            color: #333;
        }
        h1 {
            text-align: center;
            color: #2C3E50;
            margin-bottom: 30px;
            font-size: 2.2rem;
        }
        /* Radio buttons styling */
        ul {
            list-style-type: none;
            padding: 0;
            max-width: 400px;
            margin: 0 auto;
        }
        li {
            margin-bottom: 15px;
            padding: 12px 15px;
            background: white;
            border-radius: 8px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
            transition: transform 0.2s, box-shadow 0.2s;
        }
        li:hover {
            transform: translateY(-2px);
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
        }
        input[type="radio"] {
            margin-right: 10px;
            transform: scale(1.3);
            accent-color: #3498DB;
        }
        label {
            font-size: 1.1rem;
            cursor: pointer;
            display: inline-block;
            width: calc(100% - 30px);
        }
        /* Color indicators */
        label[for="color1"]:after {
            content: "■";
            color: #E74C3C;
            margin-left: 10px;
        }
        label[for="color2"]:after {
            content: "■";
            color: #3498DB;
            margin-left: 10px;
        }
        label[for="color3"]:after {
            content: "■";
            color: #2ECC71;
            margin-left: 10px;
        }
        label[for="color4"]:after {
            content: "■";
            color: #F1C40F;
            margin-left: 10px;
        }
        /* Selected state styling */
        input[type="radio"]:checked + label {
            font-weight: bold;
        }
        input[type="radio"]:checked + label:before {
            content: "✓ ";
            color: #3498DB;
        }
    </style>
</head>
<body>
    <h1>What's your favorite color?</h1>
    <ul>
        <li><input type="radio" id="option1" name="option" value=%VALUE1%><label for="option1">%VALUE1%</label></li>
        <li><input type="radio" id="option2" name="option" value=%VALUE2%><label for="option2">%VALUE2%</label></li>
        <li><input type="radio" id="option3" name="option" value=%VALUE3%><label for="option3">%VALUE3%</label></li>
        <li><input type="radio" id="option4" name="option" value=%VALUE4%><label for="option4">%VALUE4%</label></li>
    </ul>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);  // Send the page to the client
}

void handleSubmit(){
  Serial.println("BUTTON CLICKED");
}

void setup() {
  pinMode(SENS, INPUT);
  Serial.begin(115200);

  randomSeed(analogRead(SENS));
  int num = random(50);

  // Set ESP8266 as an Access Point
  WiFi.softAP(ssid, password);
  
  Serial.println("Access Point Started!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());  // Print the IP address (default is usually 192.168.4.1)

  // Define routes
  server.on("/", handleRoot);
  server.on("/answer", handleSubmit);
  
  server.begin();
  Serial.println("Web Server Started!");

}

void loop() {
  server.handleClient();
}