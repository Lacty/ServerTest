
//
// �ȒP��TCP�N���C�A���g
//


#include <winsock2.h>
#include <iostream>

int
main()
{
  WSAData wsaData;
  sockaddr_in server;
  SOCKET sock;
  char buf[32];

  // winsock2�̏�����
  int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
  if (err != 0) return -1;

  // �\�P�b�g�̍쐬
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET) return -1;

  // �ڑ���w��p�\���̂�����
  server.sin_family = AF_INET;
  server.sin_port = htons(12345);
  server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

  // �T�[�o�[�ɐڑ�
  connect(sock, (sockaddr*)&server, sizeof(server));

  // �T�[�o�[����f�[�^����M
  memset(buf, 0, sizeof(buf));
  int n = recv(sock, buf, sizeof(buf), 0);

  printf("%d, %s\n", n, buf);

  // winsock2�̏I������
  WSACleanup();

  return 0;
}