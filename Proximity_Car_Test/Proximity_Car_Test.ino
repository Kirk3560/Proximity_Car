#define maxPWM 255
#define moderatePWM 200
#define turnPWM 220
#define stopPWM 0


const int redPin = 13;
const int bluePin = 12;
const int greenPin = 11;

const int trigPinS = 4;
const int trigPinL = 1;
const int trigPinR = 0;
const int echoPinS = 3;
const int echoPinL = 8;
const int echoPinR = 2;

const int piezoPin = 7;

const int rightMotor1 = 5;
const int rightMotor2 = 6;
const int leftMotor1 = 9;
const int leftMotor2 = 10;


//speed Of Sound in centimetres per microsecond
const float speedOfSound = 0.0343;

const int turnDis = 15;
const int fastDis = 40; 


float time;
float distance;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  pinMode(trigPinS, OUTPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinS, INPUT);
  pinMode(echoPinL, INPUT);
  pinMode(echoPinR, INPUT);

  pinMode(piezoPin, OUTPUT);

  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);

}

void loop()
{
  noTone(piezoPin);
 /*Serial.print(senseDistance('l'));
  Serial.print("   ");
  Serial.print(senseDistance('s'));
  Serial.print("   ");
  Serial.println(senseDistance('r'));
  */
  //if the straight ultrasonic sensor is more than 25 cm, the car will drive straight at max speed and a RGB Led will turn green
  if (senseDistance('s') > fastDis) {
    setRGB(0, 255, 0);
    drive('s', maxPWM, maxPWM);
  }
  //if the straight ultrasonic sensor is between 10cm and 25cm , the car will drive straight at a moderate speed and a RGB Led will turn yellow
  else if (senseDistance('s') >= turnDis && senseDistance('s') <= fastDis) {
    setRGB(255, 255, 0);
    drive('s', moderatePWM, moderatePWM);
  }
  //if the straight ultrasonic sensor is less than 10cm, the car will turn, a peizo will start to ring and and a RGB Led will turn red
  else if (senseDistance('s') < turnDis && senseDistance('r') > senseDistance('l')) {
    tone(piezoPin, 1000);
    //if the right distance sensor is further from a wall than the left one, the robot will turn to the right
    setRGB(255, 0, 0);
    drive('r', turnPWM, turnPWM);
  }
  else if (senseDistance('s') < turnDis && senseDistance('r') <= senseDistance('l')) {
    tone(piezoPin, 1000);
    //if the right distance sensor is further from a wall than the left one, the robot will turn to the right
    setRGB(255, 0, 0);
    drive('l', turnPWM, turnPWM);
  }
  delay(10);
}

/*
  Serial.print(senseDistance('l'));
  Serial.print(" ");
  Serial.print(senseDistance('s'));
  Serial.print(" ");
  Serial.println(senseDistance('r'));
*/



double senseDistance(char dir) {
  //argument decides which distance sensor to return the value for
  int echoPin;
  int trigPin;
  if (dir == 'l') {
    echoPin = echoPinL;
    trigPin = trigPinL;
  }
  else if (dir == 'r') {
    echoPin = echoPinR;
    trigPin = trigPinR;
  }
  else {
    echoPin = echoPinS;
    trigPin = trigPinS;
  }

  //Turns on the trigger pin for 10 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  //the time the sound took to travel from the sensor to the wall and back to the sensor
  time = pulseIn(echoPin, HIGH);

  //Divide by 2 to find the distance from sensor to object and multiply it by the speed of sound to find the distance from the sensor to the object
  distance = time * speedOfSound / 2;

  /*
    Serial.print("Distance: ");
    Serial.println(distance);

  */
  return distance;
}
void drive(char d, int LPWM , int RPWM) {
  //depending on the direction of the char variable the motors will turn to face that direction
   // LPWM = LPWM - 2.1;
    if (d == 's') {
    analogWrite(rightMotor1, RPWM);
    analogWrite(rightMotor2, 0);
    analogWrite(leftMotor1, LPWM);
    analogWrite(leftMotor2, 0);
    }
    else if (d == 'b') {
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, RPWM);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, LPWM);
    }
    else if (d == 'r') {
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, RPWM);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
    //delay(500);
    }
    else if (d == 'l') {
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, LPWM);
    //delay(500);
    }
    else {
    }
  
}

// a method to quickly set the colours of an rgb led
void setRGB(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
