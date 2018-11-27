#define maxPWM 255
#define moderatePWM 200
#define turnPWM 225
#define stopPWM 0


const int redPin = 2;
const int bluePin = 1;
const int greenPin = 0;

const int trigPinS = 9;
const int trigPinL = 13;
const int trigPinR = 4;
const int echoPinS = 8;
const int echoPinL = 12;
const int echoPinR = 3;

const int piezoPin = 7;

const int rightMotor1 = 5;
const int rightMotor2 = 6;
const int leftMotor1 = 10;
const int leftMotor2 = 11;


//speed Of Sound in centimetres per microsecond
const float speedOfSound = 0.0343;

const int fastTurnDis = 5;
const int turnDis = 15;
const int fastDis = 40;

const int fastTurnDel = 500;
const int turnDel = 1000;


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

  //Serial.begin(9600);

}

void loop()
{
  noTone(piezoPin);
  /*
    Serial.print(senseDistance('l'));
    Serial.print("   ");
    Serial.print(senseDistance('s'));
    Serial.print("   ");
    Serial.println(senseDistance('r'));
  */
  //if the straight ultrasonic sensor is more than 25 cm, the car will drive straight at max speed and a RGB Led will turn green
  if (senseDistance('s') > fastDis) {
    setRGB(0, 255, 0);
    drive('s', maxPWM, maxPWM, 0);
  }
  //if the straight ultrasonic sensor is between 10cm and 25cm , the car will drive straight at a moderate speed and a RGB Led will turn yellow
  else if (senseDistance('s') >= turnDis && senseDistance('s') <= fastDis) {
    setRGB(255, 255, 0);
    drive('s', moderatePWM, moderatePWM, 0);
  }
  //if the straight ultrasonic sensor is less than 10cm, the car will turn, a peizo will start to ring and and a RGB Led will turn red

  else if (senseDistance('s') <= fastTurnDis) {
    //tone(piezoPin, 1000);
    setRGB(255, 0, 0);
    if (senseDistance('r') > senseDistance('l')) {
      //Serial.println("right");
      //if the right distance sensor is further from a wall than the left one, the robot will turn to the right
      drive('r', turnPWM, turnPWM, fastTurnDel);
    }
    else {
      //if the right distance sensor is further from a wall than the left one, the robot will turn to the right
      drive('l', turnPWM, turnPWM, fastTurnDel);
      //Serial.println("left");
    }
  }

  else if (senseDistance('s') < turnDis) {
    //tone(piezoPin, 1000);
    setRGB(255, 100, 0);
    if (senseDistance('r') > senseDistance('l')) {
      //Serial.println("right");
      //if the right distance sensor is further from a wall than the left one, the robot will turn to the right
      drive('r', turnPWM, turnPWM, turnDel);
    }
    else {
      //if the right distance sensor is further from a wall than the left one, the robot will turn to the right
      drive('l', turnPWM, turnPWM, turnDel);
      //Serial.println("left");
    }
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
void drive(char d, int LPWM , int RPWM, double del) {
  //depending on the direction of the char variable the motors will turn to face that direction
  double compensation = 55;
  switch (d) {
    case 's':
      LPWM = LPWM - compensation;
      analogWrite(rightMotor1, RPWM);
      analogWrite(rightMotor2, 0);
      analogWrite(leftMotor1, LPWM);
      analogWrite(leftMotor2, 0);
      break;

    case 'b':
      LPWM = LPWM - compensation;
      analogWrite(rightMotor1, 0);
      analogWrite(rightMotor2, RPWM);
      analogWrite(leftMotor1, 0);
      analogWrite(leftMotor2, LPWM);
      break;

    case 'r':
      analogWrite(rightMotor1, 0);
      analogWrite(rightMotor2, RPWM);
      analogWrite(leftMotor1, 0);
      analogWrite(leftMotor2, 0);
      delay(del);
      break;

    case 'l':
      analogWrite(rightMotor1, 0);
      analogWrite(rightMotor2, 0);
      analogWrite(leftMotor1, 0);
      analogWrite(leftMotor2, LPWM);
      delay(del);
      break;

    default:
      analogWrite(rightMotor1, 0);
      analogWrite(rightMotor2, 0);
      analogWrite(leftMotor1, 0);
      analogWrite(leftMotor2, 0);
      delay(del);
      break;
  }
}

// a method to quickly set the colours of an rgb led
void setRGB(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
