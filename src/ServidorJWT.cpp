#include "servidor_jwt.h"

int main() {
    Server svr;
    auto usuarios = cargarUsuarios();

    // ---------------------- /login ----------------------
    svr.Post("/login", [&](const Request& req, Response& res){
        try {
            auto body = json::parse(req.body);
            std::string usuario = body["usuario"];
            std::string password = body["password"];

            if(usuarios.count(usuario) && usuarios[usuario] == password){
                std::string token = generarJWT(usuario);
                guardarToken(usuario, token);

                json respuesta = {{"token", token}, {"mensaje", "Login exitoso"}};
                res.set_content(respuesta.dump(4), "application/json");
            } else {
                res.status = 401;
                res.set_content(json{{"error","Credenciales inválidas"}}.dump(4), "application/json");
            }
        } catch(...) {
            res.status = 400;
            res.set_content(json{{"error","JSON inválido"}}.dump(4), "application/json");
        }
    });

    // ---------------------- /validate ----------------------
    svr.Post("/validate", [&](const Request& req, Response& res){
        try {
            auto body = json::parse(req.body);
            std::string token = body["token"];
            std::string usuario;
            if(validarJWT(token, usuario)){
                res.set_content(json{{"valido",true},{"usuario",usuario}}.dump(4),"application/json");
            } else {
                res.status = 401;
                res.set_content(json{{"valido",false}}.dump(4),"application/json");
            }
        } catch(...) {
            res.status = 400;
            res.set_content(json{{"error","JSON inválido"}}.dump(4),"application/json");
        }
    });

    // ---------------------- /protected ----------------------
    svr.Get("/protected", [&](const Request& req, Response& res){
        if(!req.has_header("Authorization")){
            res.status = 401;
            res.set_content(json{{"error","Falta Authorization"}}.dump(4),"application/json");
            return;
        }
        std::string auth = req.get_header_value("Authorization");
        if(auth.rfind("Bearer ",0) != 0){
            res.status = 400;
            res.set_content(json{{"error","Formato inválido"}}.dump(4),"application/json");
            return;
        }
        std::string token = auth.substr(7);
        std::string usuario;
        if(validarJWT(token, usuario)){
            json respuesta = {{"usuario",usuario},{"mensaje","Acceso autorizado"}};
            res.set_content(respuesta.dump(4),"application/json");
        } else {
            res.status = 401;
            res.set_content(json{{"error","Token inválido o expirado"}}.dump(4),"application/json");
        }
    });

    std::cout << "Servidor JWT corriendo en http://localhost:8080\n";
    svr.listen("0.0.0.0",8080);
}
