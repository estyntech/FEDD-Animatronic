#include "motion.h"
#include "config.h"
#include <ESP32Servo.h>  // Install "ESP32Servo" by Kevin Harrington via Library Manager

static Servo headServo;
static Servo jawServo;

void initServos() {
  // Allocate PWM timers — ESP32Servo handles LEDC channel assignment
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);

  headServo.setPeriodHertz(50);  // Standard 50Hz servo signal
  jawServo.setPeriodHertz(50);

  headServo.attach(PIN_SERVO_HEAD, 500, 2400); // 500–2400µs pulse range
  jawServo.attach(PIN_SERVO_JAW,   500, 2400);

  setHeadAngle(HEAD_CENTER_DEG);
  setJawAngle(JAW_CLOSED_DEG);

  Serial.println("[MOTION] Servos initialized.");
}

void setHeadAngle(float degrees) {
  degrees = constrain(degrees, HEAD_MIN_DEG, HEAD_MAX_DEG);
  headServo.write((int)degrees);
}

void setJawAngle(float degrees) {
  degrees = constrain(degrees, JAW_CLOSED_DEG, JAW_OPEN_DEG);
  jawServo.write((int)degrees);
}
