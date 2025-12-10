// Pin definitions
const int sensorPin = A0;      // Analog output pin connected to A0
const int digitalPin = 2;      // Digital output pin connected to D2 (optional)

// Calibration values (adjust based on your sensor and soil)
const int dryValue = 1023;     // Sensor value in dry soil
const int wetValue = 300;      // Sensor value in wet soil

void setup() {
  Serial.begin(9600);          // Initialize serial communication
  pinMode(digitalPin, INPUT);  // Set digital pin as input
  Serial.println("Soil Moisture Sensor Test");
  Serial.println("-------------------------");
}

void loop() {
  // Read analog value
  int sensorValue = analogRead(sensorPin);
  
  // Calculate moisture percentage
  int moisturePercent = map(sensorValue, dryValue, wetValue, 0, 100);
  moisturePercent = constrain(moisturePercent, 0, 100);
  
  // Read digital value
  int digitalValue = digitalRead(digitalPin);
  
  // Display readings
  Serial.print("Analog Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Moisture: ");
  Serial.print(moisturePercent);
  Serial.print("%");
  
  // Display soil condition
  if (moisturePercent < 30) {
    Serial.print(" | Status: Dry - Water needed!");
  } else if (moisturePercent < 70) {
    Serial.print(" | Status: Moist - Good condition");
  } else {
    Serial.print(" | Status: Wet - Too much water");
  }
  
  Serial.print(" | Digital: ");
  Serial.println(digitalValue == HIGH ? "DRY" : "WET");
  
  delay(1000);  // Wait 1 second before next reading
}
