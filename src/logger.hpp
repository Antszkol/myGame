#pragma once
#include <memory>
#include <string>
#include <vector>
#include "message.hpp"

/// @brief Owns the full ordered combat log for one battle (see TurnHandler::logger_).
class Logger {
    public:
        /// @brief Appends an event to the end of the log.
        /// @param messagePtr the event to record; ownership is transferred to the Logger.
        void addMessage(std::unique_ptr<Message> messagePtr);

        /// @brief Dumps every recorded event's describe() text to std::cout, in order.
        void printAllMessages() const;

        /// @return the describe() text of the most recently added message, or an empty string if none.
        std::string getLastMessageText() const;

        /// @return every recorded event, in the order they occurred.
        const std::vector<std::unique_ptr<Message>>& getMessages() const;

    private:
        std::vector<std::unique_ptr<Message>> messages_;
};
