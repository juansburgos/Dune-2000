#include "protocol.h"
#include <string>
#include <utility>
#include "protocolerror.h"

Protocol::Protocol(Socket peer) : socket(std::move(peer)) {
}

void Protocol::sendUChar(unsigned char c) {
    bool was_closed;
    socket.sendall(&c, PROT_SHORT_SIZE, &was_closed);
    if (was_closed)
        throw ProtocolError("Escritura en socket cerrado");
}

unsigned char Protocol::receiveUChar() {
    bool was_closed = false;
    unsigned char c;
    socket.recvall(&c, PROT_SHORT_SIZE, &was_closed);
    if (was_closed)
        throw ProtocolError("Lectura de socket cerrado");
    return c;
}

void Protocol::send16(uint16_t v) {
    bool was_closed;
    uint16_t vn = htons(v);
    socket.sendall(&vn, PROT_LONG_SIZE, &was_closed);
    if (was_closed)
        throw ProtocolError("Escritura en socket cerrado");
}

uint16_t Protocol::receive16() {
    bool was_closed;
    uint16_t res;
    socket.recvall(&res, PROT_LONG_SIZE, &was_closed);
    if (was_closed)
        throw ProtocolError("Lectura de socket cerrado");
    return ntohs(res);
}

void Protocol::sendName(const std::string &name) {
    bool was_closed;
    send16(name.size());
    socket.sendall(&name[0], name.size(), &was_closed);
    if (was_closed)
        throw ProtocolError("Escritura en socket cerrado");
}

std::string Protocol::receiveName() {
    bool was_closed = false;
    uint16_t cant = receive16();
    std::string name(cant, ' ');
    socket.recvall(&name[0], cant, &was_closed);
    if (was_closed)
        throw ProtocolError("Lectura de socket cerrado");
    return name;
}

void Protocol::sendPosition(std::pair<int, int> const &position) {
    send16(position.first);
    send16(position.second);
}

std::pair<int, int> Protocol::receivePosition() {
    return {receive16(), receive16()};
}

void Protocol::stop() {
    socket.shutdown(2);
    socket.close();
}

