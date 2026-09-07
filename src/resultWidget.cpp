#include "resultWidget.hpp"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>

ResultWidget::ResultWidget(int winnerPlayerIdx, const PlayerStats& player1Stats, const PlayerStats& player2Stats, std::vector<Message*> messagePtrVector, QWidget* parent) : QDialog(parent){
    this->setWindowTitle("Battle Result");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* winnerLabel = new QLabel(QString("Player %1 won!").arg(winnerPlayerIdx), this);
    mainLayout->addWidget(winnerLabel);

    QGridLayout* statsLayout = new QGridLayout();
    statsLayout->addWidget(new QLabel("", this), 0, 0);
    statsLayout->addWidget(new QLabel("Player 1", this), 0, 1);
    statsLayout->addWidget(new QLabel("Player 2", this), 0, 2);

    this->addStatsRow(statsLayout, 1, "Enemies killed", player1Stats.fragCount_, player2Stats.fragCount_);
    this->addStatsRow(statsLayout, 2, "Casualties", player1Stats.casualtyCount_, player2Stats.casualtyCount_);
    this->addStatsRow(statsLayout, 3, "Units recruited", player1Stats.recruitedUnitsCount_, player2Stats.recruitedUnitsCount_);
    this->addStatsRow(statsLayout, 4, "Damage dealt", player1Stats.damageDealt_, player2Stats.damageDealt_);
    this->addStatsRow(statsLayout, 5, "Damage received", player1Stats.damageReceived_, player2Stats.damageReceived_);

    mainLayout->addLayout(statsLayout);

    QLabel* logLabel = new QLabel("Battle log:", this);
    mainLayout->addWidget(logLabel);

    QListWidget* logListWidget = new QListWidget(this);
    for(const auto& messagePtr : messagePtrVector){
        logListWidget->addItem(QString::fromStdString(messagePtr->describe()));
    }
    mainLayout->addWidget(logListWidget);
}

void ResultWidget::addStatsRow(QGridLayout* gridLayout, int row, const QString& label, int player1Value, int player2Value){
    gridLayout->addWidget(new QLabel(label, this), row, 0);
    gridLayout->addWidget(new QLabel(QString::number(player1Value), this), row, 1);
    gridLayout->addWidget(new QLabel(QString::number(player2Value), this), row, 2);
    return;
}
