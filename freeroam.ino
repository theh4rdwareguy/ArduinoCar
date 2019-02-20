// ************************************************************************************* //
// v1.0 (February 2016)                                                                  //
// Developed by 'thehardwareguy'.                                                        //
// YouTube Channel: https://www.youtube.com/channel/UCYoC_z7nsi842rI9hM3LZSg             //
// Website: http://www.thehardwareguy.co.uk                                              //
// Instagram: https://www.instagram.com/hardwareguy_                                     //
// GitHub: https://github.com/theh4rdwareguy                                             //
// ************************************************************************************* //

#define leftechoPin 4 //pin for sensor echo
#define lefttrigPin 3 //pin for sensor trigger

#define rightechoPin 2 //pin for sensor echo
#define righttrigPin 9 //pin for sensor trigger

#define frontechoPin 1 //pin for sensor echo
#define fronttrigPin 9 //pin for sensor trigger

//Right Motors
int enA1 = 10;
int enA2 = 6;
int in1 = 7;
int in2 = 8;

//Left Motors
int enB1 = 5; 
int enB2 = 11;
int in3 = 12;
int in4 = 13;

int rightdistance;
int rightduration;

int leftdistance;
int leftduration;

int frontdistance;
int frontduration;



int del=0;

void setup() {
  pinMode(lefttrigPin, OUTPUT);
  pinMode(leftechoPin, INPUT);
  pinMode(righttrigPin, OUTPUT);
  pinMode(rightechoPin, INPUT);
  pinMode(fronttrigPin, OUTPUT);
  pinMode(frontechoPin, INPUT);
  pinMode(enA1, OUTPUT);
  pinMode(enB1, OUTPUT);
  pinMode(enA2, OUTPUT);
  pinMode(enB2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void initRightMotor()
{
  // set speed to 125 out of possible range 0~255
  analogWrite(enA1, 70);
  analogWrite(enA2, 70);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void initLeftMotor()
{
  // set speed to 125 out of possible range 0~255
  analogWrite(enB1, 70);
  analogWrite(enB2, 70);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRIGHT()
{
  // set speed to 125 out of possible range 0~255 
  analogWrite(enA1, 70);
  analogWrite(enA2, 70);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  analogWrite(enB1, 70);
  analogWrite(enB2, 70);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLEFT()
{
  // set speed to 125 out of possible range 0~255 
  analogWrite(enA1, 70);
  analogWrite(enA2, 70);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enB1, 70);
  analogWrite(enB2, 70);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void STOP()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  digitalWrite(fronttrigPin, LOW);
}

void REVERSE()
{
    // set speed to 125 out of possible range 0~255 
    analogWrite(enA1, 70);
    analogWrite(enA2, 70);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  
    analogWrite(enB1, 70);
    analogWrite(enB2, 70);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void frontCalculation()
{
    digitalWrite(fronttrigPin, HIGH);
    delay(10);
    digitalWrite(fronttrigPin, LOW);

    frontduration=pulseIn(frontechoPin,HIGH);
    frontdistance=(frontduration/2)/29.1;
}

void leftCalculation()
{
    digitalWrite(lefttrigPin, HIGH);
    delay(10);
    digitalWrite(lefttrigPin, LOW);

    leftduration=pulseIn(leftechoPin,HIGH);
    leftdistance=(leftduration/2)/29.1;
}

void rightCalculation()
{
    digitalWrite(righttrigPin, HIGH);
    delay(10);
    digitalWrite(righttrigPin, LOW);

    rightduration=pulseIn(rightechoPin,HIGH);
    rightdistance=(rightduration/2)/29.1;
}

void freeroam()
{
     if(leftdistance < 15 && rightdistance < 15 && frontdistance < 15) //IF ONLY CENTER DETECTED
     {
        REVERSE();
     }

     else  
     if(leftdistance > 25 && rightdistance > 25 && frontdistance < 25) //IF ONLY CENTER DETECTED
    {
      STOP();
        if (rightdistance < 25 && leftdistance > 25) 
          {
            turnLEFT();
          }

        if(leftdistance < 25 && rightdistance > 25)
          {
            turnRIGHT();
          }
        else
        {
          REVERSE();
        }
    }

        if(leftdistance < 25 && rightdistance < 25) //IF LEFT AND RIGHT DETECTED
          {
            STOP();
            turnRIGHT(); 
          }

        if (frontdistance < 25 && rightdistance < 25) //IF FRONT AND RIGHT DETECTED
          {
            STOP();
            turnLEFT();
          }

        if (frontdistance < 25 && leftdistance < 25) //IF FRONT AND LEFT DETECTED
          {
            STOP();
            turnRIGHT();
          }
    

        if(leftdistance >= 25 && rightdistance >= 25 && frontdistance >= 25) /// e.g. if it is safe to go forward
          {
            initRightMotor();
            initLeftMotor();
          }
          
        if(leftdistance < 25 && rightdistance > 25)  //IF ONLY RIGHT DETECTED
          {
            STOP();
            turnRIGHT();
          }
        if (rightdistance < 25 &&leftdistance > 25)  //IF ONLY LEFT DETECTED
          {
            STOP();
            turnLEFT();
          }     
        if(rightdistance < 25)
          {
            STOP();
            turnLEFT();   
          }
          
        if(leftdistance < 25)
          {
            STOP();
            turnRIGHT();   
          }
}

void loop() 
  {  
    frontCalculation();
    leftCalculation();
    rightCalculation();

    freeroam();
  }




