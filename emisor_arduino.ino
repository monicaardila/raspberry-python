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
   int   hs ;
   int  h;
   int t;
   
   char variables[50];
   
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
    Serial.println("Sensor de Humedad valor:"); 
    hs = analogRead(0);
    
    if (hs <= 500)  Serial.println("*Sensor en el agua");  
    if ((hs > 500) and (hs <= 700)) Serial.println("*Humedo, no regar");
    if (hs > 700)     Serial.println("*Seco, necesitas regar");
    
   // Leemos la humedad relativa
   h = dht.readHumidity();
   
   // Leemos la temperatura en grados centígrados (por defecto)
   t = dht.readTemperature();

   if (isnan(h) || isnan(t)) {Serial.println("Error obteniendo los datos del sensor DHT11");return;}
  
   // Calcular el índice de calor en grados centígrados
   int hic = dht.computeHeatIndex(t, h, false);
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");

//sensor humedad dht ,temperatura,humedad suelindice de calor
   sprintf(variables,"%d;%d;%d;%d",h,t,hs,hic);

   radio.write(&variables, sizeof(variables));
   
   delay(1000);
}
