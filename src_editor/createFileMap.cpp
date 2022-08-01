#include "createFileMap.h"
#include <algorithm>
#include <utility>
#include <vector>
#include <yaml-cpp/emittermanip.h>
#include <iostream>

CreateFileMap::CreateFileMap(const std::vector<std::vector<int>> &tiles,
                            const std::vector<std::vector<int>> &specias,
                            const std::vector<std::pair<int, int>> &builds,
                            const std::vector<std::pair<int, int>> &worms,
                            const std::string &nameTile) : 
                            listaTiles(tiles), listaSpecias(specias),
                            listaBuilds(builds), listaWorm(worms),
                            nameTile(nameTile) {
}

const char* CreateFileMap::crearMapYAML() {
    file << YAML::BeginMap;
    file << YAML::Key << "terrain";
    file << YAML::Value << nameTile;
    this->crearMapaYAML();
    this->crearSpeciaYAML();
    this->crearBuildYAML();
    this->crearWormYAML();
    file << YAML::EndMap; 
    return file.c_str();
}

void CreateFileMap::crearMapaYAML() {
    file << YAML::Key << "tiles";
    file << YAML::Value << YAML::BeginMap;
    this->iterarMatriz(this->listaTiles);
    file << YAML::EndMap;
}

void CreateFileMap::crearSpeciaYAML() {
    file << YAML::Key << "specia";
    file << YAML::Value << YAML::BeginMap;
    this->iterarMatriz(this->listaSpecias);
    file << YAML::EndMap;
}

void CreateFileMap::crearBuildYAML() {
    file << YAML::Key << "players";
    file << YAML::Value << YAML::BeginMap;
    this->iterarVector(this->listaBuilds);
    file << YAML::EndMap;
}

void CreateFileMap::crearWormYAML() {
    file << YAML::Key << "worms";
    file << YAML::Value << YAML::Flow; 
    file << YAML::BeginMap;
    std::for_each(listaWorm.begin(), listaWorm.end(), [&](const auto& worm){
        file << YAML::Key << worm.first << YAML::Value << worm.second;
    });
    file << YAML::EndMap;
}

void CreateFileMap::iterarMatriz(const std::vector<std::vector<int>> &lista) {
    int i = 0;
    std::for_each (lista.begin(), lista.end(), [&](const auto &fila) {
        file << YAML::Key << i;
        file << YAML::Value << YAML::Flow << fila;
        i++;
    });
}

void CreateFileMap::iterarVector(const std::vector<std::pair<int, int>> &lista) {
    int i = 0;
    std::for_each (lista.begin(), lista.end(), [&](const auto &fila) {
        file << YAML::Key << i;
        file << YAML::Value << YAML::Flow << YAML::BeginSeq <<
                    fila.first << fila.second << YAML::EndSeq;
        i++;
    });
}

CreateFileMap::~CreateFileMap() {
}
