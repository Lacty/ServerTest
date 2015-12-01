
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>  // inet_addr()


int main() {
  int sock;
  sockaddr_in addr;
  
  // ソケット作成
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("socket");
    exit(1);
  }
  
  // 接続先指定用構造体の準備
  addr.sin_family = AF_INET;
  addr.sin_port = htons(93571);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  // 指定した接続先にデータを送信
  size_t n = sendto(sock, "Hello", 5, 0, (sockaddr*)&addr, sizeof(addr));
  if (int(n) < 1) {
    perror("sendto");
    exit(1);
  }
  
  // ソケット封鎖
  close(sock);
  
  return 0;
}
