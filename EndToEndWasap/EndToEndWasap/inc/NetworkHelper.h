#pragma once
#include "Prerequisites.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

/**
 * @class NetworkHelper
 * @brief Clase auxiliar para manejar operaciones de red usando sockets TCP en Windows.
 *
 * Proporciona funcionalidad para crear sockets de servidor y cliente,
 * así como para enviar y recibir datos en formatos de texto y binarios.
 */
class NetworkHelper {
public:
  /**
   * @brief Constructor. Inicializa Winsock si es necesario.
   */
  NetworkHelper();

  /**
   * @brief Destructor. Libera los recursos de Winsock si están en uso.
   */
  ~NetworkHelper();

  /* ================== FUNCIONES PARA SERVIDOR ================== */

  /**
   * @brief Inicia un socket servidor en el puerto indicado y lo deja en modo escucha.
   * @param port Puerto TCP donde se aceptarán conexiones.
   * @return true si el servidor se inicializó correctamente.
   * @return false en caso de error.
   */
  bool StartServer(int port);

  /**
   * @brief Espera y acepta una conexión entrante de un cliente.
   * @return SOCKET válido del cliente, o INVALID_SOCKET si falla.
   */
  SOCKET AcceptClient();

  /* ================== FUNCIONES PARA CLIENTE ================== */

  /**
   * @brief Establece una conexión con un servidor especificando IP y puerto.
   * @param ip Dirección IP del servidor (ej. "127.0.0.1").
   * @param port Puerto del servidor.
   * @return true si se conecta exitosamente.
   * @return false en caso de fallo.
   */
  bool ConnectToServer(const std::string& ip, int port);

  /* ================== ENVÍO DE DATOS ================== */

  /**
   * @brief Envía una cadena de texto al socket indicado.
   * @param socket Socket válido.
   * @param data Cadena de texto a enviar.
   * @return true si se envió correctamente.
   */
  bool SendData(SOCKET socket, const std::string& data);

  /**
   * @brief Envía datos binarios al socket (ej. clave AES o mensaje cifrado).
   * @param socket Socket válido.
   * @param data Vector de bytes a enviar.
   * @return true si se envió correctamente.
   */
  bool SendData(SOCKET socket, const std::vector<unsigned char>& data);

  /* ================== RECEPCIÓN DE DATOS ================== */

  /**
   * @brief Recibe una cadena de texto desde el socket.
   * @param socket Socket válido.
   * @return Cadena recibida. Vacía si ocurre un error.
   */
  std::string ReceiveData(SOCKET socket);

  /**
   * @brief Recibe datos binarios del socket.
   * @param socket Socket válido.
   * @param size Tamaño de los datos esperados (0 para recibir toda la data disponible).
   * @return Vector de bytes con los datos recibidos.
   */
  std::vector<unsigned char> ReceiveDataBinary(SOCKET socket, int size = 0);

  /* ================== UTILIDADES ================== */

  /**
   * @brief Cierra el socket especificado.
   * @param socket Socket que se desea cerrar.
   */
  void close(SOCKET socket);

  /**
   * @brief Envía todos los bytes del buffer, incluso si se necesitan múltiples envíos.
   * @param s Socket válido.
   * @param data Puntero al buffer de datos.
   * @param len Longitud total de datos a enviar.
   * @return true si se enviaron todos los datos correctamente.
   */
  bool SendAll(SOCKET s, const unsigned char* data, int len);

  /**
   * @brief Recibe exactamente 'len' bytes del socket, bloqueando si es necesario.
   * @param s Socket válido.
   * @param out Puntero al buffer donde se almacenarán los datos.
   * @param len Número de bytes a recibir.
   * @return true si se recibieron todos los datos correctamente.
   */
  bool ReceiveExact(SOCKET s, unsigned char* out, int len);

public:
  SOCKET m_serverSocket = -1; ///< Socket principal del servidor.
private:
  bool m_initialized = false; ///< Indica si Winsock fue inicializado.
};
