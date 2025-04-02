#include <Wire.h>
#include <Adafruit_SSD1306.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Button pins
const int buttonUp = 2;    // Pin for UP button
const int buttonDown = 3;  // Pin for DOWN button
const int buttonEnter = 4; // Pin for ENTER button

// Variables
char answers[] = {'A', 'B', 'C', 'D'};
int selectedAnswer = 0; // Index of the selected answer

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize I2C communication
    Wire.begin();

    // Initialize OLED display
    if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // Initialize buttons
    pinMode(buttonUp, INPUT_PULLUP);
    pinMode(buttonDown, INPUT_PULLUP);
    pinMode(buttonEnter, INPUT_PULLUP);

    // Display startup message
    displayMessage("Please select the\ncorrect answer");
}

void loop() {
    // Check button presses
    if (digitalRead(buttonUp) == LOW) {
        selectedAnswer = (selectedAnswer - 1 + 4) % 4; // Cycle through answers
        updateDisplay();
        delay(200); // Debounce delay
    }
    if (digitalRead(buttonDown) == LOW) {
        selectedAnswer = (selectedAnswer + 1) % 4; // Cycle through answers
        updateDisplay();
        delay(200); // Debounce delay
    }
    if (digitalRead(buttonEnter) == LOW) {
        sendCorrectAnswer();
        displayMessage("Answer sent!");
        delay(1000); // Wait before resetting
        displayMessage("Please select the\ncorrect answer");
    }
}

void updateDisplay() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Select Answer:");
    display.setCursor(0, 16);
    display.print(answers[selectedAnswer]);
    display.display();
}

void displayMessage(const char *message) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(message);
    display.display();
}

