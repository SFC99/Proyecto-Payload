
# 2do avance PIA

Este avance corresponde a los commit con hash `666a8d5`, `17c1f33` y `fcc2949`  y están relacionados con el tag `tare6-avance`.


# 3er Avance PIA — Borrador del Reporte Técnico
Este avance corresponde a los commit con hash ``, `` y ``  y están relacionados con el tag `3er-avance`.

**Proyecto:** Payload benigno de autenticación JWT  

**Integrantes:**

- Angel David Morales Palomo
- Juan Angel Rodriguez Bulnes
- Sofía Martínez Cisneros 


## 1. Resumen ejecutivo
Este proyecto implementa un payload benigno basado en un sistema completo de autenticación mediante JSON Web Tokens (JWT), compuesto por un servidor en C++ que gestiona credenciales y tokens, y un cliente que envía solicitudes de login, validación y acceso a rutas protegidas. El objetivo es demostrar un flujo realista de autenticación sin mantener sesiones persistentes y analizar técnica y éticamente su funcionamiento mediante pruebas controladas en un entorno aislado.


## 2. Descripción del payload y límites éticos
El payload consiste en un servidor JWT escrito en C++ que:
- recibe credenciales vía HTTP,
- valida usuario y contraseña desde `usuarios.txt`,
- genera un JWT firmado,
- guarda el token en `tokens.txt`,
- expone endpoints `/login`, `/validate` y `/protected`.

El cliente, también en C++, envía solicitudes HTTP y procesa las respuestas.

**Límites éticos aplicados:**
- El payload es 100% benigno: no ejecuta acciones maliciosas ni intenta evadir seguridad.
- Se utilizó únicamente en una VM aislada para evitar afectar sistemas reales.
- Las pruebas se limitaron a credenciales controladas y tráfico local.
- El alcance se mantuvo conforme a ETHICS.md previamente definido.


## 3. Diseño e implementación
### Estructura general
/src/
├─ ClienteJWT.cpp / ClienteJWT.h # Lógica del cliente, envío de solicitudes
├─ ServidorJWT.cpp / ServidorJWT.h # Lógica del servidor, endpoints y JWT
├─ Usuarios.cpp / Usuarios.h # Carga y validación de usuarios
├─ main_cliente.cpp # Punto de entrada del cliente
├─ main_servidor.cpp # Punto de entrada del servidor
└─ p.txt # Datos auxiliares

### Decisiones de implementación
- Lenguaje: **C++17** para compatibilidad multiplataforma.
- Librerías externas:
  - `cpp-httplib` para servidor HTTP.
  - `nlohmann/json` para parseo de JSON.
  - `jwt-cpp` para generación y validación de tokens.
- Manejo de memoria automático mediante objetos y RAII; no se utilizan `new`/`delete` manuales.
- Se dividió la lógica en clases para mantener separación clara entre servidor, cliente y manejo de usuarios.


## 4. Procedimiento de pruebas ejecutadas
Las pruebas se realizaron en una VM aislada con:

- **Sistema operativo:** Kali Linux 2024.1  
- **Hypervisor:** VirtualBox  
- **Snapshot:** “Snapshot previo a pruebas”  
- **IP interna:** 192.168.10.1  
- **Compilador:** g++ (Debian 12.2.0)

### Flujo reproducido
1. Compilación del servidor:
g++ ServidorJWT.cpp -o servidor -std=c++17
./servidor

2. Compilación del cliente:
g++ ClienteJWT.cpp -o cliente -std=c++17
./cliente 192.168.10.1

3. Prueba de login → generación correcta del JWT.  

4. Verificación de token → respuesta válida del servidor.  

5. Prueba de endpoint `/protected` con token válido.  

Todos los pasos están documentados en `/docs/tests.md` con outputs textuales y referencias a capturas en `/evidence/`.


## 5. Análisis estático (hallazgos iniciales)
El binario del servidor fue cargado en Ghidra y se encontraron:

### Funciones principales reconocidas:
- `generarJWT()`
- `guardarToken()`
- `validarJWT()`
- `cargarUsuarios()`
- `main()`

### Strings relevantes extraídos:
- `"login"`
- `"password"`
- `"usuarios.txt"`
- `"tokens.txt"`
- `"clave_super_secreta"` (dentro del flujo interno del JWT)

### Observaciones generales:
- Estructura clara, sin ofuscación.
- Múltiples símbolos debido al uso de templates de C++, lo cual es normal.
- Flujo de ejecución coherente con el diseño del proyecto.

Capturas del proyecto Ghidra fueron añadidas en `/evidence/`.


## 6. Análisis dinámico (hallazgos iniciales)
- El servidor se ejecutó correctamente en `0.0.0.0:8080`.
- El cliente logró conectarse y transmitir credenciales sin interrupciones.
- El JWT fue generado y almacenado correctamente en `tokens.txt`.
- `validarJWT()` devolvió estado exitoso.
- No hubo errores críticos ni excepciones detectadas.
- El tráfico capturado en Wireshark mostró comunicación HTTP estándar sin comportamientos inesperados.

Diferencias entre comportamiento esperado y observado:  
**Ninguna relevante**, salvo la necesidad de asegurar dependencias externas al compilar (httplib y json).


## 7. Riesgos identificados y mitigaciones aplicadas
| Riesgo | Mitigación |
|-------|------------|
| Clave secreta expuesta en el binario | Documentado como riesgo y recomendación de usar variables de entorno para la versión final |
| Ausencia de HTTPS | Limitar pruebas a ambiente aislado; documentado para fase final |
| Lectura de archivos en texto plano | Control estricto del entorno y permisos en VM |
| Dependencias externas no validadas | Se establecieron versiones específicas y se probaron en laboratorio |


## 8. Trabajo pendiente y plan para la entrega final
Para completar el proyecto en la versión final se tiene previsto:

### **1) Crear Makefile para automatizar compilación**
- Unificar la compilación de servidor y cliente en un solo archivo Makefile.  
- Asegurar reproducibilidad inmediata sin comandos manuales.  

### **2) Limpieza de código y eliminación de secciones innecesarias**
- Revisar encabezados innecesarios.  
- Estandarizar formato de código.  
- Eliminar comentarios obsoletos y dependencias no usadas.  

### **3) Optimización leve del cliente para manejo de fallos**
- Agregar manejo de errores ante pérdida de conexión.  
- Validación explícita de JSON malformado.  
- Mensajes más informativos en caso de fallo durante login o validación.



