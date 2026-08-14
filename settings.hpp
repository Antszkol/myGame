#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

class setting{
    public:
        void saveSettings(int brightness, pair<int, int> windowSize);

        int getBrightness() const;
        pair<int, int> getWindowSize() const;
        vector<pair<int, int>> getAvailableResolutions() const;
    private:
        string path;
        int brightness;
        pair<int, int> windowSize = {1920, 1080};
        vector<pair<int, int>> availableResolutions = {
            {1920, 1080},
            {1280, 720},
            {960, 540}
        };
};
