#pragma once
#include <string>

class JSONFormatError : public std::exception
{
public:
    JSONFormatError(std::string msg)
    {
        this->msg = msg;
    }
    const char* what() const noexcept
    {
        return this->msg.c_str();
    }
private:
    std::string msg;
};
