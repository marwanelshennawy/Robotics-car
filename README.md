# Bluetooth-Controlled 4-Wheel Robot with Obstacle Detection

An Arduino-based four-wheel robot controlled wirelessly via Bluetooth. The robot supports forward and backward movement, left and right turns, diagonal movement, five speed levels, and automatic stopping when an obstacle is detected in its direction of travel.

## Features

- **Bluetooth Control:** Receives movement commands wirelessly through a Bluetooth serial connection.
- **Four-Wheel Drive:** Controls four DC motors using the `AFMotor_R4` library.
- **Multiple Movement Modes:** Supports forward, backward, left, right, and diagonal movements.
- **Five Speed Levels:** Adjusts motor speed using commands `L1` through `L5`.
- **Obstacle Detection:** Uses front and rear sensors to stop the robot when an obstacle is detected in the direction of movement.
- **Startup Safety:** Releases all motors when the Arduino starts.

## Hardware Requirements

- Arduino board compatible with the selected motor driver and libraries.
- Motor driver compatible with `AFMotor_R4`.
- Four DC motors and a four-wheel robot chassis.
- Bluetooth serial module, such as HC-05 or HC-06.
- Two obstacle detection sensors.
- Suitable motor power supply.
- Jumper wires and connecting cables.
- Bluetooth-enabled smartphone or computer.

## System Overview

The robot operates through the following process:

1. A smartphone or computer sends a movement command over Bluetooth.
2. The Arduino receives the command through a software serial connection.
3. The command is translated into a movement or speed adjustment.
4. The motor driver controls the four DC motors.
5. Front and rear obstacle sensors are checked continuously.
6. If an obstacle is detected while the robot is moving toward it, the motors are stopped.

## Pin Configuration

| Component | Pin / Connection | Description |
|---|---|---|
| Bluetooth RX on Arduino | Pin 9 | Receives data from the Bluetooth module's TX |
| Bluetooth TX on Arduino | Pin 10 | Sends data to the Bluetooth module's RX |
| Front obstacle sensor | A5 | Detects obstacles in front of the robot |
| Rear obstacle sensor | A0 | Detects obstacles behind the robot |
| Front-left motor | M1 | Controls the front-left wheel |
| Back-left motor | M2 | Controls the back-left wheel |
| Back-right motor | M3 | Controls the back-right wheel |
| Front-right motor | M4 | Controls the front-right wheel |

**Important:** Verify the motor driver, Arduino board, and library compatibility before wiring the hardware. Connect the grounds together, check the Bluetooth module's logic-voltage requirements, and provide a suitable motor power supply.

## Bluetooth Commands

The robot receives text commands through Bluetooth at **9600 baud**.

| Command | Function |
|---|---|
| `forward` | Move forward |
| `backward` | Move backward |
| `right` | Turn right |
| `left` | Turn left |
| `forward_r` | Move diagonally forward-right |
| `forward_l` | Move diagonally forward-left |
| `backward_r` | Move diagonally backward-right |
| `backward_l` | Move diagonally backward-left |
| `stop` | Stop all motors |
| `l1` | Set speed to 20% |
| `l2` | Set speed to 40% |
| `l3` | Set speed to 60% |
| `l4` | Set speed to 80% |
| `l5` | Set speed to 100% |

Commands are case-insensitive, and surrounding whitespace is removed before processing.

**Note:** Each command must end with a newline character (`\n`). Configure your Bluetooth terminal application to append a newline when sending commands.

## Speed Control

The robot uses a PWM speed range from 0 to 255.

| Level | PWM Value | Nominal Percentage |
|---|---:|---:|
| L1 | 51 | 20% |
| L2 | 102 | 40% |
| L3 | 153 | 60% |
| L4 | 204 | 80% |
| L5 | 255 | 100% |

The default speed is 255. During diagonal movement, the motors on one side operate at half the configured speed to produce a curved trajectory.

**Implementation detail:** Speed-level commands are processed only when the robot is not stopped. To change the speed while stopped, the corresponding condition in the source code must be modified.

Actual motor speed and robot movement depend on the motor characteristics, battery voltage, wheel traction, and chassis design.

## Obstacle Detection

The robot uses two obstacle sensors:

- **Front sensor (A5):** Prevents forward, forward-left, and forward-right movement when an obstacle is detected.
- **Rear sensor (A0):** Prevents backward, backward-left, and backward-right movement when an obstacle is detected.

Both sensor pins are configured using `INPUT_PULLUP`. The code interprets a `LOW` reading as obstacle detection.

When an obstacle is detected during movement in the corresponding direction, the robot calls the `stop()` function to release all four motors.

The current implementation does not block ordinary left or right turning based on obstacle readings. Its obstacle detection should be treated as a basic safety feature rather than a complete collision-avoidance system.

## Software Requirements

- Arduino IDE
- `AFMotor_R4` library
- `SoftwareSerial` library, where supported by the selected board
- Bluetooth serial terminal or compatible controller application

The `AFMotor_R4` library must be installed and compatible with the specific Arduino board and motor driver being used. `SoftwareSerial` availability depends on the board architecture.

## Installation and Setup

1. Assemble the robot chassis and connect the four motors to the motor driver.
2. Connect the Bluetooth module to Arduino pins 9 and 10.
3. Connect the front obstacle sensor to A5 and the rear obstacle sensor to A0.
4. Install the required libraries in the Arduino IDE.
5. Open the Arduino sketch.
6. Select the correct Arduino board and port.
7. Upload the program.
8. Pair your smartphone or computer with the Bluetooth module.
9. Open a Bluetooth serial terminal configured for 9600 baud and newline-terminated commands.
10. Test the `stop` command and then test the movement commands in a clear area at low speed.

## Suggested Repository Structure

```text
bluetooth-controlled-robot/
├── README.md
└── robot.ino
```

Save the Arduino source code as `robot.ino`, or use another descriptive filename.

Consider adding a wiring diagram, hardware photographs, and a demonstration video to make the project easier to understand and reproduce.

## Future Improvements

- Implement a command timeout to stop the robot if Bluetooth communication is interrupted.
- Add sensor validation and more robust obstacle handling.
- Allow speed adjustment while the robot is stopped.
- Add battery-voltage monitoring.
- Document the exact Arduino board, motor driver, Bluetooth module, and sensor models.
- Add a wiring diagram and a demonstration video.

## Safety Precautions

- Raise the wheels off the ground during initial motor-direction testing.
- Keep hands and loose objects away from moving wheels.
- Check the motor driver's current limits and power requirements.
- Verify sensor polarity and motor direction before operating the robot on the floor.
- Test obstacle detection while stationary before testing at low speed.
- Do not rely on the obstacle sensors as the only means of preventing collisions.

## License

No license has been specified. Add a `LICENSE` file if you intend to permit others to reuse, modify, or distribute this project.

---

**Technologies:** Arduino, C/C++, Bluetooth Serial Communication, DC Motors, and Obstacle Detection.
