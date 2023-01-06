#ifndef CUSTOM_EXCEPTIONS
#define CUSTOM_EXCEPTIONS

#include <exception>
#include <string>

class NoAvailableStageException : public std::exception
{
private:
    std::string message;

public:
    NoAvailableStageException(std::string msg) : message(msg) {}

    std::string what () {
        return message;
    }
};

#endif // CUSTOM_EXCEPTIONS
