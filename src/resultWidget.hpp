#pragma once
#include <QDialog>
#include <QString>
#include <vector>
#include "message.hpp"
#include "playerStats.hpp"

class QGridLayout;

/// @brief End-of-battle dialog: winner announcement, a per-player stats grid, and the full
/// combat log.
class ResultWidget : public QDialog {
    Q_OBJECT

    public:
        /// @param winnerPlayerIdx index of the winning player.
        /// @param player1Stats player 1's final battle statistics.
        /// @param player2Stats player 2's final battle statistics.
        /// @param messagePtrVector the full combat log to display.
        /// @param parent optional owning widget.
        ResultWidget(int winnerPlayerIdx, const PlayerStats& player1Stats, const PlayerStats& player2Stats, std::vector<Message*> messagePtrVector = {}, QWidget* parent = nullptr);

    private:
        /// @brief Adds one labeled row comparing both players' values to the stats grid.
        void addStatsRow(QGridLayout* gridLayout, int row, const QString& label, int player1Value, int player2Value);
};
