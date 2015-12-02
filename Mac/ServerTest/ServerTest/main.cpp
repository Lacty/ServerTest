
#include <iostream>
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int
main()
{
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  socklen_t len;
  int sock;
  
  std::string str;
  std::cin >> str;
  
  /* ソケットの作成 */
  sock0 = socket(AF_INET, SOCK_STREAM, 0);
  
  /* ソケットの設定 */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(23456);
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_len = sizeof(addr);
  
  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));
  
  /* TCPクライアントからの接続要求を待てる状態にする */
  listen(sock0, 5);
  
  /* TCPクライアントからの接続要求を受け付ける */
  len = sizeof(client);
  sock = accept(sock0, (struct sockaddr *)&client, &len);
  
  /* 5文字送信 */
  write(sock, str.c_str(), str.size());
  
  std::string bbb;
  bbb.resize(BUFSIZ);
  read(sock, &bbb[0], bbb.size());
  std::cout << bbb << std::endl;
  
  /* TCPセッションの終了 */
  close(sock);
  
  /* listen するsocketの終了 */
  close(sock0);
  
  return 0;
}
