#include <Arduino.h>
int seven_seg_digits[10] = {     0b00000011,  // = 0
                                 0b10011111,  // = 1
                                 0b00100101,  // = 2
                                 0b00001101,  // = 3
                                 0b10011001,  // = 4
                                 0b01001001,  // = 5
                                 0b01000001,  // = 6
                                 0b00011111,  // = 7
                                 0b00000001,  // = 8
                                 0b00011001   // = 9
                                 };
int dataPin = 2;
int latchPin = 3;
int clockPin = 4;
int segSelectPins[4] = {8,9,10,11};
void setup() {
  // put your setup code here, to run once:
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(segSelectPins[0], OUTPUT);
  pinMode(segSelectPins[1], OUTPUT);
  pinMode(segSelectPins[2], OUTPUT);
  pinMode(segSelectPins[3], OUTPUT);
  Serial.begin(9600);
}

int segDisplay[4] = {0,0,0,0};
int j=3;

void loop() {
  // put your main code here, to run repeatedly
  int i;
  byte buf[4];
  if(Serial.available()>0)
  {
    Serial.readBytes(buf, 4);
    segDisplay[0]=buf[0]-'0';
    segDisplay[1]=buf[1]-'0';
    segDisplay[2]=buf[2]-'0';
    segDisplay[3]=buf[3]-'0';
  }
  for(int i=0;i<4;++i)
  {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, seven_seg_digits[segDisplay[i]]);
    digitalWrite(latchPin, HIGH);
    digitalWrite(segSelectPins[j],LOW);
    j=(j+1)%4;
    digitalWrite(segSelectPins[j],HIGH);

    delay(5);
  }
}
