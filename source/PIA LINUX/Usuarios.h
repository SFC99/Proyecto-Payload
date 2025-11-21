#pragma once
#include <string>
#include <unordered_map>
// Lee un archivo donde cada línea contiene un usuario y una contraseña.
// Almacena los pares usuario : contraseña en un unordered_map
bool cargarUsuarios(const std::string& archivo, std::unordered_map<std::string, std::string>& usuarios);
// Guarda un token asociado a un usuario en un archivo.
// Formato guardado: usuario+token
bool guardarToken(const std::string& archivo, const std::string& usuario, const std::string& token);

