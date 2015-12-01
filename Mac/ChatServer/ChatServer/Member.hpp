
#pragma once
#include <string>

#include <netinet/in.h>


class Member {
public:
  int         sock;
  bool        is_active;
  socklen_t   len;
  std::string name;
  std::string buf;
  sockaddr_in addr;
  
  Member();
};
