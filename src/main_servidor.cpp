#include "ServidorJWT.h"
#include "Usuarios.h"
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <iostream>

using json = nlohmann::json;
using namespace httplib;

int main() {
    std::unordered_map<std::string, std::string> usuarios;
    if (!cargarUsuarios("usuarios.txt", usuarios)) {
        std::cerr << "Error cargando usuarios.txt\n";
        return 1;
    }

    Server svr;

    // Endpoint /login
    svr.Post("/login", [&](const Request& req, Response& res) {
        try {
            json body = json::parse(req.body);
            std::string usuario = body["usuario"];
            std::string password = body["password"];

            if (usuarios.count(usuario) && usuarios[usuario] == password) {
                std::string token = generarJWT(usuario, SECRET_KEY);
                guardarToken("tokens.txt", usuario, token);

                json respuesta = {{"token", token}, {"mensaje", "Login exitoso"}};
                res.set_content(respuesta.dump(4), "application/json");
            } else {
                res.status = 401;
                res.set_content(json{{"error","Credenciales inválidas"}}.dump(4), "application/json");
            }
        } catch (...) {
            res.status = 400;
            res.set_content(json{{"error","JSON inválido"}}.dump(4), "application/json");
        }
    });

    // Endpoint /datos protegido
    svr.Get("/datos", [&](const Request& req, Response& res) {
        if (!req.has_header("Authorization")) {
            res.status = 401;
            res.set_content(json{{"error","Falta cabecera Authorization"}}.dump(4), "application/json");
            return;
        }

        std::string auth = req.get_header_value("Authorization");
        if (auth.rfind("Bearer ",0)!=0) {
            res.status = 400;
            res.set_content(json{{"error","Formato de token inválido"}}.dump(4), "application/json");
            return;
        }

        std::string token = auth.substr(7);
        std::string usuario;

        if (validarJWT(token, SECRET_KEY, usuario)) {
            json respuesta = {{"usuario", usuario}, {"mensaje","Acceso autorizado"}};
            res.set_content(respuesta.dump(4), "application/json");
        } else {
            res.status = 401;
            res.set_content(json{{"error","Token inválido o expirado"}}.dump(4), "application/json");
        }
    });

    std::cout << "Servidor corriendo en http://localhost:8080\n";
    svr.listen("0.0.0.0",8080);
}
