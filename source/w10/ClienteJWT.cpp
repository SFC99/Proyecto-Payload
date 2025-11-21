#include "ClienteJWT.h" // Definición del cliente JWT (funciones auxiliares)
#include "httplib.h" // Biblioteca httplib para realizar peticiones HTTP
#include "json.hpp" // Biblioteca JSON para manejar datos en formato JSON
#include <iostream> // Entrada/salida estándar

using namespace httplib;
using json = nlohmann::json; // Alias para manejar JSON

//------
// Realiza un login en el servidor enviando usuario y contraseña.
// Si el login es exitoso, devuelve el token recibido
std::string loginServidor(const std::string& servidor, int puerto,
                          const std::string& usuario, const std::string& password) {
    Client cli(servidor, puerto);
    json credenciales = {{"usuario",usuario},{"password",password}};
    auto res = cli.Post("/login", credenciales.dump(), "application/json");
    if (!res || res->status!=200) {
        std::cerr << "Login fallido\n"; // Error de autenticación
        return "";
    }
    json respuesta = json::parse(res->body);
    return respuesta["token"]; // Devuelve el token JWT
}
//------

//------
// Realiza una petición GET al servidor para obtener datos protegidos.
// Se envía el token en la cabecera Authorization.
// Si tiene éxito, devuelve el cuerpo de la respuesta.
std::string obtenerDatos(const std::string& servidor, int puerto, const std::string& token) {
    Client cli(servidor, puerto);
    Headers headers = {{"Authorization","Bearer "+token}};
    auto res = cli.Get("/datos", headers);
    if (!res || res->status!=200) {
        return "";
    }
    return res->body;
}
//--------
