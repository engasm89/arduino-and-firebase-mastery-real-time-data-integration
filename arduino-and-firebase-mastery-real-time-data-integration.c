/*
 * Course: Arduino And Firebase Mastery Real Time Data Integration
 * Platform: Arduino
 * Author: Ashraf S A AlMadhoun
 * 
 * Description:
 * This code demonstrates the core concepts taught in the "Arduino And Firebase Mastery Real Time Data Integration" course.
 * It provides a practical implementation that students can study, modify, and
 * use as a foundation for their own projects.
 * 
 * Learning Objectives:
 * - Understand the fundamental principles covered in this course
 * - Practice implementing the concepts with real code
 * - Build a working example that can be extended
 * 
 * Hardware Requirements:
 * - Development board (Arduino)
 * - Components as specified in CIRCUIT.md
 * - USB cable for programming
 * 
 * Pin Connections:
 * Refer to CIRCUIT.md for detailed wiring diagrams and pin assignments.
 * 
 * Usage:
 * 1. Review the code structure and comments
 * 2. Connect hardware according to CIRCUIT.md
 * 3. Upload code to your development board
 * 4. Monitor serial output for debugging
 * 
 * Course Link: https://www.udemy.com/course/arduino-and-firebase-mastery-real-time-data-integration/
 * Repository: https://github.com/engasm89/arduino-and-firebase-mastery-real-time-data-integration
 * 
 * Copyright (c) 2025 Ashraf S A AlMadhoun
 * Licensed under MIT License
 */

// Simulate real-time Firebase integration with JSON payloads and backoff on errors
#include <stdio.h> // Telemetry logs
#include <unistd.h> // Sleep between posts

static int sensor = 0; // Sensor value
static int backoff_ms = 200; // Initial backoff

int firebase_post(const char* path, int value) { // POST to Firebase (simulated)
  if (!path) return 0; // Validate path
  printf("POST https://firebase.example%s -> {\"value\":%d}\n", path, value); // Log POST
  int ok = (value % 3 != 0); // Simulate occasional failure
  if (!ok) printf("ERROR: network failure\n"); // Error log
  return ok; // Success flag
}

int main(void) { // Program entry point
  printf("Arduino & Firebase Mastery: Real-time Data Integration\n"); // Header
  for (int i = 0; i < 20; ++i) { // More frames
    sensor = (i * 7) % 100; // Rolling sensor value
    int ok = firebase_post("/db/sensor", sensor); // Attempt publish
    if (!ok) { // On error, back off and retry once
      usleep(backoff_ms * 1000); // Backoff sleep
      backoff_ms = backoff_ms < 5000 ? backoff_ms * 2 : 5000; // Exponential backoff
      firebase_post("/db/sensor", sensor); // Retry
    } // End error path
    usleep(200000); // 200ms normal interval
  } // End loop
  return 0; // Success
} // End of main function

