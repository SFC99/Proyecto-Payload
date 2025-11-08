# PIA — Tarea5: Autenticación JWT

## Objetivo general
Implementar un sistema de autenticación seguro mediante **JSON Web Tokens (JWT)**, transmitiendo información de sesión de manera verificada y sin persistencia en el backend.

## Plataforma objetivo
- Sistemas operativos: Windows / Linux  
- Arquitectura: x86_64 / amd64

/proyecto-jwt
│
├─ servidor_jwt.h # Funciones para JWT y gestión de usuarios
├─ servidor_jwt.cpp # Main del servidor
├─ cliente_jwt.h # Funciones cliente para login y validación
├─ cliente_jwt.cpp # Main del cliente Windows
├─ usuarios.txt # Lista de usuarios y contraseñas (usuario:password)
├─ tokens.txt # Tokens generados por el servidor (usuario:JWT)
└─ README.md # Este archivo

---

## ⚙️ Requisitos

- **Servidor Linux**:
  - Compilador C++17 (g++ o clang++)
  - [httplib.h](https://github.com/yhirose/cpp-httplib)
  - [jwt-cpp](https://github.com/Thalhammer/jwt-cpp)
  - [nlohmann/json](https://github.com/nlohmann/json)

- **Cliente Windows**:
  - Compilador C++17 (MSVC o MinGW)
  - Winsock2 para sockets TCP/IP
  - [nlohmann/json](https://github.com/nlohmann/json)

---

## 📝 Configuración

1. **Usuarios y contraseñas**  
   - Editar `usuarios.txt` en el servidor.  
   - Formato: `usuario:password`, un usuario por línea.  

   Ejemplo:


2. **Clave secreta JWT** 🔑  
- Por defecto está `clave_super_secreta` en el código.  
- Recomendado: cambiar por una cadena aleatoria segura.  
- Debe ser la misma para generación y validación de tokens.

3. **Issuer del JWT** 🏷️  
- Por defecto `"mi-servidor"`.  
- Puede cambiarse a cualquier string (ej: hostname), pero debe coincidir entre generación y validación.

---

## 🚀 Ejecución

### 🖥️ Servidor Linux

bash
g++ servidor_jwt.cpp -o servidor_jwt -std=c++17 -pthread
./servidor_jwt

El servidor escucha en http://0.0.0.0:8080.

Endpoints disponibles:
POST /login → recibe JSON { "usuario": "...", "password": "..." } y devuelve JWT.
POST /validate → recibe JSON { "token": "..." } y valida el JWT.
GET /protected → requiere header Authorization: Bearer <JWT>.

### 🖥️ Cliente Windows
g++ cliente_jwt.cpp -o cliente_jwt -std=c++17 -lws2_32
cliente_jwt.exe <IP_servidor> <puerto>


El cliente solicita usuario y contraseña, hace POST /login al servidor y recibe el JWT.

Luego puede usar /validate y /protected con ese JWT.


🔄 Ejemplo de flujo

Usuario admin se loguea desde cliente.
Cliente envía credenciales al servidor.
Servidor genera JWT y lo guarda en tokens.txt.
Cliente recibe JWT y lo usa en solicitudes protegidas.
Servidor valida el JWT y permite acceso a /protected si es válido.

🛡️ Seguridad

La contraseña no está hardcodeada en el código; se lee de usuarios.txt.
JWT asegura integridad y autenticidad: no es necesario mantener sesión en el servidor.
SECRET_KEY debe mantenerse confidencial.
Recomendado usar HTTPS en entornos de producción.

📌 Notas finales

Este sistema es útil para auditorías y pruebas de autenticación JWT.
Cumple con los objetivos de:
Transmisión segura de información de sesión 🔐
Validación de identidad sin almacenar sesiones persistentes ✅

Uso de endpoints /login, /validate, /protected 🔑

## Instrucciones para clonar el repositorio
```bash
git clone git@github.com:SFC99/Proyecto-Payload.git
cd 
