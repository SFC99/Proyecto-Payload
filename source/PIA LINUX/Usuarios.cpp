#include "Usuarios.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool cargarUsuarios(const std::string& archivo, std::unordered_map<std::string, std::string>& usuarios) {
    std::ifstream infile(archivo);
    if (!infile.is_open()) return false;

    std::string linea;
    while (std::getline(infile, linea)) {
        std::istringstream iss(linea);
        std::string usuario, password;
        if (!(iss >> usuario >> password)) continue;
        usuarios[usuario] = password;
    }
    return true;
}

bool guardarToken(const std::string& archivo, const std::string& usuario, const std::string& token) {
    std::ofstream outfile(archivo, std::ios::app);
    if (!outfile.is_open()) return false;
    outfile << usuario << " " << token << "\n";
    return true;
}
