#include "Exceptions.hpp"

InvalidMoveException::InvalidMoveException(const std::string & m)
    : msg(m) {}

InvalidMoveException::~InvalidMoveException() throw() {}

const char * InvalidMoveException::what() const throw() {
    return msg.c_str();
}

OutOfBoundsException::OutOfBoundsException(const std::string & m)
    : msg(m) {}

OutOfBoundsException::~OutOfBoundsException() throw() {}

const char * OutOfBoundsException::what() const throw() {
    return msg.c_str();
}