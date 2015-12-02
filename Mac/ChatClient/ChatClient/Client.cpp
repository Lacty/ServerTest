
#include "Client.hpp"


Client::Client() :
th_send(&Client::send, this) {}


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
    
    // recvコマンドを送った場合受信する
    if (str == "recv") {
      str.clear();
      str.resize(BUFSIZ);
      read(sock, &str[0], str.size());
      if (str[0] != '\0')
        std::cout << str;
    }
    
    // ソケット封鎖
    close(sock);
  }
}

void Client::setup(const int port, const char* address) {
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