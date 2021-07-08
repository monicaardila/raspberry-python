// Incluimos librería
   #include<SPI.h>
   #include<RF24.h>
   #include <DHT.h>
   
// Definimos el pin digital donde se conecta el sensor 
   #define DHTPIN 2 
   
// Definimos el pin analogo para ce y csn donde se conecta el sensor 
   RF24 radio(9, 10);
   
// Dependiendo del tipo de sensor
   #define DHTTYPE DHT11   
   
// Definimos variables    
   int   Valor ;
   char todo[50];
// Inicializamos el sensor DHT11
   DHT dht(DHTPIN, DHTTYPE);

   void setup(void){
   radio.begin();
   radio.setPALevel(RF24_PA_MAX);
   radio.setChannel(0x76);
   radio.openWritingPipe(0xF0F0F0F0E1LL);
   radio.enableDynamicPayloads();
   radio.powerUp();
   // Inicializamos comunicación serie
   Serial.begin(9600);
   // Comenzamos el sensor DHT 
  dht.begin();
}
void loop(void){
 
    Valor = analogRead(0);
    
    if (Valor <= 500)  {sprintf(todo,"Sensor en el agua %d" , Valor,"h"); } 
    if ((Valor > 500) and (Valor <= 700)) {sprintf(todo,"Humedo, no regar %d", Valor,"h");}
    if (Valor > 700)  {sprintf(todo,"Seco, necesitas regar %d ", Valor,"h");}
    
    radio.write(&todo, sizeof(todo ));
   
    delay(1000);
}
