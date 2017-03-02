# Arduino IoT

Unfortunatelly [Arduino UNO](https://www.arduino.cc/) is not equipped with WiFi. You have either to buy a suitable shield or you can use the [nodeMCU](http://www.nodemcu.com/index_en.html) 
>The Development Kit based on ESP8266, integates GPIO, PWM, IIC, 1-Wire and ADC all in one board. 

![](/assets/nodemcu_pins.png) 

[How to set-up NodeMCU on Arduino IDE ](https://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/) 

```c
#include <ESP8266WiFi.h>
 
const char* ssid = "AndreaAP";
const char* password = "pagepage";

const int AnalogIn  = A0;

int readingIn = 0;

 
int ledPin = 16; // GPIO16 D0 see 
WiFiServer server(80);
 
void setup() {
  Serial.begin(9600);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}
 
void loop() {


  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    Serial.println("Led HIGH");
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    Serial.println("Led LOW");
    value = LOW;
  }

  readingIn = analogRead(AnalogIn);
  Serial.println(readingIn);
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");

 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  
  readingIn = analogRead(AnalogIn);
  client.println("il valore della resistenza è:");
  client.println(readingIn);
  
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
  
}
```
