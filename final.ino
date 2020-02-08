#include <AFMotor.h>
#include <MotorDriver.h>
MotorDriver m;

/*-------------------------------------------------------------------------------------------------------------------- Initializing variables -------------------------------------*/
// Car wheels:
//  2  1
//  3  4
uint8_t trigPin1 = A0;
uint8_t echoPin1 = A1;
uint8_t trigPin2 = A2;
uint8_t echoPin2 = A3;
uint8_t trigPin3 = A4;
uint8_t echoPin3 = A5 ;
const int fwd_lim = 10;
const int left_lim = 5;
const int right_lim = 5;
const int a = 80;
const int b = 40;
const int c = 160;

/*--------------------------------------------------------------------------------------------------------------------  Motion Control ----------------------------------------*/
void fwd() {
  m.motor(1, FORWARD, a);
  m.motor(2, FORWARD, a);
  m.motor(3, FORWARD, a);
  m.motor(4, FORWARD, a);
  delay(50);
  //fwd delay should be as low as possible
}
void right() {
  //turn right
  m.motor(1, BACKWARD, a);
  m.motor(2, FORWARD, a);
  m.motor(3, FORWARD, a);
  m.motor(4, BACKWARD, a);
  delay(850);
}
void left() {
  m.motor(2, BACKWARD, a);
  m.motor(1, FORWARD, a);
  m.motor(4, FORWARD, a);
  m.motor(3, BACKWARD, a);
  delay(850);
}
void back() {
  //it is not back movement, it is turn around function.
  m.motor(1, BACKWARD, b);
  m.motor(2, FORWARD, a);
  m.motor(3, FORWARD, c);
  m.motor(4, BACKWARD, b);
  delay(1850);
}
void stopp() {
  m.motor(2, BACKWARD, 0);
  m.motor(1, FORWARD, 0);
  m.motor(4, FORWARD, 0);
  m.motor(3, BACKWARD, 0);
}

/*--------------------------------------------------------------------------------------------------------Sensor reading float functions-------------------------------*/
float firstsensor() {
  int duration1, distance1;
  digitalWrite (trigPin1, HIGH);
  delayMicroseconds (2);
  digitalWrite (trigPin1, LOW);
  duration1 = pulseIn (echoPin1, HIGH);
  distance1 = (duration1 / 2) / 29.1;
  Serial.print("FORWARD: ");
  Serial.print(distance1);
  Serial.print("cm    ");
  return distance1;
}
float secondsensor() {
  int duration2, distance2;
  digitalWrite (trigPin2, HIGH);
  delayMicroseconds (2);
  digitalWrite (trigPin2, LOW);
  duration2 = pulseIn (echoPin2, HIGH);
  distance2 = (duration2 / 2) / 29.1;
  Serial.print("LEFT: ");
  Serial.print(distance2);
  Serial.print("cm    ");
  return distance2;
}
float thirdsensor() {
  int duration3, distance3;
  digitalWrite (trigPin3, HIGH);
  delayMicroseconds (2);
  digitalWrite (trigPin3, LOW);
  duration3 = pulseIn (echoPin3, HIGH);
  distance3 = (duration3 / 2) / 29.1;
  Serial.print("RIGHT: ");
  Serial.print(distance3);
  Serial.print("cm");
  return distance3;
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------void setup ( )------------------------------------*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

/*--------------------------------------------------------------------------------------------------------------------------------------------------void loop ( )------------------------------------*/
void loop() {
  Serial.println(" ");
  float distancef, distancel, distancer;
  distancef = firstsensor();
  distancel = secondsensor();
  distancer = thirdsensor();
  delay(1);
  if ((distancef > fwd_lim) && (distancel < left_lim ) && (distancer < right_lim) ) {
    fwd();
  }
  else {
    stopp();
    if (distancef < fwd_lim && distancel > left_lim && distancer < right_lim) {
      //it should take left, since no other option
      left();
    }
    if (distancef < fwd_lim && distancel < left_lim && distancer > right_lim) {
      //it should take right, since no other option
      right();
    }
    if (distancef > fwd_lim && distancel < left_lim && distancer > right_lim) {
      //it goes straight, because the program is DEFAULT LEFT
      fwd();
    }
    if (distancef > fwd_lim && distancel > left_lim && distancer < right_lim) {
      //it goes left, because DEFAULT LEFT
      left();
    }
    else {
      fwd();
    }
    fwd();
  }
}
