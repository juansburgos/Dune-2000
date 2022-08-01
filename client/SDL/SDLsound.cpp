#include "SDLsound.h"

#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <string>

#include "SDL2pp/Chunk.hh"
#include "SDL_audio.h"
#include "SDL_mixer.h"
#include "defines.h"

SDLsound::SDLsound(int house) : house(house),
                                mixer(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 512) {
    srand(time(NULL));
    this->cargarDirectorios();
    this->cargarHouseSound();
    this->cargarUnitSound();
}

void SDLsound::cargarUnitSound() {
    this->unitSound = {
        {0, {new Chunk(path + "units/infantery-select.mp3"), new Chunk(path + "units/infantery-atack.mp3")}},
        {2, {new Chunk(path + "units/infantery-select.mp3"), new Chunk(path + "units/infantery-atack.mp3")}},
        {4, {new Chunk(path + "units/VSEL1.mp3"), new Chunk(path + "units/VCONF1.mp3")}},
        {5, {new Chunk(path + "units/VSEL2.mp3"), new Chunk(path + "units/VCONF2.mp3")}},
        {6, {new Chunk(path + "units/VSEL3.mp3"), new Chunk(path + "units/VCONF3.mp3")}},
    };
    if (house == HOUSE_HARKONNEN)
        this->unitSound.insert({3, {new Chunk(path + "units/sardaukar-select.mp3"), new Chunk(path + "units/sardaukar-atack.mp3")}});
    if (house == HOUSE_ATREIDES)
        this->unitSound.insert({1, {new Chunk(path + "units/fremen-select.mp3"), new Chunk(path + "units/fremen-atack.mp3")}});
}

void SDLsound::cargarHouseSound() {
    this->houseSound = {
        {"atackBase", new Chunk(path + "sound/ATACK_BASE.mp3")},
        {"build", new Chunk(path + "sound/BUILD.mp3")},
        {"buildLost", new Chunk(path + "sound/BUILD_LOST.mp3")},
        {"buildReady", new Chunk(path + "sound/BUILD_READY.mp3")},
        {"harvestAtack", new Chunk(path + "sound/HARVEST_ATACK.mp3")},
        {"missionFail", new Chunk(path + "sound/MISSION_FAIL.mp3")},
        {"missionWin", new Chunk(path + "sound/MISSION_WIN.mp3")},
        {"money", new Chunk(path + "sound/MONEY.mp3")},
        {"needSilos", new Chunk(path + "sound/NEED_SILOS.mp3")},
        {"notBuilding", new Chunk(path + "sound/NOT_BUILDING_PLACE.mp3")},
        {"power", new Chunk(path + "sound/POWER.mp3")},
        {"unitLost", new Chunk(path + "sound/UNIT_LOST.mp3")},
        {"unitReady", new Chunk(path + "sound/UNIT_READY.mp3")},
        {"wormAtack", new Chunk(path + "sound/WORM_ATACK.mp3")},
        {"wormSignal", new Chunk(path + "sound/WORM_SIGNAL.mp3")},
    };
}

void SDLsound::playHouseSound(const std::string &action) {
    mixer.PlayChannel(-1, *this->houseSound[action], 0);
}

void SDLsound::playUnitSelect(int codigoUnit) {
    if (codigoUnit >= 4)
        codigoUnit = 4 + rand() % 2;  // Reproduce una audio de seleccion de vehiculo
    mixer.PlayChannel(-1, *this->unitSound[codigoUnit].first, 0);
}

void SDLsound::playUnitAtack(int codigoUnit) {
    if (codigoUnit >= 4)
        codigoUnit = 4 + rand() % 2;  // Reproduce una audio de seleccion de vehiculo
    mixer.PlayChannel(-1, *this->unitSound[codigoUnit].second, 0);
}

void SDLsound::cargarDirectorios() {
    switch (this->house) {
        case HOUSE_HARKONNEN:
            path = "../assets/audio/harkonnen/";
            break;
        case HOUSE_ATREIDES:
            path = "../assets/audio/atreides/";
            break;
        case HOUSE_ORDOS:
            path = "../assets/audio/ordos/";
            break;
    }
}

SDLsound::~SDLsound() {
    for (const auto &[key, value] : houseSound)
        delete (value);
    for (const auto &[key, value] : unitSound) {
        delete (value.first);
        delete (value.second);
    }
}