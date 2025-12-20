#include <SoftwareSerial.h>

// Define SoftwareSerial pins for RYLR498
#define RX_PIN 10
#define TX_PIN 11

SoftwareSerial loraSerial(RX_PIN, TX_PIN); // RX, TX

// Here just initialize the value or give a name of each value 
// Configuration parameters     
const String networkID = "12";        // Network ID (0-16)
const String deviceAddress = "1";     // Device address (0-65535)
const String destinationAddress = "2"; // Destination address
const String frequency = "868000000"; // Frequency (EU: 868000000, US: 915000000)

void setup() {
  // Initialize serial communications
  Serial.begin(115200);
  loraSerial.begin(115200);
  
  Serial.println("LoRa RYLR498 Module Initialization");
  
  // Wait for module to initialize
  delay(2000);
  
  // Configure LoRa module
  configureLoRaModule();
  
  Serial.println("LoRa Module Ready!");
  Serial.println("Type message to send or wait to receive...");
}

void loop() {
  // Check if data is available to send from Serial Monitor
  if (Serial.available() > 0) {
    String message = Serial.readString();
    message.trim();
    sendMessage(message);
  }
  
  // Check if data is received from LoRa module
  if (loraSerial.available() > 0) {
    receiveMessage();
  }
  
  delay(100);
}

void configureLoRaModule() {
  // Reset module to factory defaults
  sendATCommand("AT+RESET");
  delay(2000);
  
  // Set network ID
  sendATCommand("AT+NETWORKID=" + networkID);
  
  // Set device address
  sendATCommand("AT+ADDRESS=" + deviceAddress);
  
  // Set frequency
  sendATCommand("AT+BAND=" + frequency);
  
  // Set parameters (optional)
  sendATCommand("AT+PARAMETER=7,7,1,8");
  
  delay(1000);
  // Save configuration
  sendATCommand("AT+SAVE");
  
  delay(1000);

}

void sendMessage(String message) {
  // Format: AT+SEND=<address>,<message>
  String command = "AT+SEND=" + destinationAddress + "," + message.length() + "," + message;
  sendATCommand(command);
  Serial.println("Sent: " + message);
}

void receiveMessage() {
  String response = loraSerial.readString();
  response.trim();
  
  // Check if it's a received message
  if (response.startsWith("+RCV=")) {
    // Parse received message format: +RCV=<addr>,<length>,<message>,<RSSI>,<SNR>
    int firstComma = response.indexOf(',');    // After address
    int secondComma = response.indexOf(',', firstComma + 1);  // After length
    int thirdComma = response.indexOf(',', secondComma + 1);  // After message
    
    if (firstComma != -1 && secondComma != -1 && thirdComma != -1) {
      String senderAddress = response.substring(5, firstComma);
      String messageLength = response.substring(firstComma + 1, secondComma);
      String message = response.substring(secondComma + 1, thirdComma);
      String rssi = response.substring(thirdComma + 1);
      
      Serial.println("Received from address " + senderAddress + ": " + message);
      Serial.println("RSSI: " + rssi + " dBm");
    }
  } else {
    Serial.println("Response: " + response);
  }
}

String sendATCommand(String command) {
  loraSerial.println(command);
  delay(100);
  
  String response = "";
  while (loraSerial.available()) {
    response += (char)loraSerial.read();
  }
  response.trim();
  
  if (response != "") {
    Serial.println("CMD: " + command);
    Serial.println("RES: " + response);
  }
  
  return response;
}
