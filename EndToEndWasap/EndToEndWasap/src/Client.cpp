#include "Client.h"

Client::Client(const std::string& ip, int port) :
  m_serverIP(ip), m_port(port), m_serverSock(INVALID_SOCKET) {

  m_crypto.GenerateRSAKeys();
  m_crypto.GenerateAESKey();
}

Client::~Client() {
  if (m_serverSock != INVALID_SOCKET) {
    m_net.close(m_serverSock);
  }
}

bool
Client::Connect() {
  std::cout << "[Client] Connecting to server at " << m_serverIP << ":" << m_port << std::endl;
  bool connected = m_net.ConnectToServer(m_serverIP, m_port);

  if (connected) {
    m_serverSock = m_net.m_serverSocket;
    std::cout << "[Client] Connected to server." << std::endl;
  }
  else {
    std::cerr << "[Client] Failed to connect to server." << std::endl;
  }
  return connected;
}

void
Client::ExchangeKeys() {
  std::string serverPublicKey = m_net.ReceiveData(m_serverSock);
  m_crypto.LoadPeerPublicKey(serverPublicKey);
  std::cout << "[Client] Received server public key." << std::endl;

  std::string clientPublicKey = m_crypto.GetPublicKeyString();
  m_net.SendData(m_serverSock, clientPublicKey);
  std::cout << "[Client] Sent client public key." << std::endl;
}

void 
Client::SendAESKeyEncrypted() {
  std::vector<unsigned char> encryptedAESKey = m_crypto.EncryptAESKeyWithPeer();
  m_net.SendData(m_serverSock, encryptedAESKey);
  std::cout << "[Client] Sent encrypted AES key." << std::endl;
}

void 
Client::SendEncryptedMessage(const std::string& message) {
  std::vector<unsigned char> iv;
  std::vector<unsigned char> encryptedMsg = m_crypto.AESEncrypt(message, iv);

  m_net.SendData(m_serverSock, iv);
  m_net.SendData(m_serverSock, encryptedMsg);
  std::cout << "[Client] Sent encrypted message: " << message << std::endl;
}