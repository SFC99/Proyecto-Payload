// Incluye la definición del servidor y constantes como SECRET_KEY, USUARIOS_FILE, TOKENS_FILE
#include "ServidorJWT.h"

// Librerías estándar para archivos, entrada/salida, tiempo y JWT
#include <fstream>
#include <iostream>
#include <chrono>
#include <jwt-cpp/jwt.h>
#include <nlohmann/json.hpp>

// Alias para usar JSON
using json = nlohmann::json;
using namespace std;


// Función auxiliar para eliminar espacios al inicio y final de una cadena
static std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");  
    if (start == std::string::npos) return "";        // Si no encuentra caracteres válidos, retorna cadena vacía

    size_t end = s.find_last_not_of(" \t\r\n");       
    return s.substr(start, end - start + 1);          // Retorna la parte sin espacios
}


// Genera un token JWT para un usuario específico
std::string generarJWT(const std::string &usuario) {
    auto token = jwt::create()
        .set_issuer("mi-servidor")                                          // Quién emite el token
        .set_subject(usuario)                                               // Usuario dueño del token
        .set_issued_at(std::chrono::system_clock::now())                    // Fecha de creación
        .set_expires_at(std::chrono::system_clock::now() +                 
                        std::chrono::minutes(5))                            // Expira en 5 minutos
        .sign(jwt::algorithm::hs256{SECRET_KEY});                           // Firma con llave secreta

    return token;
}


// Valida un token JWT y extrae el usuario si es válido
bool validarJWT(const std::string &token, std::string &usuario_out) {
    try {
        auto decoded = jwt::decode(token);                                  // Decodifica sin verificar
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{SECRET_KEY})             // Algoritmo permitido
            .with_issuer("mi-servidor");                                    // Emisor esperado

        verifier.verify(decoded);                                           // Verifica firma y contenido

        usuario_out = decoded.get_subject();                                // Obtiene el usuario del token
        return true;
    } catch (...) {                                                         // Si falla, token no válido
        return false;
    }
}


// Carga usuarios desde un archivo (formato: usuario:password)
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

        size_t sep = linea.find(':');                                       // Busca separador
        if (sep == std::string::npos) continue;

        std::string u = trim(linea.substr(0, sep));                         // Usuario
        std::string p = trim(linea.substr(sep + 1));                        // Contraseña

        if (!u.empty()) {
            usuarios[u] = p;                                                // Agrega al mapa
        }
    }

    return usuarios;
}


// Guarda un token emitido en un archivo (usuario:token)
void guardarToken(const std::string &usuario, const std::string &token) {
    std::ofstream file(TOKENS_FILE, std::ios::app);                         // Modo añadir

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir " << TOKENS_FILE << " para escritura\n";
        return;
    }

    file << usuario << ":" << token << "\n";                                 // Escribe entrada
}


// Busca un token asociado a un usuario en el archivo de tokens
bool obtenerToken(const std::string &usuario, std::string &token_out) {
    std::ifstream file(TOKENS_FILE);
    if (!file.is_open()) return false;

    std::string linea;
    while (std::getline(file, linea)) {
        linea = trim(linea);
        if (linea.empty()) continue;

        size_t sep = linea.find(':');
        if (sep == std::string::npos) continue;

        std::string u = trim(linea.substr(0, sep));                         // Usuario
        std::string t = trim(linea.substr(sep + 1));                        // Token almacenado

        if (u == usuario) {                                                 // Coincidencia
            token_out = t;
            return true;
        }
    }

    return false;                                                           // No encontrado
}
