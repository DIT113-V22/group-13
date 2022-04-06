#include <Smartcar.h>
void handleInput() { //handle serial input if there is any
  if (Serial.available()) {
    char input;
    Serial.setTimeout(100);
    while (bluetooth.available()) { input = Serial.read() }; //read till last character
    switch (input) {
      case 'l': //rotate counter-clockwise going forward
        car.setSpeed(80); //80% of the full speed
        car.setAngle(-75); //75 degrees to the left
        break;
      case 'r': //turn clock-wise
        car.setSpeed(80);
        car.setAngle(75);  //75 to the right
        break;
      case 'f': //go ahead
        car.setSpeed(100);
        car.setAngle(0);
        break;
      case 'b': //go back
        car.setSpeed(-100);
        car.setAngle(0);
        break;
      default: //if you receive something that you don't know, just stop
        car.setSpeed(0);
        car.setAngle(0);
    }
  }
}
