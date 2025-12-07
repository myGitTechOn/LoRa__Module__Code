// ==================================================================================================
//                                        Sender Code
// ==================================================================================================
#include <SoftwareSerial.h>
SoftwareSerial lora(2, 3);  // RX, TX

String lora_band = "433000000";  // Adjust to your frequency
String lora_networkid = "5";
String lora_address = "1";       // Transmitter address
String lora_rx_address = "2";    // Receiver address

void setup() {
  Serial.begin(115200);
  lora.begin(115200);
  delay(1500);
  lora.println("AT+BAND=" + lora_band);
  delay(500);
  lora.println("AT+NETWORKID=" + lora_networkid);
  delay(500);
  lora.println("AT+ADDRESS=" + lora_address);
  delay(1000);
}

void loop() {
  String message = "HELLO";
  lora.println("AT+SEND=" + lora_rx_address + "," + String(message.length()) + "," + message);
  Serial.println("Sent: " + message);
  delay(5000);
}



//======================================================================================
//                                   Receiver Code
//=====================================================================================

#include <SoftwareSerial.h>
SoftwareSerial lora(2, 3);  // RX, TX

String lora_band = "433000000";  // Match transmitter
String lora_networkid = "5";
String lora_address = "2";       // Receiver address

void setup() {
  Serial.begin(115200);
  lora.begin(115200);
  delay(1500);
  lora.println("AT+BAND=" + lora_band);
  delay(500);
  lora.println("AT+NETWORKID=" + lora_networkid);
  delay(500);
  lora.println("AT+ADDRESS=" + lora_address);
  delay(1000);
}

void loop() {
  if (lora.available()) {
    String incoming = lora.readString();
    Serial.println("Received: " + incoming);
  }
}
