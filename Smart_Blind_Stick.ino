#include "Talkie.h"
#include "Vocab_US_Large.h"
#include <SoftwareSerial.h>
Talkie voice;
SoftwareSerial gsmSerial(6,7);
const int trigPin = 4;
const int echoPin = 5;
const int motorPin = 8;
//const int buzzer = 2;
const int ledPin = 13;
const int analogInPin = A0;
int sensorValue = 0;
int buttonpin=12;
long duration;
int distance;
int safetyDistance;
void setup() {
  pinMode(2,OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
 // pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  pinMode(buttonpin,INPUT); 
Serial.begin(9600); 
delay(1000); 
gsmSerial.begin(9600); 
delay(1000); 
gsmSerial.println("AT+CNMI=2,2,0,0,0");
delay(3000); 
Serial.print("Initializing……"); 
delay(2000); 
Serial.print("System Ready  "); 
delay(1000);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
safetyDistance = distance;
if (safetyDistance <= 30){
  //digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin, HIGH);
  digitalWrite(motorPin, HIGH);
  //delay(1000);
  voice.say(sp4_CAUTION);
  delay(500);
  voice.say(sp4_DANGER);
}
else{
  //digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(motorPin, LOW);
}
Serial.print("Distance: ");
Serial.println(distance);
sensorValue = analogRead(analogInPin);
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\n");
  delay(2);
  if((sensorValue>=100)&&(sensorValue<=600)){
    digitalWrite(2,HIGH);
    digitalWrite(motorPin, HIGH);
    voice.say(sp4_WARNING);
    delay(100);
    }
  else{
    digitalWrite(2,LOW);
    digitalWrite(motorPin, LOW);
    delay(100);
    }
   if(digitalRead(buttonpin)==HIGH) 
  { 
    Serial.println("button pressed");
    delay(1000);
    voice.say(sp2_BUTTON);
    voice.say(sp2_PRESS);
    delay(500);
    voice.say(sp2_DEVICE);
    voice.say(sp2_READY);
    SendMessage(); 
   }
  if (gsmSerial.available()>0)
 Serial.write(gsmSerial.read());
 while(gsmSerial.available())
   {
  gsmSerial.read();
  }
  while(Serial.available())
   {
   Serial.read();
  }
  get_gsm();
  }
 void get_gsm()
 {
  gsmSerial.listen();
 while(gsmSerial.available()>0)
 {Serial.println("INSIDE gsmSerial.available");
  if(gsmSerial.find("Track"))
   {Serial.println("INSIDE track");
  gsmSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1 second
  gsmSerial.println("AT+CMGS=\"+918920950852\"\r"); // Replace x with mobile number
   delay(1000);
  gsmSerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module
  delay(1000);
       }
    }
 }
 void SendMessage()
 {
  gsmSerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsmSerial.println("AT+CMGS=\"x\"\r"); // Replace x with mobile number
  delay(1000);
  gsmSerial.println("Please Help Me! I am in Danger!");// The SMS text you want to send
 delay(1000);
voice.say(sp4_INFORMATION);
  voice.say(sp5_ROLL_OUT);
  delay(1000);
  voice.say(sp4_EMERGENCY);
  voice.say(sp5_INBOUND);
  delay(500);
  voice.say(sp4_EXPECT);
  voice.say(sp4_ACTION);
 gsmSerial.println((char)26);
}
