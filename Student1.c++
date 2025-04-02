#include <Wire.h>

char receivedAnswer = '\0';

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize I2C communication as a slave
    Wire.begin(8); // Set the I2C address for this ESP32s2
    Wire.onReceive(receiveEvent); // Handle data received from master
    Wire.onRequest(requestEvent); // Handle data request from master

    Serial.println("Slave ready to receive and send data.");
}

void loop() {
    // Print the received answer for debugging
    if (receivedAnswer != '\0') {
        Serial.print("Received Answer: ");
        Serial.println(receivedAnswer);
        // Keep the received answer for the master to request
    }
    delay(100);
}

void receiveEvent(int bytes) {
    if (Wire.available()) {
        receivedAnswer = Wire.read(); // Read the received byte
    }
}

void requestEvent() {
    // Send the received answer back to the master
    Wire.write(receivedAnswer);
}