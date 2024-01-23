#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

#define sensor1 6
#define sensor2 5

void setup()
{
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(13, OUTPUT);
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  //Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  //updateSerial();
  delay(1000);
  digitalWrite(13, LOW);
  preguntar();
}

void loop()
{
  //no usamos el bucle infinito
}

void preguntar()
{
    //esta lleno el tanque!
  if(digitalRead(sensor1)==LOW && digitalRead(sensor2)==LOW)
    {
      lleno();
    }
  //esta vacio el tanque?
  if(digitalRead(sensor1)==HIGH && digitalRead(sensor2)==HIGH)
    {
      vacio();
    }

    //esta a la mitad el tanque?
  if(digitalRead(sensor1)==LOW && digitalRead(sensor2)==HIGH)
    {
      mitad();
    }
}
void lleno()
{
  i4:
  //esta vacio el tanque?
  if(digitalRead(sensor1)==HIGH && digitalRead(sensor2)==HIGH)
    {vacio();}
    else
    {goto i4;}
}
void vacio()
{
  //esta vacio el tanque?
  if(digitalRead(sensor1)==HIGH && digitalRead(sensor2)==HIGH)
    {
      llamar();//activar bomba de agua
      //ya esta A LA MITAD tanque?
      i1:
       if(digitalRead(sensor1)==LOW && digitalRead(sensor2)==HIGH)
       {goto i2;}
       else
       {goto i1;}
       //esta lleno el tanque!
       i2:
       if(digitalRead(sensor1)==LOW && digitalRead(sensor2)==LOW)
       {llamar();
       lleno();}
       else
       {goto i2;}
    }
}
void mitad()
{
  llamar();//activar bomba de agua
       //esta lleno el tanque?
       i6:
       if(digitalRead(sensor1)==LOW && digitalRead(sensor2)==LOW)
       {llamar();
       lleno();}
       else
       {goto i6;}
}

void llamar()
{
  mySerial.println("ATD+ +59164831860;");
  delay(7000); // wait for 7 seconds...
  mySerial.println("ATH"); //hang up
  delay(100);
}
