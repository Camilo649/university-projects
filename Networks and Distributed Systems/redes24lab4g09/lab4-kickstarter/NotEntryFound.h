#ifndef NOTENTRYFOUND_H
#define NOTENTRYFOUND_H

#include <exception>
#include <string>

class NotEntryFound : public std::exception {
private:
    std::string message;
public:
   NotEntryFound(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // NOTENTRYFOUND_H