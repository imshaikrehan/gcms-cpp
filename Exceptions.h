#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class NoBinFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "No Bin found to store the given object";
    }
};

#endif // EXCEPTIONS_H
