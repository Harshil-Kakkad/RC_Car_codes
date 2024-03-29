#include <string.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9,10); // CE, CSN
const byte address[6] = "15042";
//jugal was here.
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
}

int data[2];
char str1[4],str2[4],str[8];

void loop() {
 
  data[0]=analogRead(A0);
  data[1]=1023-analogRead(A1);
  Serial.print(data[0]);
  Serial.print("\t");
  Serial.println(data[1]);

  /*sprintf(str1, "%04d", data[0]);
  sprintf(str2, "%04d", data[1]);
  strcpy(str, str1);
  strcat(str, str2);*/

  // Transmit the data
  radio.write(data, sizeof(data));
  delay(50);
  
}
