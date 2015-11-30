
//
// 簡単なTCPクライアント
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

  // winsock2の初期化
  int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
  if (err != 0) return -1;

  // ソケットの作成
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET) return -1;

  // 接続先指定用構造体を準備
  server.sin_family = AF_INET;
  server.sin_port = htons(12345);
  server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

  // サーバーに接続
  connect(sock, (sockaddr*)&server, sizeof(server));

  // サーバーからデータを受信
  memset(buf, 0, sizeof(buf));
  int n = recv(sock, buf, sizeof(buf), 0);

  printf("%d, %s\n", n, buf);

  // winsock2の終了処理
  WSACleanup();

  return 0;
}