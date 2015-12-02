
#include "Client.h"
#include <string>


Client::Client() {}


void Client::sendToServer() {
  while (1) {
    // ソケット作成
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) exit(-1);

    std::string str;

    // 入力
    std::getline(std::cin, str);

    // サーバーに接続
    connect(sock, (sockaddr*)&addr, sizeof(addr));

    // 送信
    send(sock, &str[0], str.size(), 0);
  }
}

void Client::recieve() {}


void Client::setup(const int port, const char* address) {
  int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
  if (err != 0) exit(-1);

  // ソケット作成
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET)  exit(-1);

  // 接続先指定
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.S_un.S_addr = inet_addr(address);

  std::cout << "名前を入力してください" << std::endl;
}

void Client::update() {
  sendToServer();
}

void Client::end() {
  WSACleanup();
}