// Motor A connections
const int enA = 9;
const int in1 = 5;
const int in2 = 6;

// Motor B connections
const int enB = 10;
const int in3 = 7;
const int in4 = 8;

// Set the speed (0 = off and 255 = max speed)
const int motorSpeed = 128;

void setup() {
  Serial.begin(9600);

  // Set all motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  stop_all();

  // Set motor speeds
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);

  Serial.println("Enter w/a/s/d to move, x to stop:");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'd':
        Serial.println("Moving Forward");
        go_forward();
        break;
      case 'a':
        Serial.println("Moving Backward");
        go_backwards();
        break;
      case 's':
        Serial.println("Turning Left");
        go_left();
        break;
      case 'w':
        Serial.println("Turning Right");
        go_right();
        break;
      case 'x':
        Serial.println("Stopping");
        stop_all();
        break;
      default:
        Serial.println("Invalid command. Use w/a/s/d/x");
    }
  }
}

void go_forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void go_backwards() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void go_right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void go_left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stop_all() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
