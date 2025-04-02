#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

// Thresholds for tilt detection (adjust based on sensitivity)
const float TILT_THRESHOLD = 0.5; // Experiment with this value (e.g., 0.3 to 1.0)

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true); // Calibrate gyro (keep sensor still)
  Serial.println("MPU6050 Car Control Ready!");
}

void loop() {
  mpu6050.update();
  
  float accX = mpu6050.getAccX(); // Forward/Backward
  float accY = mpu6050.getAccY(); // Left/Right

  char command = 'X'; // Default: Stop
  float value = 0.0;  // Magnitude of tilt

  // Determine direction
  if (accX > TILT_THRESHOLD) {
    command = 'W'; // Forward
    value = accX;
  } 
  else if (accX < -TILT_THRESHOLD) {
    command = 'S'; // Backward
    value = abs(accX);
  } 
  else if (accY > TILT_THRESHOLD) {
    command = 'A'; // Left
    value = accY;
  } 
  else if (accY < -TILT_THRESHOLD) {
    command = 'D'; // Right
    value = abs(accY);
  }

  // Send command + value to Serial
  Serial.print(command);
  Serial.print("(");
  Serial.print(value, 2); // 2 decimal places
  Serial.println(")");

  delay(100); // Adjust delay for responsiveness
}