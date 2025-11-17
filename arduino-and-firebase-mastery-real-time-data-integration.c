#include <stdio.h> // Include I/O for telemetry
#include <unistd.h> // Include sleep for timing

// Simulated sensor value and Firebase publish
static int sensor = 0; // Initialize sensor value

// Program entry simulating real-time Firebase integration
int main(void) { // Begin main function
  printf("Arduino & Firebase Mastery: Real-time Data Integration\n"); // Header
  for (int i = 0; i < 8; ++i) { // Loop to publish frames
    sensor = i * 10; // Simulate sensor update
    printf("POST https://firebase.example/db/sensor -> {\"value\":%d}\n", sensor); // Show POST intent
    usleep(500000); // Delay 500 ms
  } // End loop
  return 0; // Return success
} // End main

