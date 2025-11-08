#include "ClienteJWT.h"
#include <iostream>
#include <string>

int main() {
    std::string servidor;
    int puerto;
    std::cout << "IP del servidor: "; std::cin >> servidor;
    std::cout << "Puerto del servidor: "; std::cin >> puerto;

    std::string usuario, password;
    std::cout << "Usuario: "; std::cin >> usuario;
    std::cout << "Contraseña: "; std::cin >> password;

    std::string token = loginServidor(servidor, puerto, usuario, password);
    if(token.empty()) return 1;

    std::cout << "JWT recibido: " << token << "\n";

    std::string datos = obtenerDatos(servidor, puerto, token);
    if(datos.empty()) std::cerr << "No se pudieron obtener datos\n";
    else std::cout << "Datos protegidos:\n" << datos << "\n";

    return 0;
}
