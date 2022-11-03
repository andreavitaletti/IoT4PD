/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
const int ledPin =  D0;       // the number of the LED pin. GPIO16

int sensorValue = 0;  // value read from the pot

void setup() {
  // initialize serial communication at 115200
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(115200);
}

void loop() {
  // read the analog in value
  sensorValue = analogRead(analogInPin);
 
  // print the readings in the Serial Monitor
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\n");

  if (sensorValue < 512) {
  digitalWrite(ledPin, HIGH);
  }
  else digitalWrite(ledPin, LOW);
  delay(1000);
}
