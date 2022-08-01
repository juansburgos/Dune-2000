#ifndef PROTOCOLERROR_H
#define PROTOCOLERROR_H

#include <string>
#include <stdexcept>

class ProtocolError : public std::runtime_error {
public:
    explicit ProtocolError(const std::string &msg) : runtime_error(msg) {}
};

#endif //PROTOCOLERROR_H
