#pragma once
#include <string>

std::string loginServidor(const std::string& servidor, int puerto,
                          const std::string& usuario, const std::string& password);

std::string obtenerDatos(const std::string& servidor, int puerto, const std::string& token);
