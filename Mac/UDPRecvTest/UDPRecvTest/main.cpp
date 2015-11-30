
#include <iostream>

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>


int main() {
  int sock;
  sockaddr_in addr;
  
  char buf[2048];
  
  // ソケット作成
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("socket");
    exit(1);
  }
  
  // bindするIPアドレスとポートを設定
  addr.sin_family = AF_INET;
  addr.sin_port = htons(93571);
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_len = sizeof(addr);
  
  // ソケットに名前をつける(bindする)
  int n = bind(sock, (sockaddr*)&addr, sizeof(addr));
  if (n != 0) {
    perror("bind");
    exit(1);
  }
  
  // データを受信
  memset(buf, 0, sizeof(buf));
  recv(sock, buf, sizeof(buf), 0);
  
  // 受信したデータを出力
  printf("%s\n", buf);
  
  // ソケット封鎖
  close(sock);

  return 0;
}
