#include "dialoggamestart.h"
#include "ui_dialoggamestart.h"
#include <QDebug>

GameStartSettings DialogGameStart::getGameSettings()
{
    return m_gameSettings;
}

DialogGameStart::DialogGameStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGameStart)
{



    ui->setupUi(this);
    setWindowTitle("Pirkanmaan Valloitus");

    // Player Count and Names
    ui->playerCountSlider->setValue(2);
    ui->playerCountLabel->setText(QString::number(2));

    //set Player default names
    ui->player1nameEdit->setText("Player 1");
    ui->player2nameEdit->setText("Player 2");
    ui->player3nameEdit->setText("Player 3");
    ui->player4nameEdit->setText("Player 4");

    //Disable and enable player name fields based o ncount
    connect(ui->playerCountSlider, &QSlider::valueChanged, [=](){
        int playerCount = ui->playerCountSlider->value();

        ui->playerCountLabel->setText(QString::number(playerCount));

        if(playerCount >= 3) {
            ui->player3NameLabel->setEnabled(true);
            ui->player3nameEdit->setEnabled(true);

            if(playerCount == 4) {
                ui->player4NameLabel->setEnabled(true);
                ui->player4nameEdit->setEnabled(true);
            } else {
                ui->player4NameLabel->setEnabled(false);
                ui->player4nameEdit->setEnabled(false);
            }
        }
        else {
            ui->player3NameLabel->setEnabled(false);
            ui->player3nameEdit->setEnabled(false);
        }
    });


    //Map Size SLiders

    ui->mapWidthSlider->setMinimum(8);
    ui->mapHeightSlider->setMinimum(8);
    ui->mapWidthSlider->setMaximum(100);
    ui->mapHeightSlider->setMaximum(100);
    ui->mapWidthSlider->setValue(32);
    ui->mapHeightSlider->setValue(32);

    ui->mapWidthLabel->setText(QString::number(32));
    ui->mapHeightLabel->setText(QString::number(32));

    ui->mapWidthSlider->setTickPosition(QSlider::TickPosition::TicksLeft);
    ui->mapHeightSlider->setTickPosition(QSlider::TickPosition::TicksLeft);

    connect(ui->mapWidthSlider, &QSlider::valueChanged, [=](){
        ui->mapWidthLabel->setText(QString::number(ui->mapWidthSlider->value()));
    });

    connect(ui->mapHeightSlider, &QSlider::valueChanged, [=](){
        ui->mapHeightLabel->setText(QString::number(ui->mapHeightSlider->value()));
    });
}

DialogGameStart::~DialogGameStart()
{
    delete ui;
}


void DialogGameStart::on_exitGameBtn_clicked()
{
      qDebug() << "END GAME GAME";
    reject();
}

void DialogGameStart::on_startGameBtn_clicked()
{
    qDebug() << "START GAME";

    GameStartSettings settings;

    settings.playerCount = ui->playerCountSlider->value();

    std::vector<std::string> playerNames;

    playerNames.push_back(ui->player1nameEdit->text().toStdString());
    playerNames.push_back(ui->player2nameEdit->text().toStdString());

    if(settings.playerCount >= 3) {
        playerNames.push_back(ui->player3nameEdit->text().toStdString());
    }

    if(settings.playerCount == 4) {
        playerNames.push_back(ui->player4nameEdit->text().toStdString());
    }

    int mapWidth = ui->mapWidthSlider->value();
    int mapHeight = ui->mapHeightSlider->value();
    settings.mapSize = std::pair<int,int>(mapWidth, mapHeight);
    settings.playerNames = playerNames;
    m_gameSettings = settings;


    accept();
}
