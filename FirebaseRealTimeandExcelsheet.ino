#include <WiFiNINA.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_MLX90614.h>
#include "Firebase_Arduino_WiFiNINA.h"

// Replace with your Firebase project credentials
#define DATABASE_URL "https://health-care-monitoring-s-5e9d4-default-rtdb.firebaseio.com/"
#define DATABASE_SECRET "DC1ANEAlQ5jTqdx3HHlHI4yl59qIC4kSMHtOO061"

// Firebase data object
FirebaseData fbdo;

#define REPORTING_PERIOD_MS 1000  // Data reporting interval

Adafruit_MLX90614 mlx = Adafruit_MLX90614();  // Temperature sensor
PulseOximeter pox;  // Pulse oximeter sensor
uint32_t tsLastReport = 0;

// Wi-Fi credentials
const char* ssid = "NotUrs";         // Your Wi-Fi SSID
const char* password = "keerthivv";  // Your Wi-Fi password

String path = "/Patient Data";  // Firebase path to store data

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, password);
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // Initialize Firebase
  Firebase.begin(DATABASE_URL, DATABASE_SECRET, ssid, password);
  Firebase.reconnectWiFi(true);

  Serial.println("Setting up sensors");

  // Initialize Pulse Oximeter
  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
    Serial.println("FAILED to initialize pulse oximeter.");
    while (1);  // Halt execution if sensor fails
  } else {
    Serial.println("SUCCESS.");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);  // Set LED current for pulse oximeter

  // Initialize MLX90614 temperature sensor
  Wire.begin();
  if (!mlx.begin()) {
    Serial.println("MLX90614 temperature sensor initialization failed!");
    while (1);  // Halt execution if sensor fails
  } else {
    Serial.println("MLX90614 temperature sensor initialized.");
  }
}

void loop() {
  // Update pulse oximeter data
  pox.update();

  // Report data every REPORTING_PERIOD_MS milliseconds
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    float heartRate = pox.getHeartRate();
    float SpO2Value = pox.getSpO2();
    float ecg = analogRead(A0);  // Read ECG value from analog pin A0

    if (heartRate > 0 && SpO2Value > 0) {
      Serial.print("Heart rate: ");
      Serial.print(heartRate);
      Serial.print(" bpm / SpO2: ");
      Serial.print(SpO2Value);
      Serial.println("%");

      // Measure temperature using MLX90614
      float temperature = mlx.readAmbientTempC();
      Serial.print("Object Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");

      // Upload data to Firebase
      uploadToFirebase(heartRate, SpO2Value, temperature, ecg);
    } else {
      Serial.println("Invalid Heart rate or SpO2 values");
    }

    tsLastReport = millis();  // Reset the reporting timer
  }
}

// Function to upload sensor data to Firebase
void uploadToFirebase(float heartRate, float SpO2Value, float temperature, float ecg) {
  // Upload Heart rate
  if (Firebase.setFloat(fbdo, path + "/Heart", heartRate)) {
    Serial.println("Heart rate uploaded to Firebase");
  } else {
    Serial.println("Error uploading Heart rate: " + fbdo.errorReason());
  }

  // Upload SpO2
  if (Firebase.setFloat(fbdo, path + "/Spo2", SpO2Value)) {
    Serial.println("SpO2 uploaded to Firebase");
  } else {
    Serial.println("Error uploading SpO2: " + fbdo.errorReason());
  }

  // Upload temperature
  if (Firebase.setFloat(fbdo, path + "/Temp", temperature)) {
    Serial.println("Temperature uploaded to Firebase");
  } else {
    Serial.println("Error uploading temperature: " + fbdo.errorReason());
  }

  // Upload ECG data
  if (Firebase.setFloat(fbdo, path + "/ECG", ecg)) {
    Serial.println("ECG uploaded to Firebase");
  } else {
    Serial.println("Error uploading ECG: " + fbdo.errorReason());
  }
}
