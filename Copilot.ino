//=======================================================================================
//                                  Sender Code
//=======================================================================================

#include <SoftwareSerial.h>

SoftwareSerial LoRa(6, 5); // TX to RYLR498 RX, RX to RYLR498 TX

void setup() {
  Serial.begin(9600);
  LoRa.begin(115200); // Default baud rate for RYLR498

  LoRa.println("AT"); // Check connection
  delay(500);
  LoRa.println("AT+ADDRESS=1"); // Set device address
  delay(500);
  LoRa.println("AT+NETWORKID=100"); // Set network ID
  delay(500);
  LoRa.println("AT+BAND=865000000"); // Set frequency (India)
  delay(500);
}

void loop() {
  LoRa.println("AT+SEND=2,5,HELLO"); // Send "HELLO" to device with address 2
  delay(5000); // Wait before sending again
}



//========================================================================================
//                                     Receiver Code
//========================================================================================

#include <SoftwareSerial.h>

SoftwareSerial LoRa(6, 5); // TX to RYLR498 RX, RX to RYLR498 TX

void setup() {
  Serial.begin(9600);
  LoRa.begin(115200);

  LoRa.println("AT");
  delay(500);
  LoRa.println("AT+ADDRESS=2"); // Receiver address
  delay(500);
  LoRa.println("AT+NETWORKID=100");
  delay(500);
  LoRa.println("AT+BAND=865000000");
  delay(500);
}

void loop() {
  if (LoRa.available()) {
    String data = LoRa.readStringUntil('\n');
    Serial.println("Received: " + data);
  }
}
