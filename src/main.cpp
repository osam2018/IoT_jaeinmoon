#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <IRremote.h>

int firePin = 0;
int shockPin = 10;
int smokePin = 12;
int tiltPin = 11;
int buttonPin = 2;
int buzzerPins[2] = {5,6};
int segmentRx = 8;
int segmentTx = 9;
SoftwareSerial segments =  SoftwareSerial(segmentRx, segmentTx);
IRsend irsend;

enum {
  tone_A=0,
  tone_AS,
  tone_B,
  tone_C,
  tone_CS,
  tone_D,
  tone_DS,
  tone_E,
  tone_F,
  tone_FS,
  tone_G,
  tone_GS
};

int DTMF[13][2]={
  {941,1336}, // frequencies for touch tone 0
  {697,1209}, // frequencies for touch tone 1
  {697,1336}, // frequencies for touch tone 2
  {697,1477}, // frequencies for touch tone 3
  {770,1209}, // frequencies for touch tone 4
  {770,1336}, // frequencies for touch tone 5
  {770,1477}, // frequencies for touch tone 6
  {852,1209}, // frequencies for touch tone 7
  {852,1336}, // frequencies for touch tone 8
  {852,1477}, // frequencies for touch tone 9
  {941,1209}, // frequencies for touch tone *
  {941,1477}, // frequencies for touch tone #
  {0,0} // pause
};

void playDTMF(byte digit, byte duration);
void dialNumber(byte number[],byte len);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  segments.begin(9600);
  pinMode(shockPin, INPUT);
  pinMode(smokePin, INPUT);
  pinMode(tiltPin, INPUT);
  pinMode(buzzerPins[0], OUTPUT);
  pinMode(buzzerPins[1], OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
}
// the loop function runs over and over again forever
void loop() {
  int fire;
  int shock;
  int smoke;
  int tilt;
  int rst;
  char buffer[5]={0,0,0,0,0};
  byte numbers[11] = {1,1,9};
  fire = analogRead(firePin);
  shock = digitalRead(shockPin);
  smoke = digitalRead(smokePin);
  tilt = digitalRead(tiltPin);
  rst = digitalRead(buttonPin);
  if(rst==1)
  {
    irsend.sendSony(0xa91, 12);
    buffer[0]='0';
    buffer[1]='0';
    buffer[2]='0';
    buffer[3]='0';
    delay(50);
  }
  if(fire<800 || smoke == 1 || shock == 0 || tilt == 1)
  {
    irsend.sendSony(0xa90, 12);
    buffer[0] = (fire<800?1:0)+'0';
    buffer[1] = smoke+'0';
    buffer[2] = !shock+'0';
    buffer[3] = tilt+'0';
    segments.write(buffer[0]);
    segments.write(buffer[1]);
    segments.write(buffer[2]);
    segments.write(buffer[3]);
    dialNumber(numbers,3);
    delay(50);
  }
  else 
  {
  }
  delay(100);
}

void playDTMF(byte digit, byte duration){
  boolean tone1state=false;
  boolean tone2state=false;
  unsigned long tone1delay=(500000/DTMF[digit][0])-10; // calculate delay (in microseconds) for tone 1 (half of the period of one cycle). 10 is a fudge factor to raise the frequency due to sluggish timing.
  unsigned long tone2delay=(500000/DTMF[digit][1])-10; // calculate delay (in microseconds) for tone 2 (half of the period of one cycle). 10 is a fudge factor to raise the frequency due to sluggish timing.
  unsigned long tone1timer=micros();
  unsigned long tone2timer=micros();
  unsigned long timer=millis(); // for timing duration of a single tone
  if(digit==12){
    delay(1000); // one second delay if digit is 12
  } else {
    while(millis()-timer<duration){
      if(micros()-tone1timer>tone1delay){
        tone1timer=micros(); // reset the timer
        tone1state=!tone1state; // toggle tone1state
        digitalWrite(buzzerPins[0], tone1state);
      }
      if(micros()-tone2timer>tone2delay){
        tone2timer=micros(); // reset the timer
        tone2state=!tone2state; // toggle tone2state
        digitalWrite(buzzerPins[1], tone2state);
      }
    }
    digitalWrite(buzzerPins[0],LOW);
    digitalWrite(buzzerPins[1],LOW);
  }
}

void dialNumber(byte number[],byte len){
  for(int i=0;i<len;i++){
    playDTMF(number[i], 200);  // 200 msec duration of tone
    delay(100); // 100 msec pause between tones
  }
}

