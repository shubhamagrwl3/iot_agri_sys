#include <LiquidCrystal.h>

#include <SoftwareSerial.h>

#include<dht.h>
#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
SoftwareSerial mySerial(9,10);//RX,TX
dht DHT ;
#define DHT11_PIN 7
#define echopin 5 //echo pin
#define trigpin 4//Trigger pin
const int MOISTURE = A0;
const int THRESHHOLD = 750;
int maximumRange = 55;
int motorPin = 3;                                                                                
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup()
{
 pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(1,1);
  while (! Serial);
  Serial.println("Speed 0 to 255");
pinMode(13,OUTPUT);
pinMode(7,OUTPUT);
pinMode(echopin,INPUT);
}
void LedState(int state)
{
digitalWrite(13,state);
}
void loop()
{
digitalWrite(trigpin,LOW);
delayMicroseconds(2);
digitalWrite(trigpin,HIGH);
delay(20);
int chk=DHT.read11(DHT11_PIN);
Serial.println("Humidity");
Serial.println(DHT.humidity);
lcd.println(DHT.humidity);
Serial.println("Temperature");
Serial.println(DHT.temperature);
lcd.println(DHT.temperature);
int moisture = analogRead(MOISTURE);
Serial.print("Moisture = ");
Serial.println(moisture);
if(moisture>THRESHHOLD)
{
  digitalWrite(7,HIGH);
  SendMessage1();

}
else
{
  digitalWrite(7,LOW);
   if (Serial.available())
  {
    int speed = Serial.parseInt();
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(motorPin, speed);
    }
  }
}
delay(2000);
}

void SendMessage1()
{
  mySerial.println("AT+CMGF=1");  
  mySerial.println("AT+CMGF=1"); //Set the GSM Module in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+919636874188\"\r"); //Replace x with mobile number
  delay(1000);
  mySerial.println("Moisture is high");//the SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
}  
/*int motorPin = 3;
void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
} 
 
 
void loop() 
{ 
  if (Serial.available())
  {
    int speed = Serial.parseInt();
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(motorPin, speed);
    }
  }
} */
