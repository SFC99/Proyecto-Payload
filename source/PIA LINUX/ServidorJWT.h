#pragma once
#include <string>
#include <unordered_map>
inline const std::string SECRET_KEY    = "clave_super_secreta";
inline const std::string USUARIOS_FILE = "usuarios.txt";
inline const std::string TOKENS_FILE   = "tokens.txt";
std::string generarJWT(const std::string &usuario);
bool validarJWT(const std::string &token, std::string &usuario_out);
std::unordered_map<std::string, std::string> cargarUsuarios();
void guardarToken(const std::string &usuario, const std::string &token);
bool obtenerToken(const std::string &usuario, std::string &token_out);
