#include <Wire.h>
#include <Adafruit_VL53L0X.h>

// Line sensor thresholds
const int pragAlb = 200;
const int pragNegru = 400;

// Line sensors
const short frontSensorPin = A0;
const short backSensorPin = A1;

// Motor driver pins
const short LmotorForward = 9;
const short LmotorBackward = 8;
const short Lena = 5; // ENA (PWM)
const short RmotorForward = 11;
const short RmotorBackward = 12;
const short Rena = 10; // ENB (PWM)

// Switch pin
const int switchPin = 7;
bool isRobotOn = false;

// Distance sensor
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
const int attackDistance = 325; // mm

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!lox.begin()) {
    Serial.println("Failed to initialize VL53L0X!");
    while (1);
  }

  // Motor pins
  pinMode(LmotorForward, OUTPUT);
  pinMode(LmotorBackward, OUTPUT);
  pinMode(Lena, OUTPUT);
  pinMode(RmotorForward, OUTPUT);
  pinMode(RmotorBackward, OUTPUT);
  pinMode(Rena, OUTPUT);

  // Sensor pins
  pinMode(frontSensorPin, INPUT);
  pinMode(backSensorPin, INPUT);

  // Switch pin
  pinMode(switchPin, INPUT_PULLUP);

  stopMotor();
}

void loop() {
  // Read switch ON/OFF (active LOW because of INPUT_PULLUP)
  isRobotOn = (digitalRead(switchPin) == LOW);

  if (!isRobotOn) {
    stopMotor();
    return;
  }

  // Read line sensors
  bool frontOnLine = analogRead(frontSensorPin) < pragAlb;
  bool backOnLine  = analogRead(backSensorPin) < pragAlb;

  // Read distance sensor
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  // === DECISION LOGIC ===
  if (backOnLine) {
    Serial.println("Back sensor sees edge. Moving forward.");
    moveForward();
  }
  else if (frontOnLine) {
    Serial.println("Front sensor sees edge. Moving backward.");
    moveBackward();
  }
  else if (measure.RangeStatus == 0 &&
           measure.RangeMilliMeter < attackDistance) {
    Serial.print("Opponent detected at ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm. Attacking!");
    moveForward();
  }
  else {
    Serial.println("No edge or opponent. Scanning...");
    spinInPlace();
  }

  delay(100);
}

// === MOTOR CONTROL FUNCTIONS ===

void moveForward() {
  digitalWrite(LmotorForward, HIGH);
  digitalWrite(LmotorBackward, LOW);
  analogWrite(Lena, 255);

  digitalWrite(RmotorForward, HIGH);
  digitalWrite(RmotorBackward, LOW);
  analogWrite(Rena, 255);
}

void moveBackward() {
  digitalWrite(LmotorForward, LOW);
  digitalWrite(LmotorBackward, HIGH);
  analogWrite(Lena, 200);

  digitalWrite(RmotorForward, LOW);
  digitalWrite(RmotorBackward, HIGH);
  analogWrite(Rena, 200);
}

void spinInPlace() {
  digitalWrite(LmotorForward, HIGH);
  digitalWrite(LmotorBackward, LOW);
  analogWrite(Lena, 200);

  digitalWrite(RmotorForward, LOW);
  digitalWrite(RmotorBackward, HIGH);
  analogWrite(Rena, 200);
}

void stopMotor() {
  digitalWrite(LmotorForward, LOW);
  digitalWrite(LmotorBackward, LOW);
  digitalWrite(RmotorForward, LOW);
  digitalWrite(RmotorBackward, LOW);
  analogWrite(Lena, 0);
  analogWrite(Rena, 0);
}
