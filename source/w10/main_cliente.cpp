#include "ClienteJWT.h" // Declaración de las funciones loginServidor y obtenerDatos
#include <iostream>
#include <string>

int main() {
    std::string servidor;
    int puerto;
    // Solicita al usuario la IP o dominio del servidor
    std::cout << "IP del servidor: "; std::cin >> servidor;
    // Solicita el puerto donde escucha el servidor
    std::cout << "Puerto del servidor: "; std::cin >> puerto;

    std::string usuario, password;
    std::cout << "Usuario: "; std::cin >> usuario;
    std::cout << "Contraseña: "; std::cin >> password;
    // Llama al servidor para autenticar y obtener un token JWT
    std::string token = loginServidor(servidor, puerto, usuario, password);
    if(token.empty()) return 1;

    std::cout << "JWT recibido: " << token << "\n";
    // Solicita datos protegidos utilizando el token
    std::string datos = obtenerDatos(servidor, puerto, token);
    if(datos.empty()) std::cerr << "No se pudieron obtener datos\n";
    else std::cout << "Datos protegidos:\n" << datos << "\n";

    return 0;
}

