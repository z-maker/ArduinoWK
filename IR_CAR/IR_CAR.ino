#include <IR_Control.h>
#include <IRremote.h>
#include <Servo.h>

#define back 22
#define go 23

#define dir 24
Servo DIR;

#define IR_rx 25
IRrecv IRrx(IR_rx);
decode_results IR_decoded;
byte IRrec;

int adelante = 90;
int derecha = 120;
int izquierda = 60;

void setup() {
  Serial.begin(9600);
  
  pinMode(back,OUTPUT);
  pinMode(go,OUTPUT);
  digitalWrite(back,LOW);
  digitalWrite(go,LOW);
  
  DIR.attach(dir);
  DIR.write(90);
  
  IRrx.enableIRIn();
  
}

void loop() {

  if(IRrx.decode(&IR_decoded))
  {
    IRrec = IR_decoded.value,HEX;
    switch(IRrec)
    {
      case BTN_PP:
        DIR.write(adelante);
      break;
      case BTN_NEXT:
        DIR.write(derecha);
      break;
      case BTN_BACK:
        DIR.write(izquierda);
      break;
      case BTN_ADD:
        digitalWrite(go,HIGH);
        digitalWrite(back,LOW);
      break;
      case BTN_DEC:
        digitalWrite(go,LOW);
        digitalWrite(back,HIGH);
      break;
      case BTN_EQ:
        digitalWrite(go,LOW);
        digitalWrite(back,LOW);
      break;
    }
    Serial.println(IRrec);
    IRrx.resume();
  }
}

