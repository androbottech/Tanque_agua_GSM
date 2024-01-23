#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial SIM(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

#define MOTOR 12

String dato;

void setup()
{
  pinMode(MOTOR,OUTPUT);
  digitalWrite(MOTOR,HIGH);
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  SIM.begin(9600);

  //Serial.println("Initializing...");
  delay(1000); 
  SIM.println("AT");
  delay(500);
  SIM.println("AT");
  delay(500);
  SIM.print("AT+CLIP=1\r\n"); //Enable Caller ID
  delay(500);
  digitalWrite(A3,HIGH);
}

void loop()
{
  //updateSerial();
  if(SIM.available()>0)
    { dato=SIM.readString();
      delay(50);
  if(dato.indexOf("67563898") > -1 || dato.indexOf("71417212") > -1|| dato.indexOf("71309733") > -1 )//PREGUNTAR si aparece NUMERO"llamada"
  {
    //Serial.println("LLAMADA RECIBIDA");
    if(digitalRead(MOTOR)==HIGH)
      {digitalWrite(MOTOR,LOW);delay(100);}
    else
      {digitalWrite(MOTOR,HIGH);delay(100);}
    delay(100);
    SIM.println("ATH");
    delay(100);
    //SIM.println("ATH");
    //delay(100);
  }
  dato="";
    }
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    SIM.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(SIM.available()) 
  {
    Serial.write(SIM.read());//Forward what Software Serial received to Serial Port
  }
}
