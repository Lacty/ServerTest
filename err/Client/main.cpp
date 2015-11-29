
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
    std::cout << "ネットワークサブシステムがネットワークへの接続を準備できません\n";
    break;
  case WSAVERNOTSUPPORTED:
    std::cout << "要求されたwinsockのバージョンがサポートされていません\n";
    break;
  case WSAEINPROGRESS:
    std::cout << "ブロッキング操作の実行中であるか、またはサービスプロバイダがコールバック関数を処理しています\n";
    break;
  case WSAEPROCLIM:
    std::cout << "winsockが処理できる最大プロセス数に達しました\n";
    break;
  case WSAEFAULT:
    std::cout << "第二引数であるlpWSADataは有効なポインタではありません\n";
    break;
  }
}