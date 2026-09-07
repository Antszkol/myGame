#include "logger.hpp"
#include <iostream>

void Logger::addMessage(std::unique_ptr<Message> messagePtr){
    this->messages_.push_back(std::move(messagePtr));
    return;
}

void Logger::printAllMessages() const{
    for(const auto& messagePtr : this->messages_){
        std::cout << messagePtr->describe() << std::endl;
    }
    return;
}

std::string Logger::getLastMessageText() const{
    if(this->messages_.empty()){
        return "";
    }
    return this->messages_.back()->describe();
}

const std::vector<std::unique_ptr<Message>>& Logger::getMessages() const{
    return this->messages_;
}
