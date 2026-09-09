#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

/// @brief App-wide display settings (independent of any particular battle).
class Setting{
    public:
        /// @param windowSize new window resolution.
        void saveSettings(pair<int, int> windowSize);

        /// @return current window resolution.
        pair<int, int> getWindowSize() const;

        /// @return every resolution offered in the settings dialog.
        vector<pair<int, int>> getAvailableResolutions() const;
    private:
        string path_;
        pair<int, int> windowSize_ = {1920, 1080};
        vector<pair<int, int>> availableResolutions_ = {
            {1920, 1080},
            {1280, 720},
            {960, 540}
        };
};