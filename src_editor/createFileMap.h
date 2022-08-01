#ifndef CREATEFILEMAP_H
#define CREATEFILEMAP_H

#include <string>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <map>

class CreateFileMap {
    public:
        CreateFileMap(const std::vector<std::vector<int>> &tiles,
                        const std::vector<std::vector<int>> &specias,
                        const std::vector<std::pair<int, int>> &builds,
                        const std::vector<std::pair<int, int>> &worms,
                        const std::string &nameTile);
        ~CreateFileMap();
        const char* crearMapYAML();

    private:
        YAML::Emitter file;
        std::string nameTile;
        std::vector<std::vector<int>> listaTiles;
        std::vector<std::vector<int>> listaSpecias;
        std::vector<std::pair<int, int>> listaBuilds;
        std::vector<std::pair<int, int>> listaWorm;
        void crearMapaYAML();
        void crearSpeciaYAML();
        void agregarTileType();
        void crearBuildYAML();
        void crearWormYAML();
        void iterarMatriz(const std::vector<std::vector<int>> &lista);
        void iterarVector(const std::vector<std::pair<int, int>> &lista);
        
};

#endif
