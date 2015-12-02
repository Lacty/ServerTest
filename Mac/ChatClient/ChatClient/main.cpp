
#include "Client.hpp"


int main() {
  const int PORT = 37397;
  char ip_addr[] = "127.0.0.1";

  Client client;
  
  client.setup(PORT, ip_addr);
  
  client.update();
  
  client.end();
  
  return 0;
}
