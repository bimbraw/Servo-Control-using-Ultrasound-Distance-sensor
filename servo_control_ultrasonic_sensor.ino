#include <LiquidCrystal.h>  //Load Liquid Crystal Library
#include <Servo.h>          //Load Servo Motor Library

//Create Liquid Crystal Object called LCD
LiquidCrystal LCD(10, 9, 5, 4, 3, 2);
//Create Servo object called servoMain
Servo servoMain;	    

//defining different variables
int trig = 13;		    //TRIG connected to pin no. 13
int echo = 11;		    //ECHO connected to pin no. 11
int angle_of_servo;	    //angle_of_servo for servo motor angle
float pingtime;	            //time for wave to travel from trig to echo   
float distance;		    //distance of object from sensor

void setup() 
{
  servoMain.attach(7);	    //Servo's control pin attached to pin no. 7
  pinMode(trig,OUTPUT);	    //Set trig pin as output pin
  pinMode(echo,INPUT);	    //Set echo pin as input pin
}

void loop() 
{
  digitalWrite(trig, LOW);  //set trig pin to LOW
  delayMicroseconds(2000);  //wait for 2 seconds		
  digitalWrite(trig, HIGH); //set trig pin high for 10us
  delayMicroseconds(10);    //wait for 0.001 seconds
  digitalWrite(trig, LOW);  //set trig pin to LOW again	
  
  pingtime = pulseIn(echo, HIGH); //pulseIn gives the time for which echo is high
  pingtime = pingtime / 1000000;  //convert pingtime to seconds
  distance = (pingtime * 340 * 100) / 2;  //speed of sound = 340 m/s
   
  angle_of_servo = distance;  //equate distance to angle_of_servo
  //to make the servo move corresponding to the distance
  
  LCD.begin(16, 2); 	    //Arduino starts 16 column 2 row LCD
  LCD.setCursor(0, 0);      //Set LCD cursor column 0, row 0
  LCD.print("Target Distance:");  //Print Message (First Row)
  
  //conditional statement for a room of sides not exceeding 1.8m
  //180 has been given because we want the servoto move 
  //from 0 to 180 degrees corresponding to distance in cm
  if(distance < 180)
  {
    LCD.setCursor(0, 1);	//Set cursor to first column of second row
    LCD.print("          "); 	//Print blanks to clear the row
    LCD.setCursor(0,1);   	//Set Cursor again to first column of second row
    LCD.print(distance / 100); 	//Print measured distance
    LCD.print(" m"); 		//Print your units.
    delay(250);	                //pause for 0.5 seconds to let things settle
  }
  
  else
  {
    LCD.clear();                //clear the LCD
    LCD.setCursor(0,0);         //set cursor to 0,0
    LCD.print("Out of range");  //print out of range
  }
 
  servoMain.write(angle_of_servo);  //function to turn servo to required angle
}
