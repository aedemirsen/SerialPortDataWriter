
#include <SoftwareSerial.h>
#include <String.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

char *dataToSend;
char c;

int delayTime;
char incomingData[20];
int control = 0;

float nozzleTemp;
int pin1 = 0, pin2 = 1, pin3 = 2, pin4 = 3, pin5 = 4;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (control == 0) {
    delay(1000);
    control = 1;
  }
  int i = 0;
  while (Serial.available() > 0) { //verinin tamamini bitene kadar okur ve gelen veri degiskenine butun haliyle atar.
    c = Serial.read();  //her seferinde tek karakter okur. (byte)
    incomingData[i] = c;
    i++;
    incomingData[i] = '\0';
    delay(10);
  }
  control = 1;
  delayTime = atoi(incomingData);

  dataToSend = createDataBlock();
  Serial.print(dataToSend);
  delay(delayTime);
}


char *createDataBlock() {
  char tmpData1[10];
  char tmpData2[10];
  char tmpData3[10];
  char tmpData4[10];
  char tmpData5[10];
  char dataBlck[100] = "";
  char *dataBlock;
  ftoa(calculate(pin1), tmpData1, 2);
  ftoa(calculate(pin2), tmpData2, 2);
  ftoa(calculate(pin3), tmpData3, 2);
  ftoa(calculate(pin4), tmpData4, 2);
  ftoa(calculate(pin5), tmpData5, 2);
  strcat(dataBlck, "#");
  strcat(dataBlck, tmpData1);
  strcat(dataBlck, "-");
  strcat(dataBlck, tmpData2);
  strcat(dataBlck, "-");
  strcat(dataBlck, tmpData3);
  strcat(dataBlck, "-");
  strcat(dataBlck, tmpData4);
  /* strcat(dataBlck,"-");
    strcat(dataBlck, tmpData5);*/
  strcat(dataBlck, "&\n");
  dataBlock = dataBlck;
  return dataBlock;
}

float calculate(int thermistorPin) {
  float temperature;
  Vo = analogRead(thermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  temperature = T - 273.15;
  // Tf = (Tc * 9.0) / 5.0 + 32.0;  fahrenheit
  delay(20);
  return temperature;
}



