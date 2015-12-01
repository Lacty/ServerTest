
#include "Client.hpp"


Client::Client() :
yes(1) {}


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

void Client::recieve() {
  while(1) {
    server_len = sizeof(server_addr);
    int _sock = accept(server_sock, (sockaddr*)&server_addr, &server_len);
    if (_sock < 0) {
      perror("accept");
      exit(1);
    }
    std::string str;
    str.resize(BUFSIZ);
    read(_sock, &str[0], str.size());
    
    std::cout << str.c_str() << std::endl;
  }
}

void Client::setup(const int port, const char* address) {
  // ソケット作成
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("socket");
    exit(1);
  }
  
  // 接続先を指定
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(address);
  
  
  // ソケット作成
  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0) {
    perror("socket");
    exit(1);
  }
  
  // 接続先を指定
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(77777);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_len = sizeof(server_addr);
  
  //
  // 必ずbindできるように設定
  setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(yes));
  
  // ソケットとアドレスを紐ずける(bindする)
  int b = bind(server_sock, (sockaddr*)&server_addr, sizeof(server_addr));
  if (b != 0) {
    perror("bind");
    exit(1);
  }
  
  // サーバーから接続要求を待てる状態にする
  // 同時接続できる最大数を設定(?)
  listen(server_sock, 1);
  
  std::cout << "名前を入力してください" << std::endl;
  
  th_send = std::thread(&Client::send, this);
  th_recieve = std::thread(&Client::recieve, this);
}

void Client::update() {
  th_send.join();
  th_recieve.join();
}

void Client::end() {
  close(sock);
}