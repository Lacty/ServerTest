
#include <iostream>

#include "Server.hpp"


int main() {
  const int PORT = 79153;
  
  Server server;
  server.setup(PORT, 5);
  
  server.update();
  
  server.end();
  
  return 0;
}
