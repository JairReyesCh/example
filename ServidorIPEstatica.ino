#include <SPI.h>
#include <Ethernet.h>

const unsigned int BAUD_RATE = 9600;

byte mac [ ] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // MAC de Arduino
IPAddress ip(192, 168, 1, 199); // dirección IP estática
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(8000); // Puerto de acceso

void setup() {
  Serial.begin(BAUD_RATE);
  Ethernet.begin(mac, ip, gateway, subnet); // Inicialización de TCP/IP
  server.begin(); // Inicialización servidor
}
void loop()
{
  EthernetClient client = server.available(); // Se evalúa la disponibilidad del servidor

  if (client)
  {
    while (client.connected()) {
      if (client.available()) {
        char mensaje = client.read();
        server.write(mensaje);
      }
    }
    client.stop();
  }
}
