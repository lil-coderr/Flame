#include <Servo.h> 

Servo HorServo ; // instantiate servo to control the horizontal moving servo
Servo VerServo; // instantiate servo to control the Vertical moving servo

// Defining variables
int HorAngle; //note: value must be between 0 and 180
int VerAngle; // note: value must be between 0 and 90
int F_Sensor_pin = A0; // definge the analog pin
 bool pump = 0;

void setup() 
{ 
  pinMode(7, OUTPUT) ; //PINT 7 IS OUTPUT FOR RELAY
 digitalWrite(7,HIGH);
  //Flame sensor part
  pinMode(F_Sensor_pin, INPUT);
  Serial.begin(9600); 

  //servos part 
  HorServo.attach(9); //Attach the Servo variable to a pin 9
  VerServo.attach(10); //Attach the Servo variable to a pin 9
  
  HorServo.write(0);  // set servo to intial point
  delay(50);
  VerServo.write(0);  // set servo to intial point
  delay(400);

 
  
} 

void loop() 
{  
  while (1)
  {      //Defining variables
       float flameReading;
       float lowestflameHor = 1024;
       float lowestflameVer = 1024;
      
       int lowestHorAngle;
       int lowestVerAngle;
       
       //the horizontal servo searchs for any flames
       for (HorAngle = 0; HorAngle <= 180; HorAngle += 1) 
         { HorServo.write(HorAngle);
          delay(10);
          if (analogRead(F_Sensor_pin) < lowestflameHor)
             {
              lowestflameHor = analogRead(F_Sensor_pin) ;
              lowestHorAngle = HorAngle;
              Serial.println(lowestHorAngle); 
              Serial.println(lowestflameHor);
             }
         }
       delay(100);
       for (HorAngle = 0; HorAngle <= lowestHorAngle; HorAngle += 2)
          {HorServo.write(HorAngle);  delay(20);}
         
       //the Vertical servo searchs for any flames
       for (VerAngle = 0; VerAngle <= 90; VerAngle += 1) 
         { VerServo.write(VerAngle);
          delay(10);
          if (analogRead(F_Sensor_pin) < lowestflameVer)
             {
              lowestflameVer = analogRead(F_Sensor_pin) ;
              lowestVerAngle = VerAngle;
              Serial.println(lowestVerAngle); 
              Serial.println(lowestflameVer);
             }
         }
       delay(100);
       
       for (VerAngle = 0; VerAngle <= lowestVerAngle+12; VerAngle += 2)
         {
          VerServo.write(VerAngle);   delay(20); 
         }
         delay(1000);
       if (analogRead(F_Sensor_pin) < 800){pump = 1 ;}
      if (pump == 1) 
          { digitalWrite(7,LOW);
            delay(2000); 
            digitalWrite(7,HIGH);
            delay(500);
            pump =0; 
          } else{break ;}
          
      
 } 
  delay(1000);
  HorServo.write(0);  // set servo to intial point
  delay(100);
  VerServo.write(0);  // set servo to intial point
  delay(5000);      
}
