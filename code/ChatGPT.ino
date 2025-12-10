//==========================================================================
//                          Sender Code
//==========================================================================
// Sender_RYLR498.ino
#include <SoftwareSerial.h>

const uint8_t LORA_RX = 10; // Arduino reads from module TX
const uint8_t LORA_TX = 11; // Arduino writes to module RX
SoftwareSerial loraSerial(LORA_RX, LORA_TX);

const unsigned long PERIODIC_MS = 10000; // periodic send every 10s
unsigned long lastMillis = 0;
int messageCounter = 0;

void setup() {
  Serial.begin(9600);
  while(!Serial) { }
  Serial.println(F("RYLR498 Sender starting..."));

  loraSerial.begin(9600); // change if your module uses a different baud
  Serial.println(F("Type a message and press Enter to send via LoRa."));
}

void loop() {
  // Send from Serial Monitor -> LoRa
  if (Serial.available()) {
    String s = Serial.readStringUntil('\n');
    s.trim();
    if (s.length() > 0) {
      sendLoRa(s);
      Serial.print(F("Sent: "));
      Serial.println(s);
    }
  }

  // Periodic test packet (simulate sensor data)
  if (millis() - lastMillis >= PERIODIC_MS) {
    lastMillis = millis();
    messageCounter++;
    String pkt = String("SENSOR:") + messageCounter + ",temp=" + String(25 + (messageCounter % 5));
    sendLoRa(pkt);
    Serial.print(F("Periodic sent: "));
    Serial.println(pkt);
  }

  // Optional: read any responses from LoRa module (if remote replies)
  if (loraSerial.available()) {
    String incoming = loraSerial.readStringUntil('\n');
    incoming.trim();
    if (incoming.length()) {
      Serial.print(F("From LoRa module: "));
      Serial.println(incoming);
    }
  } // for reciver 
}

void sendLoRa(const String &msg) {
  // Add newline terminator to help receiver parse packets
  loraSerial.print(msg);
  loraSerial.print('\n');
}


//========================================================================================
//                               Receiver Code
//========================================================================================
// Receiver_RYLR498.ino
#include <SoftwareSerial.h>

const uint8_t LORA_RX = 10; // Arduino reads from module TX
const uint8_t LORA_TX = 11; // Arduino writes to module RX
SoftwareSerial loraSerial(LORA_RX, LORA_TX);

void setup() {
  Serial.begin(9600);
  while(!Serial) { }
  Serial.println(F("RYLR498 Receiver starting..."));

  loraSerial.begin(9600); // match sender/module baud
  Serial.println(F("Waiting for LoRa packets..."));
}

void loop() {
  // Read data from LoRa module and print
  if (loraSerial.available()) {
    String packet = loraSerial.readStringUntil('\n');
    packet.trim();
    if (packet.length()) {
      Serial.print(F("Received: "));
      Serial.println(packet);

      // Example: send acknowledgement back
      String ack = String("ACK:") + packet.length();
      loraSerial.print(ack);
      loraSerial.print('\n');
      Serial.print(F("Sent ack: "));
      Serial.println(ack);
    }
  }

  // Read from USB serial and forward to LoRa (optional)
  if (Serial.available()) {
    String out = Serial.readStringUntil('\n');
    out.trim();
    if (out.length()) {
      loraSerial.print(out);
      loraSerial.print('\n');
      Serial.print(F("Forwarded to LoRa: "));
      Serial.println(out);
    }
  }
}
