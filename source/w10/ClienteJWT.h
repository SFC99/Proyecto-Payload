#pragma once
#include <string>

//-----------
// Realiza una petición al servidor para autenticar un usuario
// Parámetros:
//   - servidor: dirección IP o nombre del servidor
//   - puerto: puerto donde escucha el servidor
//   - usuario: nombre de usuario a autenticar
//   - password: contraseña del usuario
// Retorna:
//   - Un token JWT en forma de string si el login es exitoso
//   - Cadena vacía si la autenticación falla
std::string loginServidor(const std::string& servidor, int puerto,
                          const std::string& usuario, const std::string& password);

//-------------

//--------------
// Envía una solicitud al servidor para obtener información protegida
// usando un token JWT previamente obtenido
// Parámetros:
//   - servidor: dirección IP o nombre del servidor
//   - puerto: puerto donde escucha el servidor
//   - token: token JWT válido para autenticar la petición
// Retorna:
//   - El contenido devuelto por el servidor si la autenticación es válida
//   - Cadena vacía si el token es inválido o existe un error
std::string obtenerDatos(const std::string& servidor, int puerto, const std::string& token);
//---------------
