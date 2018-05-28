#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial kakuile(2,3);

int servoPin = 6;
byte sensorPin = 10;
byte indicator = 13;
int speaker = 12;
int val, i;
char trig= '0';
Servo servo;

void setup()
{
  pinMode(sensorPin, INPUT);
  pinMode(indicator, OUTPUT);
  pinMode(speaker, OUTPUT);
  servo.attach(servoPin);
  kakuile.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  // Insect detection
  byte state = digitalRead(sensorPin);
  digitalWrite(indicator, state);

  if(kakuile.available()>0)
  {
    trig= kakuile.read();
  }
  if(Serial.available()>0)
  {
    trig= Serial.read();
  }

  if (trig=='0')
  {
    noTone(speaker);
    if (state == 1 && val <= 900)
    {
      Serial.println("Movement in the area");
      servo.write(0);     
      delay(500);          
      servo.write(180);      
      delay(500);
      val = analogRead(0);   //connect mic sensor to Analog 0
      delay(5);
      for(i=0;i<10;i++)
      {
        val += analogRead(0);
        delay(5);
      }
      Serial.println(val,DEC); //print the sound value to serial               
     }
     
    else if (state == 0 || val == 0 || val >900)
    {
      Serial.println("Nothing");
      val = analogRead(0);
      delay(5);
      val += analogRead(0);
      for(i=0;i<10;i++)
      {
        val += analogRead(0);
        delay(5);
      }
      Serial.println(val,DEC);
    }
  }
  
 else if (trig=='1')
  {
    Serial.println("Trigger by button");
    tone (speaker, 1000);
    servo.write(0);     
    delay(500);          
    servo.write(180);      
    delay(500);
  }

}
