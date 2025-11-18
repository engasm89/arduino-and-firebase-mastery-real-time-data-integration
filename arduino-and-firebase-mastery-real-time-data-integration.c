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

int main(void) { // Entry
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
} // End main

