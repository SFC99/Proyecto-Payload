#pragma once
#include <string>
#include <unordered_map>

bool cargarUsuarios(const std::string& archivo, std::unordered_map<std::string, std::string>& usuarios);
bool guardarToken(const std::string& archivo, const std::string& usuario, const std::string& token);
