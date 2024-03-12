#include "dialoggameend.h"
#include "ui_dialoggameend.h"
#include <QDebug>
#include "buildings/buildingbase.h"
#include "tiles/tilebase.h"
#include <QDialog>

DialogGameEnd::DialogGameEnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGameEnd)
{
    ui->setupUi(this);
    m_maxPoints = 0;
    m_winners = {};
    setWindowTitle("Pirkanmaan Valloitus");
}

DialogGameEnd::~DialogGameEnd()
{
    delete ui;
}

void DialogGameEnd::setStats(const std::shared_ptr<std::vector<std::shared_ptr<Player>>> playerList,
                             std::vector<std::shared_ptr<Course::TileBase>> tileList)
{
    qDebug() << "SET STATS";
    qDebug() << "TILE LIST SIZE" << tileList.size();
    int row = 1;
    unsigned long long size = playerList->size();

    for (unsigned long long i = 0; i < size; i++) {
        int points = 0;
        PlayerResource resources = playerList->at(i)->getResources();
        std::vector<std::shared_ptr<Course::GameObject>> objects = playerList->at(i)->getObjects();

        // Player Name Label
        addLabel(row, 0, playerList->at(i)->getName().c_str());

        int column = 1;
        // Resource Labels
        for (PlayerResource::iterator it = resources.begin(); it != resources.end(); ++it) {
            int amount = it->second;
            points = points + amount;
            addLabel(row, column, QString::number(amount));
            column++;
        }

        // Tile Label
        int tiles = 0;
        for (std::shared_ptr<Course::TileBase> tile : tileList) {
            if (tile->getOwner() == playerList->at(i)) {
                points = points + 500;
                tiles++;
            }
        }

        addLabel(row, 6, QString::number(tiles));

        // Worker and Building Labels
        std::vector<std::string> tile_types = {"Grassland", "Forest", "Water", "Desert", "Hill", "Swamp", "Water"};
        std::vector<std::string> building_types = {"Farm", "HeadQuarters", "Outpost", "EmploymentOffice", "FishingHut", "Lumbermill", "Mine", "Quarry"};
        std::vector<std::string> worker_types = {"BasicWorker", "TrainedWorker", "Farmer", "Fisher", "Lumberjack", "Miner", "Stonemason"};

        int workers = 0;
        int buildings = 0;

        for (auto object : objects) {
            std::string type = object->getType();
            if (std::find(building_types.begin(), building_types.end(), type) != building_types.end()) {
                points = points + 2000;
                buildings++;
            }
            if (std::find(worker_types.begin(), worker_types.end(), type) != worker_types.end()) {
                points = points + 200;
                workers++;
            }
        }

        addLabel(row, 7, QString::number(buildings));
        addLabel(row, 8, QString::number(workers));
        addLabel(row, 9, QString::number(points));

        if (points > m_maxPoints) {
            m_maxPoints = points;
            m_winners.clear();
            m_winners.push_back(playerList->at(i)->getName());
        }
        else if (points == m_maxPoints) {
            m_winners.push_back(playerList->at(i)->getName());
        }

        row++;
    }

    setWinnerText();
}

void DialogGameEnd::addLabel(int row, int column, QString text)
{
    QLabel *label = new QLabel;
    label->setText(text);
    label->setAlignment(Qt::AlignHCenter);
    ui->gridLayout->addWidget(label, row, column);
    label->show();
}

void DialogGameEnd::setWinnerText() {
    std::string winners = "";
    for (unsigned long long i = 0; i < m_winners.size(); i++) {
        if (i != 0) {
            winners = winners + ", ";
        }

        winners = winners + m_winners.at(i);
    }

    ui->winnerNameLabel->setText(winners.c_str());

    std::string scoreText = "";
    if (m_winners.size() > 1) {
        scoreText = "drew with " + std::to_string(m_maxPoints) + " points!";
    }
    else {
        scoreText = "is the winner with " + std::to_string(m_maxPoints) + " points!";
    }

    ui->winnerScoreLabel->setText(scoreText.c_str());
}

void DialogGameEnd::on_exitBtn_clicked() {
    reject();
}
