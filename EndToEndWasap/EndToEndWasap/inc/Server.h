#pragma once
#include "NetworkHelper.h"
#include "CryptoHelper.h"
#include "Prerequisites.h"

/**
 * @class Server
 * @brief Clase encargada de gestionar la lógica del servidor en una comunicación segura.
 *
 * Administra la conexión entrante de un cliente, el intercambio de claves públicas RSA,
 * la recepción de una clave AES cifrada, y la comunicación cifrada mediante AES-CBC.
 */
class Server {
public:
  /**
   * @brief Constructor por defecto. No inicializa el servidor.
   */
  Server() = default;

  /**
   * @brief Constructor con parámetro de puerto. Genera claves RSA automáticamente.
   * @param port Puerto en el cual el servidor escuchará conexiones.
   */
  Server(int port);

  /**
   * @brief Destructor. Cierra el socket del cliente si está activo.
   */
  ~Server();

  /**
   * @brief Inicia el servidor en el puerto especificado.
   * @return true si se inicializó correctamente.
   * @return false si ocurrió algún error.
   */
  bool Start();

  /**
   * @brief Espera una conexión entrante y realiza el intercambio de claves RSA + AES.
   *
   * Proceso:
   * 1. Enviar clave pública del servidor.
   * 2. Recibir clave pública del cliente.
   * 3. Recibir clave AES cifrada con la clave pública del servidor.
   */
  void WaitForClient();

  /**
   * @brief Recibe un mensaje cifrado usando AES y lo descifra para mostrarlo.
   *
   * Espera un vector de inicialización (IV) seguido del mensaje cifrado.
   */
  void ReceiveEncryptedMessage();

  /**
   * @brief Bucle continuo para recibir mensajes cifrados del cliente.
   *
   * Este método se puede ejecutar en un hilo separado.
   */
  void StartReceiveLoop();

  /**
   * @brief Bucle para enviar mensajes desde consola cifrados al cliente.
   *
   * Utiliza la clave AES previamente intercambiada y AES-CBC como algoritmo de cifrado.
   */
  void SendEncryptedMessageLoop();

  /**
   * @brief Inicia el chat interactivo con el cliente.
   *
   * Combina `StartReceiveLoop` en un hilo paralelo y `SendEncryptedMessageLoop` en el hilo principal.
   */
  void StartChatLoop();

private:
  int m_port;                          ///< Puerto en el que el servidor escucha.
  SOCKET m_clientSock;                ///< Socket del cliente conectado.
  NetworkHelper m_net;                ///< Ayudante para operaciones de red.
  CryptoHelper m_crypto;              ///< Ayudante para operaciones criptográficas.
  std::thread m_rxThread;             ///< Hilo encargado de recibir mensajes.
  std::atomic<bool> m_running{ false }; ///< Indica si el servidor está activo.
};
