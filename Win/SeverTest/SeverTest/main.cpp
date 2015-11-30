
//
// 簡単なTPCサーバ
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

  std::string str = "教室あつい";

  // winsock2の初期化
  int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
  if (err != 0) return -1;

  // ソケットの作成
  sock0 = socket(AF_INET, SOCK_STREAM, 0);
  if (sock0 == INVALID_SOCKET) return -1;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(73591);
  addr.sin_addr.S_un.S_addr = INADDR_ANY;
  bind(sock0, (sockaddr*)&addr, sizeof(addr));

  // TPCクライアントから接続要求を待てる状態にする
  listen(sock0, 5);

  // TPCクライアントからの接続要求を受け取る
  len = sizeof(client);
  sock = accept(sock0, (sockaddr*)&client, &len);

  // 5文字送信
  send(sock, str.c_str(), str.size(), 0);

  // TCPセッション終了
  closesocket(sock);

  // winsock2の終了処理
  WSACleanup();

  return 0;
}