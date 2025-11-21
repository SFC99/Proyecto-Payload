#pragma once
#include <httplib.h>
#include <jwt-cpp/jwt.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace httplib;
using json = nlohmann::json;

const std::string SECRET_KEY = "clave_super_secreta"; // Clave para firmar JWT
const std::string USUARIOS_FILE = "usuarios.txt";
const std::string TOKENS_FILE   = "tokens.txt";

// Genera un JWT válido 5 minutos
std::string generarJWT(const std::string& usuario) {
    auto token = jwt::create()
        .set_issuer("mi-servidor")
        .set_subject(usuario)
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes{5})
        .sign(jwt::algorithm::hs256{SECRET_KEY});
    return token;
}

// Valida JWT
bool validarJWT(const std::string& token, std::string& usuario_out) {
    try {
        auto decoded = jwt::decode(token);
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{SECRET_KEY})
            .with_issuer("mi-servidor");
        verifier.verify(decoded);
        usuario_out = decoded.get_subject();
        return true;
    } catch (...) {
        return false;
    }
}

// Carga usuarios desde un txt (formato: usuario:password)
std::unordered_map<std::string,std::string> cargarUsuarios() {
    std::unordered_map<std::string,std::string> usuarios;
    std::ifstream file(USUARIOS_FILE);
    if (!file.is_open()) return usuarios;
    std::string linea;
    while (std::getline(file, linea)) {
        size_t sep = linea.find(':');
        if (sep != std::string::npos) {
            usuarios[linea.substr(0,sep)] = linea.substr(sep+1);
        }
    }
    return usuarios;
}

// Guarda token en txt (usuario:token)
void guardarToken(const std::string& usuario, const std::string& token) {
    std::ofstream file(TOKENS_FILE, std::ios::app);
    if(file.is_open()) file << usuario << ":" << token << "\n";
}

// Busca token en txt
bool obtenerToken(const std::string& usuario, std::string& token_out) {
    std::ifstream file(TOKENS_FILE);
    if (!file.is_open()) return false;
    std::string linea;
    while(std::getline(file,linea)) {
        size_t sep = linea.find(':');
        if (sep != std::string::npos) {
            std::string u = linea.substr(0,sep);
            if(u == usuario) {
                token_out = linea.substr(sep+1);
                return true;
            }
        }
    }
    return false;
}

