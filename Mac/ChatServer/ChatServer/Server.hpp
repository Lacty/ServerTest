
#pragma once

#include <iostream>
#include <vector>

#include <thread>

#include <sys/fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Member.hpp"


class Server {
private:
  std::vector<Member> members;
  
  bool is_registered;
  bool is_update_buf;
  
  int sock;
  sockaddr_in addr;
  int yes;
  
  int log_num;
  
  std::string buf_name;
  
  std::thread th_send;
  std::thread th_recieve;
  
  void send();
  void receive();
  
public:
  Server();
  
  void setup(const int port, const int backlog);
  void update();
  void end();
};