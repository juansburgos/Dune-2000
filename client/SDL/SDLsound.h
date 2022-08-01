#ifndef SDLSOUND_H
#define SDLSOUND_H

#include "SDL2pp/Chunk.hh"
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>
#include <map>
#include <string>

using namespace SDL2pp;

class SDLsound {
    public:
        explicit SDLsound(int house);
        ~SDLsound();
        void playHouseSound(const std::string &action);
        void playUnitSelect(int codigoUnit);
        void playUnitAtack(int codigoUnit);

    private:
        int house;
        Mixer mixer;
        std::map<int, std::pair<Chunk*, Chunk*>> unitSound;
        std::map<std::string, Chunk*> houseSound;
        std::string path;
        // Metodos privados

        void cargarDirectorios();
        void cargarHouseSound();
        void cargarUnitSound();

};

#endif