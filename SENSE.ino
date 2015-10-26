/*
 * Sense : Smart 
 * Author : Geeve George
 * Instrubtables : http://www.instructables.com/member/Geeve+George/
 */

#define ALCOHOL_DAT A0
#define HEATER_SEL  A1

#include<Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int colorR = 10;
int colorG = 10;
int colorB = 10;
int BuzzerPin = 7;


void setup()
{

   
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    

  Serial.begin(9600);  // open the serial port at 9600 bps
  pinsInit();
  switchOnHeater();
  Serial.println("Start to heat the sensor, please wait 5~10min befor exposure to alcohol");
  pinMode(BuzzerPin,OUTPUT);

}
void loop()
{


    
  int sensorValue;
  sensorValue = analogRead(ALCOHOL_DAT); //read the analog value
  int value = 1023 - sensorValue;
  //Disply the results in serial monitor.

 float percent = value / 1024.0 * 100;  
  // round to two decimals
  percent = floor(percent*100) / 100;

    
    float recal = fabs(percent-10);
    

    if(recal>42)
    {
      
      colorR = 255;
      colorG = 0;
      colorB = 0;
        lcd.setRGB(colorR,colorG,colorB);
        delay(30);
     
      lcd.clear();
      lcd.print("Vapor Detected");
      lcd.setCursor(0,1);
      lcd.print(recal);
      lcd.print("%");
      digitalWrite(BuzzerPin,HIGH);
      delay(100);
      digitalWrite(BuzzerPin,LOW);
     
    }

    
    else
    {
      digitalWrite(BuzzerPin,LOW);
      colorR = 5;
      colorG = 5;
      colorB = 5;
      lcd.setRGB(colorR,colorG,colorB);
    lcd.clear();
    lcd.print("      SENSE");
    lcd.setCursor(0, 1);
    lcd.print(recal);
    
    
    
    }
    
    
 
       
/*  Serial.print("sensor test value = ");
  //sensorValue goes down when alcohol is detected. Hence subtracting from 1023.
  Serial.println(value);
  //The information below is recommended result of the judgment
        lcd.setCursor(0, 1);
 
  if(value < 300) {
    Serial.println("No alcohol vapor detected"); 
                
                lcd.println("No Vapor"); 
                
              }

  else if((value > 300) && (value < 750))
{

      Serial.println("High Concentration of Alcohol detected");
               
                lcd.print("High ");
  
}
  else if(value > 750){
    Serial.println("Very high Concentration of Alcohol detected");

              
                lcd.print("Very");
} */

  delay(100);
}

void pinsInit()
{
  pinMode(HEATER_SEL,OUTPUT);// set the HEATER_SEL as digital output.
  switchOffHeater(); //when HEATER_SEL is set, heater is switched off.
  pinMode(ALCOHOL_DAT,INPUT);
}
/*switch on the heater of Alcohol sensor*/
void switchOnHeater()
{
  digitalWrite(HEATER_SEL,LOW);
}
/*switch off the heater of Alcohol sensor*/
void switchOffHeater()
{
  digitalWrite(HEATER_SEL,HIGH);
}
