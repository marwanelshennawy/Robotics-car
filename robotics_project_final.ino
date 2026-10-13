#include "AFMotor_R4.h"
#include <SoftwareSerial.h>

SoftwareSerial bluetooth_serial(9, 10); // RX, TX

AF_DCMotor motor_fl(1);
AF_DCMotor motor_bl(2);
AF_DCMotor motor_br(3);
AF_DCMotor motor_fr(4);

int current_speed = 255;   // global speed
int running_command = 6;

void setup() {
  bluetooth_serial.begin(9600);
  pinMode(A0,INPUT_PULLUP);
  pinMode(A5,INPUT_PULLUP);

  set_speed(current_speed);
  stop();
}

void loop() {
  bool front_obstacle_detected = digitalRead(A5) == LOW;
  bool back_obstacle_detected = digitalRead(A0) == LOW;

  if(front_obstacle_detected && (running_command==1 || running_command==7 || running_command==8)){
    if (running_command != 6)
      stop();
  }
  if (back_obstacle_detected && (running_command==2 || running_command==9 || running_command==10)){
    if (running_command != 6)
      stop();
  }

  if (bluetooth_serial.available()) {

    String command = bluetooth_serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();   

    switch (getCommand(command)) {

      case 1: (front_obstacle_detected)? stop() : forward(); break;
      case 2: (back_obstacle_detected)? stop() : backward(); break;
      case 3: right(); break;
      case 4: left(); break;
      case 6: stop(); break;

      case 7: (front_obstacle_detected)? stop() : forward_right(); break;
      case 8: (front_obstacle_detected)? stop() : forward_left(); break;
      case 9: (back_obstacle_detected)? stop() : backward_right(); break;
      case 10: (back_obstacle_detected)? stop() : backward_left(); break;

      case 11:if (running_command != 6) set_speed(51); break;
      case 12:if (running_command != 6) set_speed(102); break;
      case 13:if (running_command != 6) set_speed(153); break;
      case 14:if (running_command != 6) set_speed(204); break;
      case 15:if (running_command != 6) set_speed(255); break;

      default: break;
    }
  }
}

int getCommand(String cmd) {
  if (cmd == "forward") return 1;
  if (cmd == "backward") return 2;
  if (cmd == "right") return 3;
  if (cmd == "left") return 4;
  if (cmd == "stop") return 6;

  if (cmd == "forward_r") return 7;
  if (cmd == "forward_l") return 8;
  if (cmd == "backward_r") return 9;
  if (cmd == "backward_l") return 10;

  if (cmd == "l1") return 11;
  if (cmd == "l2") return 12;
  if (cmd == "l3") return 13;
  if (cmd == "l4") return 14;
  if (cmd == "l5") return 15;

  return 0;
}

void set_speed(int speed) {
  current_speed = speed;
  motor_fl.setSpeed(speed);
  motor_bl.setSpeed(speed);
  motor_br.setSpeed(speed);
  motor_fr.setSpeed(speed);
}

void forward() {
  set_speed(current_speed);
  motor_fl.run(FORWARD);
  motor_bl.run(FORWARD);
  motor_br.run(FORWARD);
  motor_fr.run(FORWARD);
  running_command = 1;
}

void backward() {
  set_speed(current_speed);
  motor_fl.run(BACKWARD);
  motor_bl.run(BACKWARD);
  motor_br.run(BACKWARD);
  motor_fr.run(BACKWARD);
  running_command = 2;
}

void right() {
  set_speed(current_speed);
  motor_fl.run(FORWARD);
  motor_bl.run(FORWARD);
  motor_br.run(BACKWARD);
  motor_fr.run(BACKWARD);
  running_command = 3;
}

void left() {
  set_speed(current_speed);
  motor_fl.run(BACKWARD);
  motor_bl.run(BACKWARD);
  motor_br.run(FORWARD);
  motor_fr.run(FORWARD);
  running_command = 4;
}

void stop() {
  motor_fl.run(RELEASE);
  motor_bl.run(RELEASE);
  motor_br.run(RELEASE);
  motor_fr.run(RELEASE);
  running_command = 6;
}

void forward_right() {
  motor_fl.setSpeed(current_speed);
  motor_bl.setSpeed(current_speed);
  motor_br.setSpeed(current_speed / 2); 
  motor_fr.setSpeed(current_speed / 2);

  motor_fl.run(FORWARD);
  motor_bl.run(FORWARD);
  motor_br.run(FORWARD);
  motor_fr.run(FORWARD);

  running_command = 7;
}

void forward_left() {
  motor_br.setSpeed(current_speed);
  motor_fr.setSpeed(current_speed);
  motor_bl.setSpeed(current_speed / 2); 
  motor_fl.setSpeed(current_speed / 2);

  motor_br.run(FORWARD);
  motor_fr.run(FORWARD);
  motor_fl.run(FORWARD);
  motor_bl.run(FORWARD);

  running_command = 8;
}

void backward_right() {
  motor_fl.setSpeed(current_speed);
  motor_bl.setSpeed(current_speed);
  motor_br.setSpeed(current_speed / 2);
  motor_fr.setSpeed(current_speed / 2);

  motor_fl.run(BACKWARD);
  motor_bl.run(BACKWARD);
  motor_br.run(BACKWARD);
  motor_fr.run(BACKWARD);

  running_command = 9;
}

void backward_left() {
  motor_br.setSpeed(current_speed);
  motor_fr.setSpeed(current_speed);
  motor_fl.setSpeed(current_speed / 2);
  motor_bl.setSpeed(current_speed / 2);

  motor_fl.run(BACKWARD);
  motor_bl.run(BACKWARD);
  motor_br.run(BACKWARD);
  motor_fr.run(BACKWARD);

  running_command = 10;
}
