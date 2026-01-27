#include <AFMotor.h>
#include <Servo.h>

// --- Motors Setup for Normal Wheel System ---
AF_DCMotor MotorFL(2); AF_DCMotor MotorFR(1); 
AF_DCMotor MotorBL(3); AF_DCMotor MotorBR(4); 

// --- Weapons Setup ---
Servo cannonServo;   
Servo spikeServo;    
const int taserPin = A0; // Taser Relay on Analog Pin A0 [cite: 2026-01-18]

void setup() {
    Serial.begin(9600);
    
    pinMode(taserPin, OUTPUT);
    digitalWrite(taserPin, LOW); // Taser initial OFF [cite: 2026-01-18]
    
    // Default Max Speed
    SetSpeed(255); 
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        
        switch(command) {
            // --- Movement Controls ---
            case 'F': MoveForward(); break; 
            case 'B': MoveBackward(); break;
            case 'L': TurnLeft(); break;
            case 'R': TurnRight(); break;
            case 'S': StopMotors(); break;

            // --- DEADLY TASER/SHOCK ATTACK ---
            case 'X': // STUN GUN ON
                digitalWrite(taserPin, HIGH); [cite: 2026-01-18]
                break;
            case 'x': // STUN GUN OFF
                digitalWrite(taserPin, LOW); [cite: 2026-01-18]
                break;

            // --- CANNON ATTACK ---
            case 'K': 
                cannonServo.attach(9);
                cannonServo.write(180); delay(300);             
                cannonServo.write(0); delay(150);
                cannonServo.detach();  
                break;

            // --- REAR DEFENSE: SPIKES ---
            case 'W': 
                spikeServo.attach(10);
                spikeServo.write(110); delay(800);           
                spikeServo.write(0); delay(150);
                spikeServo.detach();   
                break;
        }
    }
}

// --- Normal Wheel Movement Logic ---
void MoveForward() {
    MotorFL.run(FORWARD); MotorFR.run(FORWARD);
    MotorBL.run(FORWARD); MotorBR.run(FORWARD);
}

void MoveBackward() {
    MotorFL.run(BACKWARD); MotorFR.run(BACKWARD);
    MotorBL.run(BACKWARD); MotorBR.run(BACKWARD);
}

void TurnLeft() {
    // Left wheel stop, Right wheel forward (Normal car turn)
    MotorFL.run(RELEASE); MotorBL.run(RELEASE);
    MotorFR.run(FORWARD); MotorBR.run(FORWARD);
}

void TurnRight() {
    // Right wheel stop, Left wheel forward
    MotorFL.run(FORWARD); MotorBL.run(FORWARD);
    MotorFR.run(RELEASE); MotorBR.run(RELEASE);
}

void StopMotors() {
    MotorFL.run(RELEASE); MotorFR.run(RELEASE);
    MotorBL.run(RELEASE); MotorBR.run(RELEASE);
}

void SetSpeed(int val) {
    MotorFL.setSpeed(val); MotorFR.setSpeed(val);
    MotorBL.setSpeed(val); MotorBR.setSpeed(val);
}
