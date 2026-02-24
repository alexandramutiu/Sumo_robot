# Sumo_robot
Autonomous Arduino sumo robot using VL53L0X distance sensing and dual line detection to avoid the ring edge and aggressively attack opponents.

  🤖 Sumo Robot with VL53L0X

Autonomous sumo robot using:

- VL53L0X ToF distance sensor
- Dual line sensors
- L298N motor driver
- Arduino-compatible board

The robot avoids the ring edge and attacks opponents when detected.



  🚀 Features

- Edge detection (front and rear)
- Opponent detection with VL53L0X
- Autonomous attack behavior
- Safe motor control
- Hardware switch ON/OFF



  🧩 Hardware Required

- Arduino UNO
- VL53L0X distance sensor
- 2x line sensors
- L298N motor driver
- 2x DC motors
- Chassis + wheels
- Toggle switch
- Battery



 🔌 Pin Configuration

 Line Sensors
| Sensor | Pin |
|--------|-----|
| Front  | A0  |
| Back   | A1  |

  Motor Driver
| Function | Pin |
|----------|-----|
| L Forward | 9 |
| L Backward | 8 |
| ENA (PWM) | 5 |
| R Forward | 11 |
| R Backward | 12 |
| ENB (PWM) | 10 |

     Other
| Device | Pin |
|--------|-----|
| Switch | 7 |



  ⚙️ How It Works

1. Robot checks edge sensors first (highest priority)
2. If safe, checks for opponent distance
3. If opponent detected → attack
4. Otherwise → spin and search



  🛠️ Setup

1. Install **Adafruit VL53L0X** library
2. Upload the code
3. Place robot inside sumo ring
4. Flip the switch
5. Enjoy controlled chaos

