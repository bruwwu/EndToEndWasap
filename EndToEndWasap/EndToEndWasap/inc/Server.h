#pragma once
#include "NetworkHelper.h"
#include "CryptoHelper.h"
#include "Prerequisites.h"
class
	Server {
public:
	Server() = default;
	Server(int port);

	~Server();

	bool Start();
	void WaitForClient();
  void ReciveEncryptedMessage();

private:
	int m_port;
  int m_clientSocket;
	NetworkHelper m_net;
  CryptoHelper m_crypto;

};