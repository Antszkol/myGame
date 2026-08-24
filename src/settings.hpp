#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

class Setting{
    public:
        void saveSettings(int brightness, pair<int, int> windowSize);

        int getBrightness() const;
        pair<int, int> getWindowSize() const;
        vector<pair<int, int>> getAvailableResolutions() const;
    private:
        string path_;
        int brightness_;
        pair<int, int> windowSize_ = {1920, 1080};
        vector<pair<int, int>> availableResolutions_ = {
            {1920, 1080},
            {1280, 720},
            {960, 540}
        };
};