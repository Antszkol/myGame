#pragma once
#include <string>

class Message {
    public:
        virtual ~Message() = default;

        virtual std::string describe() const = 0;
};
