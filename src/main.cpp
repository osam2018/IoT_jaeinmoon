#include <Arduino.h>
#include <Servo.h>

int firePin = 0;
int shockPin = 13;
int smokePin = 12;
int tiltPin = 11;
int buzzerPin = 10;
int servoPin = 9;
int relayPin = 8;

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
Servo servo;

void open_door() {
  servo.write(90);
}

void close_door() {
  servo.write(0);
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(shockPin, INPUT);
  pinMode(smokePin, INPUT);
  pinMode(tiltPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
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
}
