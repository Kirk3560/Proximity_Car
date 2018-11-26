#define maxPWM 255
#define moderatePWM 150
#define turnPWM 130
#define stopPWM 0


const int redPin = 13;
const int bluePin = 12;
const int greenPin = 11;

const int trigPin = 4;
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

float time;
float distance;
bool reverse;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPinS, INPUT);
  pinMode(echoPinL, INPUT);
  pinMode(echoPinR, INPUT);

  pinMode(piezoPin, OUTPUT);

  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);


  Serial.begin(9600);

}

void loop()
{
  noTone(piezoPin);
  //if the straight ultrasonic sensor is more than 25 cm, the car will drive straight at max speed and a RGB Led will turn green
  if (senseDistance('s') > 25) {
    drive('s', maxPWM, maxPWM);
    setRGB(0, 255, 0);
  }
  //if the straight ultrasonic sensor is between 10cm and 25cm , the car will drive straight at a moderate speed and a RGB Led will turn yellow
  else if (senseDistance('s') >= 10 && senseDistance('s') <= 25) {
    drive('s', moderatePWM, moderatePWM);
    setRGB(255, 255, 0);
  }
  //if the straight ultrasonic sensor is less than 10cm, the car will turn, a peizo will start to ring and and a RGB Led will turn red
  else if (senseDistance('s') < 10) {
    tone(piezoPin, 1000);
    //if the right distance sensor is further from a wall than the left one, the robot will turn to the right
    if (senseDistance('r') > senseDistance('l')) {
      drive('r', turnPWM, turnPWM);
    }
    //if the right distance sensor is closer from a wall than the left one, the robot will turn to the left
    else if (senseDistance('r') < senseDistance('l')) {
      drive('l', turnPWM, turnPWM);
    }
    setRGB(255, 0, 0);
  }
  delay(10);
  /*
    Serial.print(senseDistance('l'));
    Serial.print(" ");
    Serial.print(senseDistance('s'));
    Serial.print(" ");
    Serial.println(senseDistance('r'));
  */
}

double senseDistance(char dir) {
 //argument decides which distance sensor to return the value for
  int echoPin; 
  if (dir == 'l') {
    echoPin = echoPinL;
  }
  else if (dir == 'r') {
    echoPin = echoPinR;
  }
  else {
    echoPin = echoPinS;
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
  LPWM = LPWM - 20;
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
  }
  else if (d == 'l') {
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, LPWM);
  }
  else {
    analogWrite(rightMotor1, 0);
    analogWrite(rightMotor2, 0);
    analogWrite(leftMotor1, 0);
    analogWrite(leftMotor2, 0);
  }
}

// a method to quickly set the colours of an rgb led
void setRGB(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
