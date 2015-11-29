
#include <winsock2.h>
#include <iostream>


void
ErrWSA(int err);

int
main()
{
  int err;
  WSAData wsaData;
  SOCKET  sock;

  err = WSAStartup(MAKEWORD(2, 0), &wsaData);
  if (err != 0) {
    ErrWSA(err);
    return -1;
  }

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET) {
    std::cout << "socket failed\n";
    return -1;
  }

  WSACleanup();

  return 0;
}

void
ErrWSA(int err) {
  switch (err) {
  case WSASYSNOTREADY:
    std::cout << "�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��܂���\n";
    break;
  case WSAVERNOTSUPPORTED:
    std::cout << "�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��܂���\n";
    break;
  case WSAEINPROGRESS:
    std::cout << "�u���b�L���O����̎��s���ł��邩�A�܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă��܂�\n";
    break;
  case WSAEPROCLIM:
    std::cout << "winsock�������ł���ő�v���Z�X���ɒB���܂���\n";
    break;
  case WSAEFAULT:
    std::cout << "�������ł���lpWSAData�͗L���ȃ|�C���^�ł͂���܂���\n";
    break;
  }
}