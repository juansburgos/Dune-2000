#ifndef ACCEPTERROR_H
#define ACCEPTERROR_H

#include <string>

class AcceptError : public std::runtime_error {
public:
    explicit AcceptError(const std::string &msg) : runtime_error(msg) {}
};

#endif //ACCEPTERROR_H
