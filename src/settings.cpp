#include "settings.hpp"

void Setting::saveSettings(int newBrightness, pair<int, int> newWindowSize){
    brightness_ = newBrightness;
    windowSize_ = newWindowSize;
}

int Setting::getBrightness() const {
    return brightness_;
}

pair<int, int> Setting::getWindowSize() const {
    return windowSize_;
}

vector<pair<int, int>> Setting::getAvailableResolutions() const {
    return availableResolutions_;
}