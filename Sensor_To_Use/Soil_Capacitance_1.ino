// Capacitive Soil Moisture Sensor with Arduino

// Pin Definitions
const int sensorPin = A0;        // Analog output connected to A0
const int digitalPin = 2;        // Digital output connected to D2 (optional)

// Calibration values (adjust based on your sensor and soil type)
const int airValue = 850;        // Sensor value in air (dry)
const int waterValue = 400;      // Sensor value in water (wet)

// Variables
int sensorValue = 0;
int moisturePercent = 0;

void setup() {
  Serial.begin(9600);           // Initialize serial communication
  pinMode(digitalPin, INPUT);   // Set digital pin as input (optional)
  
  Serial.println("Capacitive Soil Moisture Sensor Test");
  Serial.println("====================================");
  delay(2000);
}

void loop() {
  // Read analog value from sensor
  sensorValue = analogRead(sensorPin);
  
  // Convert to moisture percentage (0-100%)
  moisturePercent = map(sensorValue, airValue, waterValue, 0, 100);
  
  // Constrain to 0-100% range
  moisturePercent = constrain(moisturePercent, 0, 100);
  
  // Display results
  Serial.print("Analog Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Moisture: ");
  Serial.print(moisturePercent);
  Serial.print("%");
  
  // Read digital output (optional)
  int digitalValue = digitalRead(digitalPin);
  Serial.print(" | Digital Output: ");
  Serial.println(digitalValue == HIGH ? "DRY" : "WET");
  
  // Moisture level indicator
  if(moisturePercent < 30) {
    Serial.println("Status: Soil is DRY - Water needed!");
  } 
  else if(moisturePercent >= 30 && moisturePercent < 70) {
    Serial.println("Status: Soil moisture is ADEQUATE");
  } 
  else {
    Serial.println("Status: Soil is WET");
  }
  
  Serial.println("------------------------------------");
  
  delay(1000);  // Wait 1 second before next reading
}
