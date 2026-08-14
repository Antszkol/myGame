#include "settings.hpp"

void setting::saveSettings(int newBrightness, pair<int, int> newWindowSize){
    brightness = newBrightness;
    windowSize = newWindowSize;
}

int setting::getBrightness() const {
    return brightness;
}

pair<int, int> setting::getWindowSize() const {
    return windowSize;
}

vector<pair<int, int>> setting::getAvailableResolutions() const {
    return availableResolutions;
}
