
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <DabbleESP32.h>

#if __has_include(<esp_arduino_version.h>)
#include <esp_arduino_version.h>
#endif

// ---------------- MOTOR PINS ----------------

// Left motor
#define IN1 32
#define IN2 33
#define ENA 27

// Right motor
#define IN3 25
#define IN4 26
#define ENB 13

// ---------------- PWM SETTINGS ----------------

#define PWM_FREQ 1000
#define PWM_RES  8

#define MIN_DUTY 100
#define MAX_DUTY 255

int speedDuty = 180;
const int STEP = 35;

// ---------------- PWM COMPATIBILITY ----------------

void pwmWriteMotor(int pin, int channel, int duty) {
  duty = constrain(duty, 0, 255);

#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(pin, duty);
#else
  ledcWrite(channel, duty);
#endif
}

void pwmSetupMotor(int pin, int channel) {
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(pin, PWM_FREQ, PWM_RES);
#else
  ledcSetup(channel, PWM_FREQ, PWM_RES);
  ledcAttachPin(pin, channel);
#endif
}

// ---------------- MOTOR CONTROL ----------------

void setMotor(int in1, int in2, int en,
              int channel, float speed) {

  speed = constrain(speed, -1.0, 1.0);

  if (speed == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    pwmWriteMotor(en, channel, 0);
    return;
  }

  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  int duty = MIN_DUTY +
             abs(speed) * (speedDuty - MIN_DUTY);

  duty = constrain(duty, MIN_DUTY, speedDuty);

  pwmWriteMotor(en, channel, duty);
}

void drive(float leftSpeed, float rightSpeed) {
  setMotor(IN1, IN2, ENA, 0, leftSpeed);
  setMotor(IN3, IN4, ENB, 1, rightSpeed);
}

void stopMotors() {
  drive(0, 0);
}

// ---------------- SPEED CONTROL ----------------

void updateSpeed() {

  if (GamePad.isTrianglePressed()) {
    speedDuty += STEP;
    speedDuty = min(speedDuty, MAX_DUTY);
    delay(180);
  }

  if (GamePad.isCrossPressed()) {
    speedDuty -= STEP;
    speedDuty = max(speedDuty, MIN_DUTY);
    delay(180);
  }
}

// ---------------- SETUP ----------------

void setup() {

  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pwmSetupMotor(ENA, 0);
  pwmSetupMotor(ENB, 1);

  stopMotors();

  Dabble.begin("UGV_ESP32");

  Serial.println("UGV Ready!");
}

// ---------------- MAIN LOOP ----------------

void loop() {

  Dabble.processInput();

  updateSpeed();

  float leftSpeed = 0;
  float rightSpeed = 0;

  // -------- JOYSTICK MODE --------

  int x = GamePad.getXaxisData();
  int y = GamePad.getYaxisData();

  if (GamePad.getRadius() > 0) {

    float forward = y / 7.0;
    float turn = x / 7.0;

    const float TURN_GAIN = 0.8;

    leftSpeed  = forward + turn * TURN_GAIN;
    rightSpeed = forward - turn * TURN_GAIN;

    leftSpeed = constrain(leftSpeed, -1.0, 1.0);
    rightSpeed = constrain(rightSpeed, -1.0, 1.0);

  }

  // -------- D-PAD MODE --------

  else {

    if (GamePad.isUpPressed()) {
      leftSpeed = 1;
      rightSpeed = 1;
    }

    else if (GamePad.isDownPressed()) {
      leftSpeed = -1;
      rightSpeed = -1;
    }

    else if (GamePad.isLeftPressed()) {
      leftSpeed = -1;
      rightSpeed = 1;
    }

    else if (GamePad.isRightPressed()) {
      leftSpeed = 1;
      rightSpeed = -1;
    }

    // -------- SPIN BUTTONS --------

    if (GamePad.isSquarePressed()) {
      leftSpeed = -1;
      rightSpeed = 1;
    }

    if (GamePad.isCirclePressed()) {
      leftSpeed = 1;
      rightSpeed = -1;
    }
  }

  // -------- DRIVE --------

  drive(leftSpeed, rightSpeed);

  delay(20);
}
