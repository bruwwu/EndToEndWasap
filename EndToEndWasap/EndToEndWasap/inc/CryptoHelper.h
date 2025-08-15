#pragma once
#include "Prerequisites.h"
#include "openssl\rsa.h"
#include "openssl\aes.h"

/**
 * @class CryptoHelper
 * @brief Clase que encapsula la lógica criptográfica para RSA y AES.
 *
 * Proporciona utilidades para:
 * - Generación de claves RSA.
 * - Intercambio seguro de claves AES.
 * - Cifrado y descifrado simétrico con AES-256 en modo CBC.
 * - Exportación e importación de claves públicas.
 */
class CryptoHelper {
public:
  /**
   * @brief Constructor que inicializa estructuras criptográficas.
   */
  CryptoHelper();

  /**
   * @brief Destructor que libera los recursos criptográficos utilizados.
   */
  ~CryptoHelper();

  /* ========================= RSA ========================= */

  /**
   * @brief Genera un nuevo par de claves RSA de 2048 bits.
   *
   * Este par de claves se almacena internamente en `rsaKeyPair`.
   */
  void GenerateRSAKeys();

  /**
   * @brief Devuelve la clave pública del usuario en formato PEM.
   * @return Cadena de texto que contiene la clave en formato PEM.
   */
  std::string GetPublicKeyString() const;

  /**
   * @brief Carga y almacena la clave pública del peer desde una cadena en formato PEM.
   * @param pemKey Clave pública en formato PEM.
   */
  void LoadPeerPublicKey(const std::string& pemKey);

  /* ========================= AES ========================= */

  /**
   * @brief Genera una clave AES-256 aleatoria (32 bytes).
   *
   * Esta clave se utilizará para el cifrado simétrico posterior.
   */
  void GenerateAESKey();

  /**
   * @brief Cifra la clave AES generada con la clave pública del peer usando RSA.
   * @return Vector de bytes que representa la clave AES cifrada.
   */
  std::vector<unsigned char> EncryptAESKeyWithPeer();

  /**
   * @brief Descifra la clave AES recibida cifrada con la clave pública del servidor.
   * @param encryptedKey Clave AES cifrada en forma de vector de bytes.
   */
  void DecryptAESKey(const std::vector<unsigned char>& encryptedKey);

  /**
   * @brief Cifra un mensaje utilizando AES-256 en modo CBC.
   *
   * @param plaintext Texto plano a cifrar.
   * @param outIV Vector donde se almacenará el IV generado aleatoriamente.
   * @return Vector de bytes con el mensaje cifrado.
   */
  std::vector<unsigned char> AESEncrypt(const std::string& plaintext, std::vector<unsigned char>& outIV);

  /**
   * @brief Descifra un mensaje previamente cifrado con AES-256-CBC.
   *
   * @param ciphertext Vector de bytes con el mensaje cifrado.
   * @param iv Vector con el IV utilizado durante el cifrado.
   * @return Cadena de texto descifrada.
   */
  std::string AESDecrypt(const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& iv);

private:
  RSA* rsaKeyPair;              ///< Par de claves RSA (privada y pública del cliente).
  RSA* peerPublicKey;           ///< Clave pública del servidor o peer.
  unsigned char aesKey[32];     ///< Clave AES de 256 bits (clave simétrica).
};
