#define b0 9600
#define b1 115200
#define NOTE_ON 0x90
#define NOTE_OFF 0x80

String W = " ";
char w;
char notes[6];

byte cmd=0;
int note=0;
int volume=0;
int chanel=0;

void setup() {
  Serial.begin(b1);
  Serial1.begin(b1);
  pinMode(13, OUTPUT);
}
void loop() {
  if (Serial1.available()) {
    w = Serial1.read();
    if (w == '(') {
      cmd=0;
      note=0;
      volume=0;
      chanel=0;
      int x = 0;
      while (w != ')') {
        delay(10);
        w = Serial1.read();
        x++;
        switch (x) {
          case 1:
            if (w == '+')cmd = NOTE_ON;
            if (w == '-')cmd = NOTE_OFF;
            break;
          case 2:
            chanel = w-48;
            break;
          case 3:
            note = w;
            break;
          case 4:
            volume = w;
            break;
          case 5:
          Serial.write(cmd+chanel);
          Serial.write(note);
          Serial.write(volume);
          break;
        }
      }
      
    }    
  }

  if (Serial.available()) {
    char s = Serial.read();
    Serial1.print(s);
  }

}
