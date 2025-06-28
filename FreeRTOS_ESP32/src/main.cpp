#include <Arduino.h>

// Task handles to manage each task
TaskHandle_t ledTask1;
TaskHandle_t ledTask2;

// Set LED pins
const int ledPin1 = 2;
const int ledPin2 = 4;

void setup() {
  Serial.begin(115200);

  // Set LED pins as output
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // Create the first task on core 0
  xTaskCreatePinnedToCore(
    ledBlink1,       // Function that will run in the task
    "LED_Task_1",    // Task name (just a label)
    10000,           // Stack size
    NULL,            // No input parameters
    1,               // Priority level
    &ledTask1,       // Task handle to control the task
    0                // Run on core 0
  );
  delay(500); // Small delay before creating the next task

  // Create the second task on core 1
  xTaskCreatePinnedToCore(
    ledBlink2,
    "LED_Task_2",
    10000,
    NULL,
    1,
    &ledTask2,
    1 // Run this one on core 1
  );
  delay(500);
}

// Task 1: Turns LED on/off every 1 second
void ledBlink1(void *pvParameters) {
  Serial.print("Running LED Task 1 on core ");
  Serial.println(xPortGetCoreID());

  while (true) {
    digitalWrite(ledPin1, HIGH); // Turn LED on
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait 1 second
    digitalWrite(ledPin1, LOW);  // Turn LED off
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait 1 second
  }
}

// Task 2: Turns LED on/off every 700 milliseconds
void ledBlink2(void *pvParameters) {
  Serial.print("Running LED Task 2 on core ");
  Serial.println(xPortGetCoreID());

  while (true) {
    digitalWrite(ledPin2, HIGH); // Turn LED on
    vTaskDelay(700 / portTICK_PERIOD_MS); // Wait 700ms
    digitalWrite(ledPin2, LOW);  // Turn LED off
    vTaskDelay(700 / portTICK_PERIOD_MS); // Wait 700ms
  }
}

// Empty loop (not used because we use FreeRTOS tasks)
void loop() {
}
