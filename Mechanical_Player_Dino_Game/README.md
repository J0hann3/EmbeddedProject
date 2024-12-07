<h1 align=center>💻 Mechanical Player Dino Game</h1>

## About

The goal of the project is to create a robot that can play Dino game(on Chrome without Internet connection).

## Features
- **Description**: Use arduino board to play the Dino game on a PC using only registers manipulation.
- **Feature**: Detect the changes in light caused by the obstacles to press the space bar.
- **How to Use**: Recreate the circuit using the schema then push the code on the board

## Setup
- **Clone the Repository**:
	```bash
	git clone https://github.com/J0hann3/EmbeddedProject;
	cd EmbeddedProject/Mechanical_Player_Dino_Game
	```
- **Components needed to recreate the project**:
	- UNO R3 Controller Board(ATmega328)
	- Server Motor
	- Photoresistor(Photocell)
	- USB cable
	- 10k Resistor
	- Breadboard
	- Wires
	- Scotch

[Link to the kit Elegoo: The most complete starter kit](https://eu.elegoo.com/fr/products/elegoo-mega-2560-the-most-complete-starter-kit?utm_source=officialhome&utm_medium=referral&utm_id=eustorefr)


- Construct the circuit following the schema bellow:

![Circuit Schema](/Mechanical_Player_Dino_Game/img/schema_circuit.png)

- Place the photoresistor on the screen where the cactus pass, use scotch to attach it
- Place the servo motor on the space bar and fix it with scotch
- Configure on the script the pression  that will be applied on the space bar and the sensibility of the photoresitor

## Usage
- Run the command `make` to flush the code to the board
- Launch a dino game to see the board play on its own

## New Notion

### Photoresistor
The photoresistor is a resistance that decrease or increase depending on the light source.
If the luminosity increase the resistance will decrease.
I used it the now want a cactus arrived to make the dino jump.
With the analog pin of the board, we can take the information as an input, to then output the movement if needed in the servo motor. 

### Servo Motor
The servor motor take a signal as input to convert it in the desired motor position.
Thanks to duty cycle I created a signal that can vary depending on the input from the photoresistor.

## Demo
### Final Result

![Dino Game](/Mechanical_Player_Dino_Game/img/demo_dino.mp4)

### Construction and components
- **Photoresistor**, place on the screen.
![Photoresistor](/Mechanical_Player_Dino_Game/img/photoresistor.jpg)

- **Servo Motor**, position on the space bar.
![Servo Motor](/Mechanical_Player_Dino_Game/img/motor.jpg)

- **Board**, connected to the photoresistor and the servo motor.
![Board](/Mechanical_Player_Dino_Game/img/circuit.jpg)
