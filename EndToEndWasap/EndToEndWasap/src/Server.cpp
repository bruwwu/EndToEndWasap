#include "Server.h"

Server::Server(int port) : m_port(port), m_clientSocket(-1) {
  m_crypto.GenerateRSAKeys();
}

Server::~Server() {
  if (m_clientSocket != 1) {
    m_net.close(m_clientSocket);
  }
}

bool Server::Start() {
  std::cout << "Starting server on port " << m_port << std::endl;
  return m_net.StartServer(m_port);
}

void Server::WaitForClient() {
  std::cout << "[Server] Waiting for client to connect...\n";

  m_clientSocket = m_net.AcceptClient();
  if (m_clientSocket == INVALID_SOCKET) {
    std::cerr << "[Server] Failed to accept client connection.\n";
    return;
  }
  std::cout << "[Server] Client connected. \n";

  std::string serverPublicKey = m_crypto.GetPublicKeyString();
  m_net.SendData(m_clientSocket, serverPublicKey);

  std::string clientPublicKey = m_net.ReceiveData(m_clientSocket);
  m_crypto.LoadPeerPublicKey(clientPublicKey);

  std::vector<unsigned char> encryptedAESKey = m_net.ReceiveDataBinary(m_clientSocket, 256);
  m_crypto.DecryptAESKey(encryptedAESKey);

  std::cout << "[Server] AES key decrypted successfully.\n";
}

void Server::ReciveEncryptedMessage() {
  std::vector<unsigned char> iv = m_net.ReceiveDataBinary(m_clientSocket, 16);
  std::vector<unsigned char> encryptedMessage = m_net.ReceiveDataBinary(m_clientSocket, 128);
  std::string msg = m_crypto.AESDecrypt(encryptedMessage, iv);
  std::cout << "[Server] Received encrypted message: " << msg << std::endl;
}