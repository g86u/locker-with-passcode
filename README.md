# Locker with passcode
## Prelude
The [Arduino course that you can find on Skillshare](https://skl.sh/3BiAi2E) inspires the project I made.

## Requiered components
- Arduino Uno
- Breadboard (optional)
- Keypad
- LCD display
- Servo motor
- Passive buzzer
- 2x LEDs (green and red, if possible)
- Multiple male-to male or female-to-male wires (depending on the preference for teh breadboard)
- 2x resistors
- one variable resistor

## IDE
I initially used Arduino, and after I started to work on Visual Code Studio using the extension named [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).

## Description
Using the keypad, you can introduce a four characters password that will appear on the LCD. If the password is correct, the servo motor will spin, the green LED will light up, the buzzer will make a sound, and the "locker" will remain open for 10 seconds. If the password is incorrect, the red LED will light up, and the buzzer will make another sound. If the password is incorrectly introduced thrice in a row, the red LED will light up, the buzzer will produce a deeper sound, and the "locker" will block for 30 seconds.
