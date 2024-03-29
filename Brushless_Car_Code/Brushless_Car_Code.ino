#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <String.h>
#include <stdlib.h>
int max=110;
int min=70;

RF24 radio(8,7); // CE, CSN
const byte address[6] = "15042";
char receivedData[32] = "";
int  xAxis, yAxis;
int motorSpeedA = 0;
int motorSpeedB = 0;
int joystick[2]; 
Servo LESC;
Servo RESC;

String data,xD,yD;
int x,y;
int d[2];
 
void setup() {
Serial.begin(9600);
  LESC.attach(6,1000,2000);
  RESC.attach(3,1000,2000);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); 
}
void loop() {
 
  if (radio.available()) {   // If the NRF240L01 module received data
     
    radio.read(d, sizeof(d));
    xAxis=d[1];
    yAxis=d[0];
    /*xD = data.substring(0, 4);
    yD = data.substring(4, 8);
    x=xD.toInt();
    y=yD.toInt();

    // Print received values
    Serial.println(data);*/
    /*Serial.print("Received Analog 1: ");
    Serial.print(d[0]);
    Serial.print("\t Received Analog 2: ");
    Serial.println(d[1]);*/
 
  }
  else{
    LESC.write(90);
    RESC.write(90);
  }
  
  if(yAxis<470 || yAxis>550){
    motorSpeedA=map(yAxis,0,1023,min,max);
    motorSpeedB=map(yAxis,0,1023,min,max);
    
  }
  else {
    motorSpeedA = 90;
    motorSpeedB = 90;
  }
  if(xAxis<470){
    int xMapped = map(xAxis, 0, 512, 90, min);
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
  }
  else if(xAxis>550){
    int xMapped = map(xAxis, 1023, 512, 90, min);
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
  }
  //limiting 
  if(motorSpeedA>max){motorSpeedA=max;}
  if(motorSpeedA<min){motorSpeedA=min;}
  if(motorSpeedB>max){motorSpeedB=max;}
  if(motorSpeedB<min){motorSpeedB=min;}

  /*if(motorSpeedA>=90 && motorSpeedA<=120){motorSpeedA=90;}//91 to 120
  else if(motorSpeedA>120 && motorSpeedA<=150){motorSpeedA=150;}//121 to 150
  else if(motorSpeedA>150 && motorSpeedA<=180){motorSpeedA=180;}//151 to 180

  else if(motorSpeedA>60 && motorSpeedA<90){motorSpeedA=60;}//61 to 90
  else if(motorSpeedA>30 && motorSpeedA<=60){motorSpeedA=30;}//31 to 60
  else if(motorSpeedA>=0 && motorSpeedA<=30){motorSpeedA=0;}//0 to 30

  if(motorSpeedB>=90 && motorSpeedB<=120){motorSpeedB=90;}//91 to 120
  else if(motorSpeedB>120 && motorSpeedB<=150){motorSpeedB=150;}//121 to 150
  else if(motorSpeedB>150 && motorSpeedB<=180){motorSpeedB=180;}//151 to 180

  else if(motorSpeedB>60 && motorSpeedB<90){motorSpeedB=60;}//61 to 90
  else if(motorSpeedB>30 && motorSpeedB<=60){motorSpeedB=30;}//31 to 60
  else if(motorSpeedB>=0 && motorSpeedB<=30){motorSpeedB=0;}//0 to 30*/
  RESC.write(motorSpeedB);
  LESC.write(motorSpeedA);
  Serial.print("Left = ");
  Serial.print(motorSpeedA);
  Serial.print("\t");
  
  Serial.print("Right = ");
  Serial.println(motorSpeedB);
}
