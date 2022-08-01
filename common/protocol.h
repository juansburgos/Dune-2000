#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <arpa/inet.h>
#include <cstdint>
#include <string>
#include "dto.h"
#include "socket.h"

#define PROT_SHORT_SIZE 1
#define PROT_LONG_SIZE 2

// Client->Server
#define PROT_UNIRSE_CODE 1
#define PROT_LISTAR_JUEGOS_CODE 2
#define PROT_CREAR_PARTIDA_CODE 3
#define PROT_LISTAR_MAPAS_CODE 4
#define PROT_MOVER_CODE 5
#define PROT_CONSTRUIR_CODE 6
#define PROT_CREAR_UNIDAD_CODE 7
#define PROT_ATACAR_CODE 8
#define PROT_DESTRUIR_CODE 9

class Protocol {
   protected:
    Socket socket;

   public:
    explicit Protocol(Socket peer);

    void sendUChar(unsigned char c);

    unsigned char receiveUChar();

    void send16(uint16_t v);

    uint16_t receive16();

    void sendName(const std::string& name);

    std::string receiveName();

    Protocol(const Protocol&) = delete;

    Protocol& operator=(const Protocol&) = delete;

    void sendPosition(std::pair<int, int> const& position);

    std::pair<int, int> receivePosition();

    virtual void stop();
};

#endif  // PROTOCOL_H
