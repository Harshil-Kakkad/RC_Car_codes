#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define enA A0  
#define in1 A1
#define in2 A2
#define enB A5   
#define in3 A3
#define in4 A4
//jugal was here.
RF24 radio(7,8); // CE, CSN
const byte address[6] = "15042";
char receivedData[32] = "";
int  xAxis, yAxis;
int motorSpeedA = 0;
int motorSpeedB = 0;
int min=0,max=180;
int joystick[2]; 
 
void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
 
}
void loop() {
 
  if (radio.available()) {   // If the NRF240L01 module received data
     
      radio.read( joystick, sizeof(joystick) );
 
    radio.read(&receivedData, sizeof(receivedData));
    yAxis = joystick[0];
    xAxis = 1023-joystick[1];
    
    //Serial.print(yAxis);
    //Serial.print("\t");
    //Serial.println(xAxis);
 
  }
  //else{Serial.println("Hello World");}
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


  if(motorSpeedA<90){
    Serial.print("Left Back");
    Serial.print("\t");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    int in=map(motorSpeedA,89,0,0,255);
    analogWrite(enA,in);
  }
  else if(motorSpeedA>90){
    Serial.print("Left Forward");
    Serial.print("\t");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    int in=map(motorSpeedA,91,180,0,255);
    analogWrite(enB,in);
  }
  else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  if(motorSpeedB<90){
    Serial.println("Right Back");
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    int in=map(motorSpeedB,89,0,0,255);
    analogWrite(enB,in);
  }
  else if(motorSpeedB>90){
    Serial.println("Right Forward");
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    int in=map(motorSpeedB,91,180,0,255);
    analogWrite(enB,in);
  }
  else{
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}
