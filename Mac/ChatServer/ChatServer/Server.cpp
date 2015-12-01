
#include "Server.hpp"


Server::Server() :
is_registered(false),
is_update_buf(false),
yes(1),
th_send(&Server::send, this),
th_recieve(&Server::receive, this)
{
  memset(&buf, 0, sizeof(buf));
}


void Server::send() {
  while(1) {
    if (!is_update_buf) continue;
    
    std::string str;
    
    // ログを更新した人以外にログを送信
    for (auto& member : members) {
      if (member.name == buf_name) continue;
      
      // ソケット作成
      member.sock = socket(AF_INET, SOCK_STREAM, 0);
      if (member.sock < 0) {
        perror("socket");
        exit(1);
      }
      
      // メンバーに接続要請
      connect(member.sock, (sockaddr*)&member.addr, sizeof(member.addr));
      
      str = member.name + ":" + buf.c_str();
      
      std::cout << str << std::endl;
      
      // バッファ送信
      write(member.sock, &str[0], str.size());
    }
  }
}

void Server::receive() {
  while(1) {
    Member m;
    m.sock = accept(sock, (sockaddr*)&m.addr, &m.len);
    if (m.sock < 0) {
      perror("accept");
      exit(1);
    }
  
    // 登録済みのメンバーか探す
    for (auto& member : members) {
      if (*inet_ntoa(m.addr.sin_addr) == *inet_ntoa(member.addr.sin_addr)) {
        is_registered = true;
        m.name = member.name.c_str();
      }
    }
  
    // 登録済みメンバーならログを残す
    if (is_registered) {
      m.buf.resize(BUFSIZ);
      read(m.sock, &m.buf[0], m.buf.size());
    
      // 発言をログに残す
      std::cout << m.name << ":" << m.buf.c_str() << std::endl;
      
      // 配信用バッファにログをコピー
      buf_name = m.name;
      buf = m.name + ":" + m.buf.c_str();
      
      close(m.sock);
    }
    else {
      // 新規メンバーなら登録
      m.buf.resize(BUFSIZ);
      read(m.sock, &m.buf[0], m.buf.size());
    
      m.name = m.buf.c_str();
      members.emplace_back(m);
    
      std::cout << m.name << "さんがログインしました" << std::endl;
    
      close(m.sock);
    }
  }
}

void Server::setup(const int port, const int backlog) {
  // ソケット作成
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("socket");
    exit(1);
  }
  
  // ポート・アドレスを設定
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_len = sizeof(addr);
  
  // 必ずbindできるように設定
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(yes));
  
  // ソケットとアドレスを紐ずける(bindする)
  int b = bind(sock, (sockaddr*)&addr, sizeof(addr));
  if (b != 0) {
    perror("bind");
    exit(1);
  }
  
  // クライアントから接続要求を待てる状態にする
  // 同時接続できる最大数を設定(?)
  listen(sock, backlog);
}

void Server::update() {
  th_recieve.join();
}

void Server::end() {
  members.clear();
  close(sock);
}