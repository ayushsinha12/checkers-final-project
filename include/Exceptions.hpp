#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class InvalidMoveException : public std::exception {
private:
    std::string msg;
public:
    InvalidMoveException(const std::string & m);
    virtual ~InvalidMoveException() throw();
    virtual const char * what() const throw();
};

class OutOfBoundsException : public std::exception {
private:
    std::string msg;
public:
    OutOfBoundsException(const std::string & m);
    virtual ~OutOfBoundsException() throw();
    virtual const char * what() const throw();
};

#endif