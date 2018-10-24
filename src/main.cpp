#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

int firePin = 0;
int shockPin = 13;
int smokePin = 12;
int tiltPin = 11;
int buzzerPins[2] = {9,10};
int servoPin = 6;
int relayPin = 8;
int segmentRx = 2;
int segmentTx = 3;
SoftwareSerial segments =  SoftwareSerial(segmentTx, segmentRx);
Servo servo;

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
void open_door() {
  servo.write(90);
}

void close_door() {
  servo.write(0);
}

void playDTMF(byte digit, byte duration);
void dialNumber(byte number[],byte len);

// the setup function runs once when you press reset or power the board
void setup() {
  segments.begin(9600);
  pinMode(shockPin, INPUT);
  pinMode(smokePin, INPUT);
  pinMode(tiltPin, INPUT);
  pinMode(buzzerPins[0], OUTPUT);
  pinMode(buzzerPins[1], OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  servo.attach(servoPin);
}

// the loop function runs over and over again forever
void loop() {
  int fire;
  int shock;
  int smoke;
  int tilt;
  fire = analogRead(firePin);
  shock = digitalRead(shockPin);
  smoke = digitalRead(smokePin);
  tilt = digitalRead(tiltPin);
  delay(500);
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
    playDTMF(number[i], 1000);  // 100 msec duration of tone
    delay(1000); // 100 msec pause between tones
  }
}

