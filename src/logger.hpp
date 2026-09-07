#pragma once
#include <memory>
#include <string>
#include <vector>
#include "message.hpp"

class Logger {
    public:
        void addMessage(std::unique_ptr<Message> messagePtr);
        void printAllMessages() const;

        std::string getLastMessageText() const;

    private:
        std::vector<std::unique_ptr<Message>> messages_;
};
