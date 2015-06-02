// RECIEVER CODE

//NOTE :- THIS CODE IS USED WHEN CONTROLLING THE ROBOT VIA THE BREADBORD REMOTE

#include <VirtualWire.h>

//declaring pin nos to FIRST L293D
/*int en1 = 5;
 int en2 = 6;
 int in1 = 7;
 int in2 = 8;
 int in3 = 9;
 int in4 = 10;
 //declaring pin nos to SECOND L293D
 int en1o2 = 3;
 int en2o2 = 11;
 int in1o2 = 4;
 int in2o2 = 12;
 int in3o2 = 14;
 int in4o2 = 15;
 int motorPin[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15};//array for storing pin nos
*/

#include <Wire.h>// Intializing the libraries.
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();// This is the motor shield being intialized.
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); // This intialize the motor.
int treatvalue (int data) // This is convert the joystick data to be able to use for the motors.
{
  if(data > 512 && data < 1024)
  {
    return ((data/2)-256);
  }
  else if(data == 1024)
  {
    return(data = 255);
  }
  else if(data < 512 && data > 0)
  {
   return(abs((data/2)-256));
  }
  else if (data == 0)
  {
   return(data - 255); 
  }
  else
  {
    return (data = 0); 
  }
}
int joyValue = 0;
int motorSpeed = 0;
void setup()
{
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");
    myMotor->setSpeed(255);
    myMotor->run(FORWARD);
    myMotor->run(RELEASE);    
    // Initialise the IO and ISR
    vw_setup(2000);	 // Bits per sec
    vw_set_rx_pin(2);    //Rx Data pin to Digital  Pin 2
    vw_rx_start();       // Start the receiver PLL running
   /* for (int i = 0; i < 12; i++) 
   {
          pinMode(motorPin[i], OUTPUT);
   }
   /*
/*
This is basically what the above for loop does :-
pinMode(en1, OUTPUT);
pinMode(en2, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(en1o2, OUTPUT);
pinMode(en2o2, OUTPUT);
pinMode(in1o2, OUTPUT);
pinMode(in2o2, OUTPUT);
pinMode(in3o2, OUTPUT);
pinMode(in4o2, OUTPUT);
*/
}//close setup

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
	int i;
        digitalWrite(13, true); // Flash a light to show received good message
	// Message with a good checksum received, dump it.
	for (i = 0; i < buflen; i++)
	{
        joyValue = buf[i] - '0';
        Serial.println(joyValue);
        motorSpeed = treatvalue(joyValue);
	 Serial.print(buf[i]);//print received command
        if(joyValue > 512)//if button 1 is pressed.... i.e.forward buton
      {
        forward(motorSpeed);//go forward
        Serial.println(" = forward");
      }
    if(joyValue < 512)//if button 2 is pressed.... i.e.back buton
      {
        backward(motorSpeed);//go backward
        Serial.println(" = backward");
      }
      /*
        if(buf[i] == '3')//if button 3 is pressed.... i.e.left buton
      {
        left();//go left
        Serial.println(" = left");
      }
        if(buf[i] == '4')//if button 4 is pressed.... i.e.right buton
      {
        right();//go right
        Serial.println(" = right");
      }
      */
        if(joyValue == 512)//if button 5 is pressed.... i.e.stop buton
       {
         stopMotor(motorSpeed);//stop/brake
         Serial.println(" = stopped");
       }
	    Serial.print(" ");
	}
	Serial.println("");
        digitalWrite(13, false);

   }//close if
}//close loop


////////////////////////////////////////////////////////////////////////////////////////
//set of functions

int forward(int motorSpeed)
{
  myMotor->setSpeed(motorSpeed);
  myMotor->run(FORWARD);
  }
  
  
int backward(int motorSpeed)
{
  myMotor->setSpeed(255);
  myMotor->run(BACKWARD);
  
}
/*
int left(int motorSpeed)
{
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
  digitalWrite(en1o2,HIGH);
  digitalWrite(en2o2,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in1o2,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in2o2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in3o2,LOW);
  digitalWrite(in4,HIGH);
  digitalWrite(in4o2,HIGH);
  
}

int right(int motorSpeed)
{
  digitalWrite(en1,HIGH);
  digitalWrite(en2,HIGH);
  digitalWrite(en1o2,HIGH);
  digitalWrite(en2o2,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in1o2,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in2o2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in3o2,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(in4o2,LOW);
  
}
*/
int stopMotor(int motorSpeed)
{
  myMotor->setSpeed(motorSpeed);
  myMotor->run(RELEASE);
}
  
 //End Of Code
