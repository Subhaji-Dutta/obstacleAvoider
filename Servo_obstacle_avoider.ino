#include <Servo.h>

// Define servos
Servo leftMotor;
Servo rightMotor;
Servo sensorMotor;

// Define ultrasonic sensor pins
const int trigPin = 4;
const int echoPin = 7;

// Define servo pins
const int leftMotorPin = 5;
const int rightMotorPin = 6;
const int sensorMotorPin = 3;

void setup() {
    Serial.begin(9600);
    leftMotor.attach(leftMotorPin);
    rightMotor.attach(rightMotorPin);
    sensorMotor.attach(sensorMotorPin);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    sensorMotor.write(90); // Start with sensor facing forward
    delay(1000);
}

// Function to get distance
int getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    int duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2; // Convert to cm
}

// Function to move forward
void moveForward() {
    leftMotor.write(170); // Adjust speed for 360-degree servos
    rightMotor.write(10);
}

// Function to move backward
void moveBackward() {
    leftMotor.write(10);
    rightMotor.write(170);
    delay(500);
}

// Function to turn left
void turnLeft() {
    leftMotor.write(10);
    rightMotor.write(10);
    delay(500);
}

// Function to turn right
void turnRight() {
    leftMotor.write(170);
    rightMotor.write(170);
    delay(500);
}

void stopMoving() {
    leftMotor.write(90);
    rightMotor.write(90);
}

void loop() {
    int frontDistance = getDistance();
    
    if (frontDistance < 20) { // If obstacle is detected
        stopMoving();
        delay(500);

        moveBackward(); // Move back a little
        stopMoving();
        
        // Scan left and right
        sensorMotor.write(30);
        delay(500);
        int leftDistance = getDistance();
        
        sensorMotor.write(150);
        delay(500);
        int rightDistance = getDistance();
        
        sensorMotor.write(90); // Reset to center
        delay(500);
        
        // Choose the best direction
        if (leftDistance > rightDistance) {
            turnLeft();
        } else {
            turnRight();
        }
    } else {
        moveForward();
    }
}
