///servo direction settings
#include <Servo.h>
#define p_dir 8
#define left 0
#define center 50
#define right 111
Servo dir;

/// distance sensor settings
#include <Ultrasonic.h>
#define trig 6
#define echo 7
Ultrasonic ult(trig, echo);
int distance;
//tip for an optim evasion movement turn at 30 cm

// * indicators leds
#define wLed00 50
#define wLed01 51
#define wLed02 52
#define wLed03 53
#define buzzer 48
int ledArray[] = {wLed00, wLed01, wLed02, wLed03, buzzer};

// go_back sett
#define gb0 2
#define gb1 3

#define stop_ car(0,0)
#define go_   car(0,1)
#define back_ car(0,2)

#define left_ car(1,0)
#define left_go   car(1,1)
#define left_back car(1,2)

#define right_ car(2,0)
#define right_go car(2,1)
#define right_back car(2,2)


void setup() {
  Serial1.begin(115200); //start the wifi serial vel
  Serial.begin(115200); //start the board serial vel
  dir.attach(p_dir);    //assign the dir pinout
  dir.write(center);    //ceter the direction wheels at start

  for (int l = 0; l < sizeof(ledArray); l++) { //init the settings for the leds
    pinMode(ledArray[l], OUTPUT);
    digitalWrite(ledArray[l], HIGH);
    delay(200);
    digitalWrite(ledArray[l], LOW);
  }

  pinMode(gb0, OUTPUT);
  pinMode(gb1, OUTPUT);
  digitalWrite(gb0, LOW);
  digitalWrite(gb1, LOW);

  go_;
  delay(1000);
  back_;
  delay(1000);
  left_go;
  delay(1000);
  left_back;
  delay(1000);
  right_go;
  delay(1000);
  right_back;
  delay(1000);
  stop_;
  
}

void loop() {

}

void car(int LR, int GB) {
  // (00)center stop, (01)center go, (02) center back
  // (10)left stop, (11)left go, (12) left back
  // (20)rigth stop, (21)right go,(22)right back
  switch (LR) {
    case 0:
      dir.write(center);
      break;
    case 1:
      dir.write(left);
      break;
    case 2:
      dir.write(right);
      break;
  }

  switch (GB) {
    case 2:
      digitalWrite(gb0, HIGH);
      digitalWrite(gb1, LOW);
      break;
    case 1:
      digitalWrite(gb0, LOW);
      digitalWrite(gb1, HIGH);
      break;
    case 0:
      digitalWrite(gb0, LOW);
      digitalWrite(gb1, LOW);
      break;
  }
}


