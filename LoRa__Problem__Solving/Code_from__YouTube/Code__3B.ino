//=============================================== Receiver Code =======================================================

//--------------------------------------------------------------------------------------------------------------

#include <SoftwareSerial.h>

#define RX 3
#define TX 2
SoftwareSerial LoRaSerial(RX, TX); // RX, TX

void setup() {
  Serial.begin(115200); // Initialize USB Serial
  delay(1000);
  
  LoRaSerial.begin(115200); // Initialize Software Serial
  
}

void loop() {
  // Check if data is available on USB Serial
  while (Serial.available()) {
    String data = Serial.readString();
    LoRaSerial.println(data); // Send data to Software Serial

    //Serial.flush() //is very slow
  }

  // Check if data is available on Software Serial
  while (LoRaSerial.available()) {
    String data = LoRaSerial.readString();
    Serial.println(data); // Send data to USB Serial

    //LoRaSerial.flush();
  }
}

//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------





//=================================================  Sender Code ===========================================

//-------------------------------------------------------------------------------------------------------

#include <SoftwareSerial.h>

#define RX 3
#define TX 2
SoftwareSerial LoRaSerial(RX, TX); // RX, TX

const int ledPin = 13;
unsigned long lastTransmitTime = 0;

void setup() {
  Serial.begin(115200); // Initialize USB Serial
  delay(1000);
  
  LoRaSerial.begin(115200); // Initialize Software Serial

  pinMode(ledPin, OUTPUT);
  
}

void loop() {
  if (millis() - lastTransmitTime >= 1000) {
    lastTransmitTime = millis();
    digitalWrite(ledPin, HIGH);
    delay(100);

    LoRaSerial.println("AT+SEND=2,5,Hello"); // Send data

    digitalWrite(ledPin, LOW); // Turn off sender LED
  }
}


//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------

//==============================================================================================================
