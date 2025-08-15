#pragma once
#include "NetworkHelper.h"
#include "CryptoHelper.h"
#include "Prerequisites.h"

/**
 * @class Client
 * @brief Clase que representa un cliente que se conecta a un servidor para intercambiar mensajes cifrados.
 *
 * Esta clase gestiona la conexión de red, el intercambio de claves RSA y el cifrado/descifrado
 * de mensajes mediante AES. Utiliza `NetworkHelper` para la comunicación y `CryptoHelper`
 * para las operaciones criptográficas.
 */
class Client {
public:
	/**
	 * @brief Constructor por defecto.
	 */
	Client() = default;

	/**
	 * @brief Constructor con IP y puerto del servidor.
	 * @param ip Dirección IP del servidor.
	 * @param port Puerto del servidor.
	 */
	Client(const std::string& ip, int port);

	/**
	 * @brief Destructor. Cierra la conexión si está activa.
	 */
	~Client();

	/**
	 * @brief Establece conexión con el servidor.
	 * @return true si la conexión fue exitosa.
	 * @return false si ocurrió un error.
	 */
	bool Connect();

	/**
	 * @brief Intercambia claves públicas con el servidor.
	 *
	 * Envía la clave pública del cliente y recibe la clave pública del servidor.
	 */
	void ExchangeKeys();

	/**
	 * @brief Cifra la clave AES con la pública del servidor y la envía.
	 *
	 * Este paso es necesario para establecer un canal seguro simétrico.
	 */
	void SendAESKeyEncrypted();

	/**
	 * @brief Cifra un mensaje con AES y lo envía al servidor.
	 * @param message Texto plano que se desea cifrar y enviar.
	 */
	void SendEncryptedMessage(const std::string& message);

	/**
	 * @brief Inicia un bucle para enviar múltiples mensajes cifrados.
	 *
	 * El usuario puede escribir mensajes en consola hasta enviar "/exit".
	 */
	void SendEncryptedMessageLoop();

	/**
	 * @brief Inicia el bucle de comunicación segura con el servidor.
	 *
	 * Lanza un hilo para recibir mensajes mientras permite enviar mensajes desde la consola.
	 */
	void StartChatLoop();

	/**
	 * @brief Bucle de recepción continua de mensajes cifrados desde el servidor.
	 *
	 * Descifra y muestra los mensajes recibidos.
	 */
	void StartReceiveLoop();

private:
	std::string m_ip;         ///< Dirección IP del servidor.
	int m_port;               ///< Puerto del servidor.
	SOCKET m_serverSock;      ///< Socket conectado al servidor.
	NetworkHelper m_net;      ///< Ayudante para comunicación por red.
	CryptoHelper m_crypto;    ///< Ayudante para operaciones criptográficas.
};
