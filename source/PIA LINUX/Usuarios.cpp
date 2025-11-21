#include "Usuarios.h"
#include <fstream>
#include <sstream>
#include <iostream>
// Lee un archivo donde cada línea contiene: usuario contraseña
// y almacena esos pares dentro de un unordered_map
bool cargarUsuarios(const std::string& archivo, std::unordered_map<std::string, std::string>& usuarios) {
    std::ifstream infile(archivo); // Abre archivo para lectura
    if (!infile.is_open()) return false; // Retorna false si no se pudo abrir

    std::string linea;
    while (std::getline(infile, linea)) {  // Lee línea por línea
        std::istringstream iss(linea);     // Permite separar la línea en partes
        std::string usuario, password;
        if (!(iss >> usuario >> password)) continue;
        usuarios[usuario] = password;
    }
    return true;
}
// Guarda un token asociado a un usuario en un archivo.
// Formato guardado: usuario token
bool guardarToken(const std::string& archivo, const std::string& usuario, const std::string& token) {
    std::ofstream outfile(archivo, std::ios::app);
    if (!outfile.is_open()) return false;
    outfile << usuario << " " << token << "\n";
    return true;
}

