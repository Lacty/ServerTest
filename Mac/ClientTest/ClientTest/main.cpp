
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


in_addr_t toInAddrT(char* addr) {
  return in_addr_t((unsigned long)addr);
}

int
main()
{
  struct sockaddr_in server;
  int sock;
  char buf[32];
  ssize_t n;
  int port = 73591;
  char address[] = "192.168.10.140";
  
  /* ソケットの作成 */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  
  /* 接続先指定用構造体の準備 */
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(address);
  
  /* サーバに接続 */
  connect(sock, (struct sockaddr *)&server, sizeof(server));
  
  /* サーバからデータを受信 */
  memset(buf, 0, sizeof(buf));
  n = read(sock, buf, sizeof(buf));
  
  printf("%d, %s\n", int(n), buf);
  
  /* socketの終了 */
  close(sock);
  
  return 0;
}