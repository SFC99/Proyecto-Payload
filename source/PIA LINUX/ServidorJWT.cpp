#include "ServidorJWT.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <jwt-cpp/jwt.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;
static std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}
std::string generarJWT(const std::string &usuario) {
    auto token = jwt::create()
        .set_issuer("mi-servidor")
        .set_subject(usuario)
        .set_issued_at(std::chrono::system_clock::now())
        .set_expires_at(std::chrono::system_clock::now() +
                        std::chrono::minutes(5))
        .sign(jwt::algorithm::hs256{SECRET_KEY});
    return token;
}
bool validarJWT(const std::string &token, std::string &usuario_out) {
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
std::unordered_map<std::string, std::string> cargarUsuarios() {
    std::unordered_map<std::string, std::string> usuarios;
    std::ifstream file(USUARIOS_FILE);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir " << USUARIOS_FILE << std::endl;
        return usuarios;
    }
    std::string linea;
    while (std::getline(file, linea)) {
        linea = trim(linea);
        if (linea.empty()) continue;
        size_t sep = linea.find(':');
        if (sep == std::string::npos) continue;
        std::string u = trim(linea.substr(0, sep));
        std::string p = trim(linea.substr(sep + 1));
        if (!u.empty()) {
            usuarios[u] = p;
        }
    }
    return usuarios;
}
void guardarToken(const std::string &usuario, const std::string &token) {
    std::ofstream file(TOKENS_FILE, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir " << TOKENS_FILE << " para escritura\n";
        return;
    }
    file << usuario << ":" << token << "\n";
}

bool obtenerToken(const std::string &usuario, std::string &token_out) {
    std::ifstream file(TOKENS_FILE);
    if (!file.is_open()) return false;

    std::string linea;
    while (std::getline(file, linea)) {
        linea = trim(linea);
        if (linea.empty()) continue;

        size_t sep = linea.find(':');
        if (sep == std::string::npos) continue;

        std::string u = trim(linea.substr(0, sep));
        std::string t = trim(linea.substr(sep + 1));

        if (u == usuario) {
            token_out = t;
            return true;
        }
    }
    return false;
}

