
//
// �ȒP��TPC�T�[�o
//


#include <winsock2.h>
#include <iostream>

int
main()
{
  WSAData wsaData;
  SOCKET sock0;
  sockaddr_in addr;
  sockaddr_in client;
  int len;
  SOCKET sock;

  std::string str = "��������";

  // winsock2�̏�����
  int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
  if (err != 0) return -1;

  // �\�P�b�g�̍쐬
  sock0 = socket(AF_INET, SOCK_STREAM, 0);
  if (sock0 == INVALID_SOCKET) return -1;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(73591);
  addr.sin_addr.S_un.S_addr = INADDR_ANY;
  bind(sock0, (sockaddr*)&addr, sizeof(addr));

  // TPC�N���C�A���g����ڑ��v����҂Ă��Ԃɂ���
  listen(sock0, 5);

  // TPC�N���C�A���g����̐ڑ��v�����󂯎��
  len = sizeof(client);
  sock = accept(sock0, (sockaddr*)&client, &len);

  // 5�������M
  send(sock, str.c_str(), str.size(), 0);

  // TCP�Z�b�V�����I��
  closesocket(sock);

  // winsock2�̏I������
  WSACleanup();

  return 0;
}