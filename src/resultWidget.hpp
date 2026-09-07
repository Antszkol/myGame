#pragma once
#include <QDialog>
#include <QString>
#include <vector>
#include "message.hpp"
#include "playerStats.hpp"

class QGridLayout;

class ResultWidget : public QDialog {
    Q_OBJECT

    public:
        ResultWidget(int winnerPlayerIdx, const PlayerStats& player1Stats, const PlayerStats& player2Stats, std::vector<Message*> messagePtrVector = {}, QWidget* parent = nullptr);

    private:
        void addStatsRow(QGridLayout* gridLayout, int row, const QString& label, int player1Value, int player2Value);
};
