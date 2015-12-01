
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
  
  int server_sock;
  sockaddr_in server_addr;
  socklen_t server_len;
  int yes;
  
  std::thread th_send;
  std::thread th_recieve;
  
  void send();
  void recieve();
  
public:
  Client();
  
  void setup(const int port, const char* address);
  void update();
  void end();
};
