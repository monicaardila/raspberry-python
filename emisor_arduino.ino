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
   int  h;
   int t;
   
   char Stierra[50];
   char Shumedad[50];
   char Stemperatura[50];
   char Scalor[50];
   
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
    
    if (Valor <= 500)  {sprintf(Stierra,"Sensor en el agua %d" , Valor ); } 
    if ((Valor > 500) and (Valor <= 700)) {sprintf(Stierra,"Humedo, no regar %d", Valor);}
    if (Valor > 700)  {sprintf(Stierra,"Seco, necesitas regar %d ", Valor);}
    
   // Leemos la humedad relativa
   h = dht.readHumidity();
   
   // Leemos la temperatura en grados centígrados (por defecto)
   t = dht.readTemperature();

   if (isnan(h) || isnan(t)) {Serial.println("Error obteniendo los datos del sensor DHT11");return;}
  
   // Calcular el índice de calor en grados centígrados
   int hic = dht.computeHeatIndex(t, h, false);

   sprintf(Shumedad,"Humedad : %d ", h);
   sprintf(Stemperatura,"Temperatura : %d ", t);
   sprintf(Scalor," Indice de calor: %d ", hic);

   radio.write(&Shumedad, sizeof(Shumedad));
   radio.write(&Stemperatura, sizeof(Stemperatura));
   radio.write(&Scalor, sizeof(Scalor));
   radio.write(&Stierra, sizeof(Stierra));
   
   delay(1000);
}
