# 🧩 Tarea 5 — Primer avance PIA — Equipo SecureAuth

## 📘 Resumen del proyecto
El proyecto tiene como objetivo **implementar y documentar un sistema de autenticación mediante JSON Web Tokens (JWT)** para validar la identidad de usuarios en un entorno seguro.  
El *payload* del JWT permitirá la **transmisión verificada de información de sesión** entre el cliente y el servidor, garantizando la integridad y confidencialidad de los datos sin mantener sesiones persistentes en el backend.

---

## 🎯 Alcance y límites

### ✅ Funcionalidades permitidas (alcance)
- Generación de tokens JWT firmados con algoritmo `HS256` o `RS256`.  
- Validación de la firma y expiración del token en cada solicitud.  
- Inclusión de *claims* estándar (`sub`, `name`, `iat`, `exp`) y personalizados (`role`, `permissions`).  
- Uso obligatorio de HTTPS en las comunicaciones cliente-servidor.  
- Flujo completo de autenticación: login → emisión de token → acceso a recursos protegidos.

### ❌ Funcionalidades prohibidas (límites)
- No incluir datos sensibles (contraseñas, secretos externos) dentro del payload.  
- No persistir tokens fuera del entorno de pruebas.  
- No exponer claves privadas o llaves secretas en repositorios públicos.  
- No realizar pruebas en servidores productivos ni con usuarios reales.

---

## 🗓️ Plan de trabajo por fases

| **Fase** | **Descripción** | **Fecha límite** | **Resultado esperado** |
|-----------|-----------------|------------------|------------------------|
| **Fase 1 – Diseño** | Definición del flujo de autenticación JWT y estructura del payload. | 31/10/2025 | Diagrama de flujo y documento técnico inicial. |
| **Fase 2 – Implementación** | Codificación de endpoints `/login`, `/validate`, `/protected`. | 07/11/2025 | API funcional en entorno de pruebas. |
| **Fase 3 – Pruebas** | Pruebas unitarias y validación de seguridad (exp, firma, roles). | 14/11/2025 | Resultados de pruebas y reporte de errores. |
| **Fase 4 – Documentación** | Redacción del manual técnico y entrega del avance final. | 20/11/2025 | Documento final y commit etiquetado. |

---

## 👥 Distribución de tareas por integrante

| **Integrante** | **Tareas asignadas** |
|----------------|----------------------|
| **Angel David Morales Palomo** | • Diseñar el flujo de autenticación y estructura del JWT (header, payload, signature).<br>• Implementar endpoint `/login` para generar tokens.<br>• Documentar el diseño técnico inicial y los *claims* usados. |
| **Sofía Martínez Cisneros** | • Desarrollar el middleware de verificación y validación de tokens.<br>• Implementar manejo de errores (token expirado, inválido o modificado).<br>• Realizar pruebas unitarias en endpoints protegidos. |
| **Juan Angel Rodriguez Bulnes** | • Configurar las medidas de seguridad del entorno (HTTPS, variables de entorno, claves).<br>• Ejecutar pruebas funcionales completas del flujo JWT.<br>• Elaborar documentación final, incluyendo sección de seguridad y conclusiones. |

---

## 🔒 Medidas éticas y de seguridad

- Todo el desarrollo se realiza en **máquinas virtuales (VMs) aisladas**, sin conexión a redes productivas.  
- Se crean **snapshots antes de cada cambio importante**, para revertir el entorno si ocurre un fallo.  
- No se realiza **exfiltración ni persistencia** de datos fuera del entorno controlado.  
- Las **claves secretas** y configuraciones sensibles se almacenan mediante **variables de entorno cifradas**.  
- Se usa **HTTPS obligatorio** y se verifica la **integridad de tokens** mediante firma digital.  
- Se mantiene un archivo `SECURITY.md` con políticas de mitigación y auditoría.

---

## 🏷️ Commit / Tag inicial



---

## 📎 Notas finales
Este documento sirve como base para el primer avance del PIA.  
Todas las pruebas, configuraciones y desarrollos descritos se realizarán en un entorno académico controlado, siguiendo prácticas seguras y éticas.
