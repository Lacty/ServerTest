
#include "Client.h"
#include <string>


Client::Client() {}


void Client::sendToServer() {
  while (1) {
    // �\�P�b�g�쐬
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) exit(-1);

    std::string str;

    // ����
    std::getline(std::cin, str);

    // �T�[�o�[�ɐڑ�
    connect(sock, (sockaddr*)&addr, sizeof(addr));

    // ���M
    send(sock, &str[0], str.size(), 0);
  }
}

void Client::recieve() {}


void Client::setup(const int port, const char* address) {
  int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
  if (err != 0) exit(-1);

  // �\�P�b�g�쐬
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET)  exit(-1);

  // �ڑ���w��
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.S_un.S_addr = inet_addr(address);

  std::cout << "���O����͂��Ă�������" << std::endl;
}

void Client::update() {
  sendToServer();
}

void Client::end() {
  WSACleanup();
}