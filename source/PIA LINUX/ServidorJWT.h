#pragma once
#include <string>
#include <unordered_map>

// Llave secreta utilizada para firmar y validar tokens JWT
// *** IMPORTANTE ***: en un servidor real esta clave nunca debe estar en texto plano
// ni dentro del código fuente
inline const std::string SECRET_KEY    = "clave_super_secreta";
inline const std::string USUARIOS_FILE = "usuarios.txt";
inline const std::string TOKENS_FILE   = "tokens.txt";
std::string generarJWT(const std::string &usuario);
bool validarJWT(const std::string &token, std::string &usuario_out);
// Carga usuarios desde un archivo de texto y los almacena en un mapa
std::unordered_map<std::string, std::string> cargarUsuarios();
//Escribe en el archivo de tokens un nuevo par usuario:token
void guardarToken(const std::string &usuario, const std::string &token);
// Busca en el archivo de tokens el token asociado a un usuario específico
bool obtenerToken(const std::string &usuario, std::string &token_out);

