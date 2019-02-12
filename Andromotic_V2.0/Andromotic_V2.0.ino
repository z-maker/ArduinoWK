String ATCMD [] =
  {
    "AT+CWQAP",
    "AT+CWMODE=3",
    "AT+CWSAP?",
    "AT+CIPMUX=1",
    //"AT+CWLAP",
    //"AT+CWJAP=\"(-(-(-_-)-)-)\",\"Stewee666@killer.sys32x86\"",
    "AT+CIPSERVER=1,6789",
    "AT+CIFSR",
    "END"           //FINAL DE LOS COMANDOS
  };

  

String W;
char   w;

#define baud0 9600
#define baud1 115200

#define X0  42
#define X1  43
#define X2  44
#define X3  45
#define X4  46
#define X5  47
#define X6  48
#define X7  49
#define X8  50
#define X9  51
#define X10 52
#define X11 53
byte l []={X0,X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11};
void setup(){
  Serial1.begin(baud0);
  Serial.begin(baud0);
  delay(1000);

  int index=0;
  
  while(ATCMD[index] != "END"){
   
    Serial1.println(ATCMD[index++]); //escribir la configuracion del modulo wifi

    while(true){
      String s = GetLineWIFI();
      if(s!="")Serial.println(s);
      if(s.startsWith("no change"))break;//////////
      if(s.startsWith("OK"))break;       //
      if(s.startsWith("ready"))break;   ////////////
    }
    Serial.println("............comand sucess...............");
  }
  
  pinMode(X0 ,OUTPUT);
  pinMode(X1 ,OUTPUT);
  pinMode(X2 ,OUTPUT);
  pinMode(X3 ,OUTPUT);
  pinMode(X4 ,OUTPUT);
  pinMode(X5 ,OUTPUT);
  pinMode(X6 ,OUTPUT);
  pinMode(X7 ,OUTPUT);
  pinMode(X8 ,OUTPUT);
  pinMode(X9 ,OUTPUT);
  pinMode(X10,OUTPUT);
  pinMode(X11,OUTPUT);

  pinMode(13,OUTPUT);
  delay(25);
  digitalWrite(13,HIGH);
  
}

void loop(){

  
  
  if(Serial1.available()){  //imprime lo que entra del wifi al serial
    w = Serial1.read();
    Serial.print(w);
    W = W + w;
  }

  if(Serial.available()){ //imprime lo que entra del serial wifi
    char s = Serial.read();
    Serial1.print(s);
  }

  if(w=='\n'){  //si se pulsa intro
    
     if ( W.indexOf("a") > 0 )    // Comprobamos si q esta incluido en el string
               {
                 digitalWrite( X0, !digitalRead(X0)) ;
                 
               }

     if ( W.indexOf("b") > 0 )
               {
                 digitalWrite( X1, !digitalRead(X1)) ;
                 
               }
     if ( W.indexOf("c") > 0 )
               {
                 digitalWrite( X2, !digitalRead(X2)) ;
                 
               }
    if ( W.indexOf("d") > 0 )
               {
                 digitalWrite( X3, !digitalRead(X3)) ;
                 
               }
    if ( W.indexOf("e") > 0 )
               {
                 digitalWrite( X4, !digitalRead(X4)) ;
                 
               }  

    if ( W.indexOf("f") > 0 )
               {
                 digitalWrite( X5, !digitalRead(X5)) ;
                 
               }
    
    if ( W.indexOf("g") > 0 )
               {
                 funny();
                 
               }
    if ( W.indexOf("h") > 0 )//apagr todos
               {
                 offAll();
                 
               }
    if ( W.indexOf("i") > 0 )//encender todos
               {
                 onAll();
                 
               }

    
  
    W = "" ;
    w = ' ';
  }
}



String GetLineWIFI(){
  String S = "";
  if(Serial1.available()){
    char c= Serial1.read();
    while(c != '\n'){
      S = S + c;
      delay(25);
      c = Serial1.read();
    }
  }
  return (S);
}

void onAll(){
  
  for(int x =0; x<12; x++){
      digitalWrite(l[x],HIGH);
  }
}

void offAll(){
  
  for(int x =0; x<12; x++){
      digitalWrite(l[x],LOW);
  }
}

void funny(){
  offAll();
  digitalWrite(13,LOW);
  for(int x=0; x<5; x++){
    int r = random(0,11);
    delay(90);
    digitalWrite(l[r],HIGH);
    delay(90);
    digitalWrite(l[r],LOW);
  }
  
 for(int x=0; x<5; x++){
  for(int x=0; x<7; x++){
    delay(100);
    digitalWrite(l[x],HIGH);
    
  }
  for(int x=0; x<7; x++){
    delay(100);
    digitalWrite(l[x],LOW);
    
  }
 }
  digitalWrite(13,HIGH);
}


