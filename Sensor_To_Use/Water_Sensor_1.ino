int sensorPin = A0; // Analog output pin of water sensor
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin); // Read analog value from sensor
  Serial.print("Water Sensor Value: ");
  Serial.println(sensorValue);         // Print the sensor value to Serial Monitor
  delay(1000);                        // Wait for 1 second
}
