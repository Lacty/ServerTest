
#include <iostream>

#include "Server.hpp"


int main() {
  const int PORT = 37397;
  
  Server server;
  server.setup(PORT, 5);
  
  server.update();
  
  server.end();
  
  return 0;
}
