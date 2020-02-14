# MicroMouseBot

The code written in Arduino IDE for the MicroMouse bot on Arduino Uno with installed motor drivers. The components used are three ultrasonic sensors to detect obstacles (walls) in the front, left and right directions and four motors for the four wheels.

The algorithm is based on Default Left rule : It prefers to take left whenever there is a left turn possible , or goes straight  there's no way left and takes right only if there's no other possibility.
