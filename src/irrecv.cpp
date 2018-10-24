#include <IRremote.h>
#include <Servo.h>

Servo servo;
int irPin=5;
int i;
int stat;
IRrecv irrecv(irPin);
decode_results results;
int leds[16] = {0b10000000,
                0b11000000,
                0b11100000,
                0b11110000,
                0b11111000,
                0b11111100,
                0b11111110,
                0b11111111,
                0b01111111,
                0b00111111,
                0b00011111,
                0b00001111,
                0b00000111,
                0b00000011,
                0b00000001,
                0b00000000};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  servo.attach(6);
  servo.write(180);
  irrecv.enableIRIn();
  i=0;
  stat = 0;
  digitalWrite(3, LOW);
  shiftOut(2, 4, MSBFIRST, leds[15]);
  digitalWrite(3, HIGH);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if(results.value == 0xa90)
    {
      stat = 1;
      Serial.println("high");
      servo.write(0);
      digitalWrite(8,HIGH);
    }
    else if(results.value == 0xa91)
    {
      stat = 0;
      Serial.println("reset");
      servo.write(180);
      digitalWrite(8,LOW);
      digitalWrite(3, LOW);
      shiftOut(2, 4, MSBFIRST, leds[15]);
      digitalWrite(3, HIGH);
    }
    irrecv.resume();
  }
  if(stat==1)
  {
    digitalWrite(3, LOW);
    shiftOut(2, 4, MSBFIRST, leds[i]);
    digitalWrite(3, HIGH);
    i=(i+1)%16;
  }
  delay(200);
}
