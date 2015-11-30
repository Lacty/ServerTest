
#include <iostream>     // write() close()
#include <sys/fcntl.h>  // htons()
#include <sys/socket.h> // sockaddr socklen_t bind() accept() socket()
#include <netinet/in.h> // sockaddr_in

#include <ostream>

int main() {
  int sock;
  int conc_sock;
  sockaddr_in addr;
  sockaddr_in client;
  socklen_t len;
  int port = 73591;
  
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
    
    if (conc_sock < 0) {
      std::cout << "accept faild" << std::endl;
      return -1;
    } else {
      std::cout << "accept" << std::endl;
    }
    
    std::cout << str.c_str() << ":" << str.size() << std::endl;
    write(conc_sock, str.c_str(), str.size());
    
    close(conc_sock);
  }
  
  close(sock);
  
  return 0;
}
