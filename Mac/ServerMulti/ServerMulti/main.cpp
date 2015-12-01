
#include <iostream>     // write() close()
#include <sys/fcntl.h>  // htons()
#include <sys/socket.h> // sockaddr socklen_t bind() accept() socket()
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_addr() inet_ntoa()

#include <ostream>

int main() {
  int sock;
  int conc_sock;
  sockaddr_in addr;
  sockaddr_in client;
  socklen_t len;
  int port = 79153;
  
  std::string str = "教室あついかもしれないかもしれない";
  
  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_len = sizeof(addr);
  
  bind(sock, (sockaddr*)&addr, sizeof(addr));
  
  listen(sock, 5);
  
  while (1) {
    len = sizeof(client);
    conc_sock = accept(sock, (sockaddr*)&client, &len);
    
    std::cout << "connect from :" << inet_ntoa(client.sin_addr) << std::endl;
    std::cout << "port ftom :" << ntohs(client.sin_port) << std::endl;
    
    send(conc_sock, str.c_str(), str.size(), 0);
    
    close(conc_sock);
  }
  
  close(sock);
  
  return 0;
}
