#include <Smartcar.h>

//const int SIDE_FRONT_PIN = ; // you can use only analog enabled pins
const int TRIGGER_PIN    = 6; // D6
const int ECHO_PIN       = 7; // D7

ArduinoRuntime arduinoRuntime;
SR04 front(arduinoRuntime, TRIGGER_PIN, ECHO_PIN, 500);
//GP2D120 sideFrontIR(arduinoRuntime,SIDE_FRONT_PIN); // measure distances between 5 and 25 centimeters
BrushedMotor leftMotor(arduinoRuntime, smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(arduinoRuntime, smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);

const int fSpeed   = 70;  // 70% of the full speed forward
const int bSpeed   = -70; // 70% of the full speed backward
const int lDegrees = -75; // degrees to turn left
const int rDegrees = 75;  // degrees to turn right

SimpleCar car(control);
void setup()
{
    Serial.begin(9600); // start the serial
}

void loop()
{
    Serial.println(front.getDistance());
    if (front.getDistance() < 100)
    {
      if(front.getDistance() > 0){
          car.setSpeed(0);
       }
    }
    delay(100);
    handleInput();
}

void handleInput()
{ // handle serial input if there is any
    if (Serial.available())
    {
        char input = Serial.read(); // read everything that has been received so far and log down
                                    // the last entry
        switch (input)
        {
        case 'l': // rotate counter-clockwise going forward
            car.setSpeed(fSpeed);
            car.setAngle(lDegrees);
            break;
        case 'r': // turn clock-wise
            car.setSpeed(fSpeed);
            car.setAngle(rDegrees);
            break;
        case 'f': // go ahead
            car.setSpeed(fSpeed);
            car.setAngle(0);
            break;
        case 'b': // go back
            car.setSpeed(bSpeed);
            car.setAngle(0);
            break;
        default: // if you receive something that you don't know, just stop
            car.setSpeed(0);
            car.setAngle(0);
        }
    }
}
