#include<SPI.h>
#include<RF24.h>
// ce, csn pins
RF24 radio(9, 10);
int   Valor ;
char todo[50];

void setup(void){
radio.begin();
radio.setPALevel(RF24_PA_MAX);
radio.setChannel(0x76);
radio.openWritingPipe(0xF0F0F0F0E1LL);
radio.enableDynamicPayloads();
radio.powerUp();
Serial.begin(9600);
}
void loop(void){
 
    Valor = analogRead(0);
    
    if (Valor <= 500)  {
    sprintf(todo,"Sensor en el agua %d" , Valor,"h"); } 
    if ((Valor > 500) and (Valor <= 700)) { 
    sprintf(todo,"Humedo, no regar %d", Valor,"h");   }
    if (Valor > 700)  {
    sprintf(todo,"Seco, necesitas regar %d ", Valor,"h");}
    
    radio.write(&todo, sizeof(todo ));
   
    delay(1000);
}
