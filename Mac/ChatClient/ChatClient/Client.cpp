
#include "Client.hpp"


Client::Client() :
th_send(&Client::send, this)
{
  buf.clear();
}


void Client::send() {
  while(1) {
    // ソケット作成
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
      perror("accept");
      exit(1);
    }
  
    std::string str;
    
    // 入力
    std::getline(std::cin, str);
    
    // サーバに接続
    connect(sock, (sockaddr*)&addr, sizeof(addr));
    
    // 送信
    write(sock, &str[0], str.size());
  }
}

void Client::setup(const int port, const char* address) {
  // ソケット作成
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("accept");
    exit(1);
  }
  
  // 接続先を指定
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(address);
  
  std::cout << "名前を入力してください" << std::endl;
}

void Client::update() {
  th_send.join();
}

void Client::end() {
  close(sock);
}