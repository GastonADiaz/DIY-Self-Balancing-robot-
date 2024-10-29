#include <SoftwareSerial.h>  // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos del Arduino conectados al Bluetooth

void setup()
{
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  Serial.println("Listo");
  BT.begin(38400);      // Inicializamos el puerto serie BT (Para Modo AT 2)
}
 
void loop()
{
  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    Serial.write(BT.read());    // Lee BT y  envia a arduino
  }
 
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     BT.write(Serial.read()); // Lee arduino y envia a BT
  }
}
