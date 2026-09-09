#pragma once
#include <string>

/// @brief Abstract base for a single recorded battle event (see Logger). Each subclass captures
/// only the data it needs to render itself as text.
class Message {
    public:
        virtual ~Message() = default;

        /// @brief Renders this event as a human-readable combat log line.
        /// @return the event description text.
        virtual std::string describe() const = 0;
};
