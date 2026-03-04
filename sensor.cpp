#include "sensor.h"
#include "config.h"
// claude generated
#include <Wire.h>
#include <VL53L0X.h>   // Pololu VL53L0X library (install via Arduino Library Manager)

static VL53L0X sensor;

bool initSensor() {
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  sensor.setTimeout(500);

  if (!sensor.init()) {
    Serial.println("[SENSOR] ERROR: VL53L0X not found on I2C bus!");
    return false;
  }

  // High speed mode: ~20ms timing budget (sufficient for this application)
  sensor.setMeasurementTimingBudget(20000);
  sensor.startContinuous();
  Serial.println("[SENSOR] VL53L0X initialized OK.");
  return true;
}

int readDistanceMM() {
  uint16_t dist = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred() || dist >= 8190) {
    return -1; // Out of range or error
  }
  return (int)dist;
}
