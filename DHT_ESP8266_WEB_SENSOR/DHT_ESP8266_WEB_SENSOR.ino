#include <DHT.h>// importar la libreria del sensor temperatura

#define DHT_PIN 7 //pin donde se conectara el pin data del sensor
#define DHT_TYPE DHT11 //tipo por que existe el DHT22 tambien

// definir los valores de comunicacion del serial,
//el wifi puede venir por defecto en alguno de los dos
#define BAUD_9600 9600
#define BAUD_115200 115200 

DHT sensor (DHT_PIN,DHT_TYPE); //crear la instancia del sensor  DHT s (pin de datos,tipo de sensor)

int humedad; // variable almacenar datos de humedad
int temperatura;//variable almacenar datos de temperatura

String ssid ="TOR NET ACCESS"; //"(-(-(-_-)-)-)";//cadena con el nombre de la red a la que se conectara el sensor
String key  = "TheKiller666";//"CICADA0333";// cadena con la clave de la red

char   w;//tipo character que recibira las peticiones
String W; // cadena para almacenar todos los datos de entrada de peticiones del sensor

// array tipo string que escribira los comandos at 
//para configurar el wifi en modo AccesPoint y Cliente
//buscar comandos AT ES8266 para detalles
String ModeBOTH[] = {
  
  "AT+CWMODE=3",//CAMBIAR A MODO dual
  "AT+CWSAP?",
  "AT+CWQAP",//DESCONECTARSE DEL AP
 // "AT+CWLAP",//LISTAR CONECCIONES DISPONIBLES
  "AT+CWJAP=\"" +ssid + "\",\"" + key + "\"",//comando at para conectar a la red
  "AT+CWJAP?",//COMPROBAR A QUE AP ESTA CONECTADO
  "AT+CIPMUX=1",//PARA PERMITIR MULTIPLES CONECCIONES
  "AT+CIPSERVER=1,6789",//INICIAR EL SERVIDOR 0=CLOSE 1=OPEN , PORT
  "AT+CIPSTA?",//VER  IP ASIGNADA POR EL AP
  "YA_XD"//saber cuando termina los comandos
};




void setup() {
  // Todas las configuraciones e inicializacion de variables aqui (¬_¬)
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  Serial.begin(BAUD_115200);//iniciar la comunicacion del arduino 
  Serial1.begin(BAUD_115200);//iniciar la comunicacion del serial para wifi
  //ambos deben tener el mismo valor en baudios
  
  delay(1000);//una espera de 1 seg para darle tiempo a que se inicie el wifi
  sensor.begin();//iniciar las lectiras del sensor temperatura
  
  //pasarle la lista de ordenes al metodo para que escriba las ordenes AT al modulo
   setupWMODE(ModeBOTH);
   digitalWrite(13,HIGH);
}

void loop() {
  // toda la logica del programa aqui (¬_¬)!:

  humedad=sensor.readHumidity();//leer valor del sensor hum
  temperatura=sensor.readTemperature();//leer valor del sensor temp


  if (Serial1.available())
  {
    w = Serial1.read() ;
    Serial.print(w);
    W=W+w;
    if (w == 71)
    {
      Serial.println("Enviando web request");
      webBody();
      delay(500);
    }
  }
  
  if (Serial.available())
  {
    char c = Serial.read();
    Serial1.print(c);
  }

}


//metodos 
void setupWMODE(String ordenes[]){//para configirar el wifi
  int index = 0;
  while (ordenes[index] != "YA_XD")
  { 
    Serial1.println(ordenes[index++]);
      while ( true)
      {
        String s = GetLineWIFI(); //llamada a metodo para almacenar lo que responde el modulo
          if ( s != "") Serial.println(s);
          if ( s.startsWith("no change")) break;
          if ( s.startsWith("OK"))break;
          if ( s.startsWith("ready"))break;
    }
    Serial.println("....................");
  }
}


String GetLineWIFI()//metodo para concatenar lo que responde el wifi
{ 
  String S = "" ;
    if (Serial1.available())
    { 
      char c = Serial1.read(); ;
        while ( c != '\n' )            //Hasta que el caracter sea intro
        {
         S = S + c ;
        delay(25) ;
        c = Serial1.read();
        }
    return ( S ) ;
  }
}


void webBody(void)//metodo para constriur el cuerpo de la pagina web (Personalizar (e.e)/ )
{
  http("<!DOCTYPE HTML>");
  http("<html lang=\"es\">");
  http("<meta charset=\"UTF-8\">");
  http("<head><title>Practica</title>");
  http("<meta http-equiv=\"refresh\" content=\"5\"></head>");
  http("<body style=\"background-color:#9900ff;\"><center><h1 style=\"color:rgb(255,255,255);\"> Practica de la Unidad 6 </center></h1>");
  http("<center><h2 style=\"color:rgb(255,255,255);\">Temperatura = "+(String)temperatura+" C°</h2></center>");
  http("<center><h2 style=\"color:rgb(255,255,255);\">Humedad relativa = "+(String)humedad+"</h2></center>");
  http("</body>");
  http("</html>");

  delay(10);
  Serial1.println("AT+CIPCLOSE=0");
  delay(500);
}

void http(String output)//metodo para enviar linea por linea el cuerpo de la pagina al nagegador del pc
{
  Serial1.print("AT+CIPSEND=0,");              // AT+CIPSEND=0, num evia datos alcliente
  Serial1.println(output.length());            //ver detalles en comandos at
  if (Serial1.find(">"))                       // Si recibimos la peticion del mensaje
  { 
    Serial.println(output);
    Serial1.println(output);            //Aqui va el string hacia el WIFI
    delay(10);
    while ( Serial1.available() > 0 )
    { 
      if (  Serial1.find("SEND OK") )    // Busca el OK en la respuesta del wifi para saber que envio la pag completa
      break;
    }
  }
}

