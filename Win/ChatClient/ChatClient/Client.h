
#pragma once

#include <winsock2.h>
#include <iostream>


class Client {
private:
  WSADATA wsaData;
  sockaddr_in addr;
  SOCKET sock;

  void sendToServer();
  void recieve();

public:
  Client();

  void setup(const int port, const char* address);
  void update();
  void end();
};