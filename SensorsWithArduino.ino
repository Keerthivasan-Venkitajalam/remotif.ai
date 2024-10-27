#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_MLX90614.h>

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;

Adafruit_MLX90614 mlx;

void onBeatDetected() {
    Serial.println("Beat!");
}

void setup() {
    Serial.begin(9600);
    Serial.print("Initializing pulse oximeter..");

    // Initialize the PulseOximeter instance
    // Failures are generally due to improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);  // Stop execution if initialization fails
    } else {
        Serial.println("SUCCESS");
    }
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Initialize MLX90614
    mlx.begin();

    // Setup for ECG lead off detection
    pinMode(10, INPUT);  // Lead-off detection LO +
    pinMode(11, INPUT);  // Lead-off detection LO -
}

void loop() {
    // Make sure to call update as fast as possible
    pox.update();

    // Report data every REPORTING_PERIOD_MS milliseconds
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        // Heart rate and SpO2 readings from Pulse Oximeter
        Serial.print("Heart rate: ");
        Serial.print(pox.getHeartRate());
        Serial.print(" bpm / SpO2: ");
        Serial.print(pox.getSpO2());
        Serial.println("%");

        // Read temperature from MLX90614 sensor
        float ambientTemp = mlx.readAmbientTempC();
        float objectTemp = mlx.readObjectTempC();

        Serial.print("Ambient Temperature: ");
        Serial.print(ambientTemp);
        Serial.println(" °C");

        Serial.print("Object Temperature: ");
        Serial.print(objectTemp);
        Serial.println(" °C");

        // Check ECG lead-off status
        if ((digitalRead(10) == 1) || (digitalRead(11) == 1)) {
            Serial.println('!');
        } else {
            // Read ECG analog value
            Serial.print("ECG Value: ");
            Serial.println(analogRead(A0));
        }

        // Update the timestamp for the next report
        tsLastReport = millis();
    }

    // Add delay if needed to prevent serial flooding
}
