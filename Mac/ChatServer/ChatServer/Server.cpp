
#include "Server.hpp"


Server::Server() :
is_registered(false),
is_update_buf(false),
yes(1),
log_num(0),
th_send(&Server::send, this),
th_recieve(&Server::receive, this) {}


void Server::send() {
  while(1) {
    if (!is_update_buf) continue;
    
    std::string str;
    
    // ログを更新した人以外にログを送信
    for (auto& member : members) {
      if (member.name == buf_name) continue;
    }
    is_update_buf = false;
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
    is_registered = false;
    for (auto& member : members) {
      if (inet_addr(&inet_ntoa(m.addr.sin_addr)[0]) ==
          inet_addr(&inet_ntoa(member.addr.sin_addr)[0]))
      {
        is_registered = true;
        m.name = member.name.c_str();
      }
    }
  
    // 登録済みメンバーならログを残す
    if (is_registered) {
      m.buf.resize(BUFSIZ);
      read(m.sock, &m.buf[0], m.buf.size());
    
      // 発言をログに残す
      std::cout << log_num << ">>" << m.name << ":" << m.buf.c_str() << std::endl;
      
      // 文字列分にリサイズ
      m.buf.resize(strlen(&m.buf[0]));
      
      // recvコマンドが送られたらログを送信
      if (m.buf == "recv") {
        for (auto& member : members) {
          if (inet_addr(&inet_ntoa(m.addr.sin_addr)[0]) ==
              inet_addr(&inet_ntoa(member.addr.sin_addr)[0]))
          {
            m.name = member.name.c_str();
            write(m.sock, &member.buf[0], strlen(&member.buf[0]));
            
            // ログを消去してメモリを再確保する
            member.buf.clear();
          }
        }
      }
      else {
        // 発言者以外のバッファにログを蓄積させる
        for (auto& member : members) {
          if (inet_addr(&inet_ntoa(m.addr.sin_addr)[0]) !=
              inet_addr(&inet_ntoa(member.addr.sin_addr)[0]))
          {
            member.buf += std::to_string(log_num) + ">>" + m.name + ":" + m.buf + "\n";
          }
        }
      }
      
      // ソケット封鎖
      close(m.sock);
    }
    else {
      // 新規メンバーなら登録
      m.buf.resize(BUFSIZ);
      read(m.sock, &m.buf[0], m.buf.size());
    
      // 名前登録とバッファ消去
      m.name = m.buf.c_str();
      m.buf.clear();
      members.emplace_back(m);
    
      std::cout << m.name << "さんがログインしました" << std::endl;
      close(m.sock);
    }
    
    log_num++;
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
  th_send.join();
}

void Server::end() {
  members.clear();
  close(sock);
}