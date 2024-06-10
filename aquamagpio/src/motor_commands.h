#include "motor_functions.h"
#include "user_inputs.h"
void stop_motor(AccelStepper* stepper) {
  reset_direction(stepper);
  stepper->stop();
  current_state = STOPPED;
  Serial.println("Motor stopped.");
  print_menu();
}

void start_motor(AccelStepper* stepper) {
  // print_debug_log();
  reset_direction(stepper);
  current_state = RUNNING;
  Serial.println("Motor started.");
  print_debug_log(stepper);
  
}



//todo fix speed to take in just a number or full command
void speed(AccelStepper* stepper, String command) {
  //Serial.println(command);
  int indexOfSpace = command.indexOf(' ');
      if (indexOfSpace != -1) {
        String speedString = command.substring(indexOfSpace + 1);
        float speedValue = speedString.toFloat();
        if (speedValue != 0.0 || speedString == "0" || speedString == "0.0") {
          set_speed(stepper, speedValue);
        } else {
          Serial.print(speedString);
          Serial.println(" is an invalid speed value.");
        }
      } else {
        Serial.println("Invalid command format. Use 'SPEED <value>'.");
    }
}

void move(AccelStepper* stepper, String command) {
  int indexOfSpace = command.indexOf(' ');
  if (indexOfSpace != -1) {
      String positionString = command.substring(indexOfSpace + 1);
      long position = positionString.toInt();
      move_to(stepper, position);
      Serial.println("new position to move to is: ");
      Serial.println(position);
      // stepper.setSpeed(motor_speed);
  } else {
      Serial.println("Invalid command format. Use 'MOVE <value>'.");
    }
}

void set(AccelStepper* stepper, String command) {
  int indexOfSpace = command.indexOf(' ');
  if (indexOfSpace != -1) {
    String distanceString = command.substring(indexOfSpace + 1);
    float distanceValue = distanceString.toFloat();
    if (distanceValue != 0.0 || distanceString == "0" || distanceString == "0.0") {
      set_home(stepper, distanceValue);
    } else {
      Serial.print(distanceString);
      Serial.println(" is an invalid distance value.");
    }
  } else {
    set_home(stepper, 0);
  }
}