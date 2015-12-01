
#include "Client.h"


int main() {
  const int PORT = 79153;
  char ip_addr[] = "192.168.10.74";

  Client client;

  client.setup(PORT, ip_addr);

  client.update();

  client.end();

  return 0;
}