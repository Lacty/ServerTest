
#pragma once

#include <iostream>

#include <thread>

#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class Client {
private:
  int sock;
  sockaddr_in addr;
  
  int recv_sock;
  sockaddr_in recv_addr;
  
  std::thread th_send;
  
  void send();
  
public:
  Client();
  
  void setup(const int port, const char* address);
  void update();
  void end();
};
