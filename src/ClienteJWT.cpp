#include "ClienteJWT.h"
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>

using namespace httplib;
using json = nlohmann::json;

std::string loginServidor(const std::string& servidor, int puerto,
                          const std::string& usuario, const std::string& password) {
    Client cli(servidor, puerto);
    json credenciales = {{"usuario",usuario},{"password",password}};
    auto res = cli.Post("/login", credenciales.dump(), "application/json");
    if (!res || res->status!=200) {
        std::cerr << "Login fallido\n";
        return "";
    }
    json respuesta = json::parse(res->body);
    return respuesta["token"];
}

std::string obtenerDatos(const std::string& servidor, int puerto, const std::string& token) {
    Client cli(servidor, puerto);
    Headers headers = {{"Authorization","Bearer "+token}};
    auto res = cli.Get("/datos", headers);
    if (!res || res->status!=200) {
        return "";
    }
    return res->body;
}
