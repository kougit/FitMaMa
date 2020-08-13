#include <LiquidCrystal.h>

LiquidCrystal lcd(9,10,5,6,7,8);   
int signal=11;
int distance;
unsigned long pulseduration=0;
    void measureDistance()
{
 // set pin as output so we can send a pulse
 pinMode(signal, OUTPUT);
// set output to LOW
 digitalWrite(signal, LOW);
 delayMicroseconds(5);
 
 // now send the 5uS pulse out to activate Ping)))
 digitalWrite(signal, HIGH);
 delayMicroseconds(5);
 digitalWrite(signal, LOW);
 
 // now we need to change the digital pin
 // to input to read the incoming pulse
 pinMode(signal, INPUT);
 
 // finally, measure the length of the incoming pulse
 pulseduration=pulseIn(signal, HIGH);
}
     
    void setup()
    {
      
      lcd.begin(20,4);
      lcd.print("   FIT-MAMA");
      delay(2000);   
      pinMode(13,OUTPUT);
      Serial.begin(19200); // for GSM shield
      delay(100);  // give time to log on to network.
     
      Serial.print("AT+CMGF=1\r");  // set SMS mode to text
      delay(100);
      Serial.print("AT+CNMI=2,2,0,0,0\r"); 
      // blurt out contents of new SMS upon receipt to the GSM shield's Serial out
      delay(100);
      
    }
     
    void loop() { 

      // get the raw measurement data from Ping)))
 measureDistance(); 
 // divide the pulse length by half
 pulseduration=pulseduration/2;  
 // now convert to centimetres. We're metric here people...
 distance = int(pulseduration/29);
int pressure,pressure1;
if(distance>10)
{
  pressure=0;
  pressure1=1;
}
else
{
 pressure1=map(distance,0,10,70,90);
 pressure=map(pressure1,70,100,80,110);
 pressure=2+pressure*1.37483;
  
}
 
 
      int  sensorValue = analogRead(A0); 
      int  sensor1Value = analogRead(A1);
       int  sensor2Value = analogRead(A2);
      int hr=map(sensor1Value,40,1023,0,100); 
      float voltage=sensorValue*5;//converting the reading to voltage
      voltage/=1024;
      float temp_degC=(voltage-0.5)*100;

      if(temp_degC>38)
      {
        digitalWrite(13,HIGH);
        Serial.println("AT+CMGF=1"); // set the SMS mode to text 
      delay(2500); 
      Serial.write("AT+CMGS="); 
      Serial.write(34); //ASCII of “ 
      Serial.write("+256778145457"); 
      Serial.write(34); 
      Serial.write(13); 
      Serial.write(10); 
      delay(2500);
      Serial.print("Temp: ");
      Serial.print(temp_degC);
      Serial.print("deg");
      Serial.print("C  ");
      Serial.print("HR: ");
       Serial.print(sensor1Value);
       Serial.print("BPM ");
       Serial.print("Psys: ");
       Serial.print(pressure);
       Serial.print("mmHg ");  
       Serial.print("Pdia: ");
       Serial.print(pressure1);
       Serial.print("mmHg ");
       Serial.print("UC");
       Serial.println(sensor2Value);
       delay(2500); 
       Serial.write(26); 
       Serial.write(13); 
       Serial.write(10);//Ascii code of ctrl+z to send the message   
       delay(5000);
      
        lcd.clear();  
         lcd.print("TEMP: ");
         lcd.print(temp_degC);      // display the temperature
         lcd.print(0XB0);
         lcd.print("C ");
         delay(1000);
      }
      if(temp_degC<38)
      {
        if(temp_degC>35)
      {
        digitalWrite(13,LOW);
      }
      else
      {
       lcd.clear();  
         lcd.print("TEMP: ");
         lcd.print(temp_degC);      // display the temperature
         lcd.print(0XB0);
         lcd.print("C ");
         delay(1000);
         digitalWrite(13,HIGH);
        Serial.println("AT+CMGF=1"); // set the SMS mode to text 
      delay(2500); 
      Serial.write("AT+CMGS="); 
      Serial.write(34); //ASCII of “ 
      Serial.write("+256778145457"); 
      Serial.write(34); 
      Serial.write(13); 
      Serial.write(10); 
      delay(2500);
      Serial.print("Temp: ");
      Serial.print(temp_degC);
      Serial.print("deg");
      Serial.print("C  ");
      Serial.print("HR: ");
       Serial.print(sensor1Value);
       Serial.print("BPM ");
       Serial.print("Psys: ");
       Serial.print(pressure);
       Serial.print("mmHg ");  
       Serial.print("Pdia: ");
       Serial.print(pressure1);
       Serial.print("mmHg ");
       Serial.print("UC");
       Serial.println(sensor2Value);
       delay(2500); 
       Serial.write(26); 
       Serial.write(13); 
       Serial.write(10);//Ascii code of ctrl+z to send the message   
       delay(5000);
      
        
      }
      }
         
       lcd.clear();  
       lcd.print("TEMP: ");
       lcd.print(temp_degC);      // display the temperature
       lcd.print(0XB0);
       lcd.print("C ");
       delay(1000);
      
         
       
       lcd.print("HR: ");
       lcd.print(sensor1Value);
       lcd.print("BPM ");     lcd.print("uC: ");
       lcd.print(sensor2Value);
       lcd.print("Nm");

       lcd.setCursor(0,1);
       lcd.print("Psys: ");
       lcd.print(pressure);
       lcd.print("mmHg "); 
       lcd.setCursor(0,2);
       lcd.print("Pdia: ");
       lcd.print(pressure1);
       lcd.print("mmHg ");
       
     
       delay(5000);
      
    }
