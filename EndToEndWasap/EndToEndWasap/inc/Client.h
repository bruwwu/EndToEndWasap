#pragma once
#include "NetworkHelper.h"
#include "CryptoHelper.h"
#include "Prerequisites.h"

class Client {
public: 
  Client() = default;
  Client(const std::string& serverIP, int port);
  ~Client();

  bool 
  Connect();
  
  void 
  SendEncryptedMessage(const std::string& message);
  
  void 
  ExchangeKeys();

  void
    SendAESKeyEncrypted();

private:
  std::string m_serverIP;
  int m_port;
  NetworkHelper m_net;
  CryptoHelper m_crypto;
  SOCKET m_serverSock;
};
