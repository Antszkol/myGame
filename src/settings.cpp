#include "settings.hpp"

void Setting::saveSettings(pair<int, int> newWindowSize){
    windowSize_ = newWindowSize;
}

pair<int, int> Setting::getWindowSize() const {
    return windowSize_;
}

vector<pair<int, int>> Setting::getAvailableResolutions() const {
    return availableResolutions_;
}