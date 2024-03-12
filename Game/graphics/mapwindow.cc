#include "mapwindow.hh"
#include "ui_mapwindow.h"
#include "graphics/simplemapitem.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <math.h>
#include "gameview.h"
#include "gamescene.h"
#include "gameeventhandler.h"

#include "core/gameresourcemaps.hh"

#include <QTimer>

MapWindow::MapWindow(QWidget *parent,
                     int width,
                     int height,
                       const std::shared_ptr<GameEventHandler> &ghandler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_gameEventHandler(ghandler),
    m_simplescene(new GameScene(this, width, height, 50, ghandler))
{
    m_ui->setupUi(this);
    setWindowTitle("Pirkanmaan Valloitus");

    GameView * graphicsView = new GameView(this);
    m_ui->verticalLayout_3->addWidget(graphicsView);


    GameScene* sgs_rawptr = m_simplescene.get();
    graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));

    // Create Building Buttons
    buildHQBtn = createObjectButton("HQ", Course::ConstResourceMaps::HQ_BUILD_COST);
    m_ui->buildGridLayout->addWidget(buildHQBtn, 0, 0);
    buildHQBtn->show();
    QWidget::connect(buildHQBtn, &ObjectButton::clicked, [=]{
        setBuildingMode(CursorInsertTarget::HEADQUARTERS);
    });

    buildFarmBtn = createObjectButton("Farm", Course::ConstResourceMaps::FARM_BUILD_COST);
    m_ui->buildGridLayout->addWidget(buildFarmBtn, 0, 1);
    buildFarmBtn->show();
    QWidget::connect(buildFarmBtn, &ObjectButton::clicked, [=]{
        setBuildingMode(CursorInsertTarget::FARM);
    });

    buildOutpostBtn = createObjectButton("Outpost", Course::ConstResourceMaps::OUTPOST_BUILD_COST);
    m_ui->buildGridLayout->addWidget(buildOutpostBtn, 0, 2);
    buildOutpostBtn->show();
    QWidget::connect(buildOutpostBtn, &ObjectButton::clicked, [=]{
        setBuildingMode(CursorInsertTarget::OUTPOST);
    });

    buildFishingHutBtn = createObjectButton("Fishing Hut", Course::ConstResourceMaps::FH_BUILD_COST);
    m_ui->buildGridLayout->addWidget(buildFishingHutBtn, 0, 3);
    buildFishingHutBtn->show();
    QWidget::connect(buildFishingHutBtn, &ObjectButton::clicked, [=]{
        setBuildingMode(CursorInsertTarget::FISHINGHUT);
    });

    buildEObtn = createObjectButton("Employment Office", Course::ConstResourceMaps::EMPLOYMENT_OFFICE_BUILD_COST);
    m_ui->buildGridLayout->addWidget(buildEObtn);
    buildEObtn->show();
    QWidget::connect(buildEObtn, &ObjectButton::clicked, [=]{
        setBuildingMode(CursorInsertTarget::EMPLOYMENTOFFICE);
    });

    // TODO: Unique icons

    buildLMBtn = createObjectButton("Lumber Mill", Course::ConstResourceMaps::LM_BUILD_COST);
    m_ui->buildGridLayout->addWidget(buildLMBtn);
    buildLMBtn->show();
    QWidget::connect(buildLMBtn, &ObjectButton::clicked, [=]{
        setBuildingMode(CursorInsertTarget::LUMBERMILL);
    });

    buildMineBtn = createObjectButton("Mine", Course::ConstResourceMaps::MINE_BUILD_COST);
    m_ui->buildGridLayout->addWidget(buildMineBtn);
    buildMineBtn->show();
    QWidget::connect(buildMineBtn, &ObjectButton::clicked, [=]{
        setBuildingMode(CursorInsertTarget::MINE);
    });

    buildQuarryBtn = createObjectButton("Quarry", Course::ConstResourceMaps::QUARRY_BUILD_COST);
    m_ui->buildGridLayout->addWidget(buildQuarryBtn);
    buildQuarryBtn->show();
    QWidget::connect(buildQuarryBtn, &ObjectButton::clicked, [=]{
        setBuildingMode(CursorInsertTarget::QUARRY);
    });

    // Create Worker Buttons
    buildFarmerBtn = createObjectButton("", Course::ConstResourceMaps::FA_RECRUITMENT_COST, ":/images/sprites/farmer.png");
    m_ui->workerLayout->addWidget(buildFarmerBtn, 1, 0);
    buildFarmerBtn->show();
    QWidget::connect(buildFarmerBtn, &ObjectButton::clicked, [=]{
        setInsertWorkerMode(CursorInsertTarget::FARMER);
    });
    setWorkerLabels(0, Course::ConstResourceMaps::FA_WORKER_EFFICIENCY);
    m_ui->setWorker1Btn->hide();

    buildFisherBtn = createObjectButton("", Course::ConstResourceMaps::FISHER_RECRUITMENT_COST, ":/images/sprites/fisher.png");
    m_ui->workerLayout->addWidget(buildFisherBtn, 2, 0);
    buildFisherBtn->show();
    QWidget::connect(buildFisherBtn, &ObjectButton::clicked, [=]{
        setInsertWorkerMode(CursorInsertTarget::FISHER);
    });
    setWorkerLabels(1, Course::ConstResourceMaps::FISHER_WORKER_EFFICIENCY);
    m_ui->setWorker2Btn->hide();

    buildLumberjackBtn = createObjectButton("", Course::ConstResourceMaps::LJ_RECRUITMENT_COST, ":/images/sprites/lumberjack.png");
    m_ui->workerLayout->addWidget(buildLumberjackBtn, 3, 0);
    buildLumberjackBtn->show();
    QWidget::connect(buildLumberjackBtn, &ObjectButton::clicked, [=]{
        setInsertWorkerMode(CursorInsertTarget::LUMBERJACK);
    });
    setWorkerLabels(2, Course::ConstResourceMaps::LJ_WORKER_EFFICIENCY);
    m_ui->setWorker3Btn->hide();

    buildMinerBtn = createObjectButton("", Course::ConstResourceMaps::MI_RECRUITMENT_COST, ":/images/sprites/miner.png");
    m_ui->workerLayout->addWidget(buildMinerBtn, 4, 0);
    buildMinerBtn->show();
    QWidget::connect(buildMinerBtn, &ObjectButton::clicked, [=]{
        setInsertWorkerMode(CursorInsertTarget::MINER);
    });
    setWorkerLabels(3, Course::ConstResourceMaps::MI_WORKER_EFFICIENCY);
    m_ui->setWorker4Btn->hide();

    buildStonemasonBtn = createObjectButton("", Course::ConstResourceMaps::SM_RECRUITMENT_COST, ":/images/sprites/stonemason.png");
    m_ui->workerLayout->addWidget(buildStonemasonBtn, 5, 0);
    buildStonemasonBtn->show();
    QWidget::connect(buildStonemasonBtn, &ObjectButton::clicked, [=]{
        setInsertWorkerMode(CursorInsertTarget::STONEMASON);
    });
    setWorkerLabels(4, Course::ConstResourceMaps::SM_WORKER_EFFICIENCY);
    m_ui->setWorker5Btn->hide();
}


MapWindow::~MapWindow()
{
    delete m_ui;
}

//NOT USED, USING SINGLETON INSTEAD
void MapWindow::setGEHandler(
        const std::shared_ptr<GameEventHandler> &nHandler)
{
    m_gameEventHandler = nHandler;
}



void MapWindow::updatePlayerContext(const std::weak_ptr<Player>& curPlayer)
{
    qDebug() << "current polayer";
    QString playerName = curPlayer.lock()->getName().c_str();

        qDebug() << "PLAYER NAME:" << playerName;

    qDebug() << "set ui indicator";
    m_ui->turnIndicator->setText("Turn: " + playerName);




    qDebug() << "set resources";

    PlayerResource resource = curPlayer.lock()->getResources();

    qDebug() << "get resourcies";

    // Set resource labels
    m_ui->goldLabel->setText(QString::number(resource.at(Course::BasicResource::MONEY)));
    m_ui->woodLabel->setText(QString::number(resource.at(Course::BasicResource::WOOD)));
    m_ui->oreLabel->setText(QString::number(resource.at(Course::BasicResource::ORE)));
    m_ui->stoneLabel->setText(QString::number(resource.at(Course::BasicResource::STONE)));
    m_ui->foodLabel->setText(QString::number(resource.at(Course::BasicResource::FOOD)));


    //set resources per turn labels
    updateBuildButtons(curPlayer);

}


void MapWindow::setGameStateContext(const std::shared_ptr<GameState> &gameState) {
    m_ui->roundIndicator->setText("Turn: " + QString::number(gameState->getTurncount()));
}

void MapWindow::setGameMessage(std::string message) {
    m_ui->gameMessageLabel->setStyleSheet("color: red; font-size:11pt;");
    m_ui->gameMessageLabel->setText(message.c_str());

    //Clear message after time
    QTimer::singleShot(2000, this, [=](){
        //Clear message after time
        if(m_ui->gameMessageLabel->text() != "") {
            QTimer::singleShot(1000, this, [=](){
                m_ui->gameMessageLabel->setText("");
            });
        } else {
    m_ui->gameMessageLabel->setText("");
        }
    });
}

void MapWindow::setCostLabels(Course::ResourceMap resourceMap)
{
    for (Course::ResourceMap::iterator it = resourceMap.begin(); it != resourceMap.end(); ++it) {
        Course::BasicResource key = it->first;
        int cost = -it->second;
        QString costStr;
        costStr.setNum(cost);
        switch(key) {
            case(Course::BasicResource::NONE):
                break;
            case(Course::BasicResource::MONEY):
                m_ui->goldCostLabel->setText(costStr);
                break;
            case(Course::BasicResource::WOOD):
                m_ui->woodCostLabel->setText(costStr);
                break;
            case(Course::BasicResource::STONE):
                m_ui->stoneCostLabel->setText(costStr);
                break;
            case(Course::BasicResource::FOOD):
                m_ui->foodCostLabel->setText(costStr);
                break;
            case(Course::BasicResource::ORE):
                m_ui->oreCostLabel->setText(costStr);
                break;
        }
    }
}

void MapWindow::setWorkerLabels(int row, Course::ResourceMapDouble productionMap)
{
    switch(row) {
    case 0:
        m_ui->worker1GoldLabel->setText(QString::number(productionMap.at(Course::BasicResource::MONEY)));
        m_ui->worker1WoodLabel->setText(QString::number(productionMap.at(Course::BasicResource::WOOD)));
        m_ui->worker1StoneLabel->setText(QString::number(productionMap.at(Course::BasicResource::STONE)));
        m_ui->worker1FoodLabel->setText(QString::number(productionMap.at(Course::BasicResource::FOOD)));
        m_ui->worker1OreLabel->setText(QString::number(productionMap.at(Course::BasicResource::ORE)));
        break;
    case 1:
        m_ui->worker2GoldLabel->setText(QString::number(productionMap.at(Course::BasicResource::MONEY)));
        m_ui->worker2WoodLabel->setText(QString::number(productionMap.at(Course::BasicResource::WOOD)));
        m_ui->worker2StoneLabel->setText(QString::number(productionMap.at(Course::BasicResource::STONE)));
        m_ui->worker2FoodLabel->setText(QString::number(productionMap.at(Course::BasicResource::FOOD)));
        m_ui->worker2OreLabel->setText(QString::number(productionMap.at(Course::BasicResource::ORE)));
        break;
    case 2:
        m_ui->worker3GoldLabel->setText(QString::number(productionMap.at(Course::BasicResource::MONEY)));
        m_ui->worker3WoodLabel->setText(QString::number(productionMap.at(Course::BasicResource::WOOD)));
        m_ui->worker3StoneLabel->setText(QString::number(productionMap.at(Course::BasicResource::STONE)));
        m_ui->worker3FoodLabel->setText(QString::number(productionMap.at(Course::BasicResource::FOOD)));
        m_ui->worker3OreLabel->setText(QString::number(productionMap.at(Course::BasicResource::ORE)));
        break;
    case 3:
        m_ui->worker4GoldLabel->setText(QString::number(productionMap.at(Course::BasicResource::MONEY)));
        m_ui->worker4WoodLabel->setText(QString::number(productionMap.at(Course::BasicResource::WOOD)));
        m_ui->worker4StoneLabel->setText(QString::number(productionMap.at(Course::BasicResource::STONE)));
        m_ui->worker4FoodLabel->setText(QString::number(productionMap.at(Course::BasicResource::FOOD)));
        m_ui->worker4OreLabel->setText(QString::number(productionMap.at(Course::BasicResource::ORE)));
        break;
    case 4:
        m_ui->worker5GoldLabel->setText(QString::number(productionMap.at(Course::BasicResource::MONEY)));
        m_ui->worker5WoodLabel->setText(QString::number(productionMap.at(Course::BasicResource::WOOD)));
        m_ui->worker5StoneLabel->setText(QString::number(productionMap.at(Course::BasicResource::STONE)));
        m_ui->worker5FoodLabel->setText(QString::number(productionMap.at(Course::BasicResource::FOOD)));
        m_ui->worker5OreLabel->setText(QString::number(productionMap.at(Course::BasicResource::ORE)));
        break;
    }
}

void MapWindow::resetCostLabels()
{
    m_ui->goldCostLabel->setText("");
    m_ui->woodCostLabel->setText("");
    m_ui->stoneCostLabel->setText("");
    m_ui->foodCostLabel->setText("");
    m_ui->oreCostLabel->setText("");
}

ObjectButton* MapWindow::createObjectButton(QString label, Course::ResourceMap resourceMap, QString image)
{
    ObjectButton *newBtn = new ObjectButton(label);

    if (image != "") {
        newBtn->setIcon(QIcon(QPixmap(image)));
    }

    QWidget::connect(newBtn, &ObjectButton::hoverEnter, [=]{
        setCostLabels(resourceMap);
    });
    QWidget::connect(newBtn, &ObjectButton::hoverLeave, [=]{
        resetCostLabels();
    });

    return newBtn;
}

void MapWindow::updateWorkerButtons(const std::shared_ptr<Player>& player) {
    if(!m_gameEventHandler.lock()->playerHasFreWorkerSlots(player)) {

        buildMinerBtn->setEnabled(false);
        buildStonemasonBtn->setEnabled(false);
        buildFisherBtn->setEnabled(false);
        buildLumberjackBtn->setEnabled(false);
        buildFarmerBtn->setEnabled(false);
    } else {
        buildMinerBtn->setEnabled(true);
        buildStonemasonBtn->setEnabled(true);
        buildFisherBtn->setEnabled(true);
        buildLumberjackBtn->setEnabled(true);
        buildFarmerBtn->setEnabled(true);
    }
}


void MapWindow::updateBuildButtons(const std::weak_ptr<Player>& curPlayer) {
   PlayerResource resource = curPlayer.lock()->getResources();

   //TODO FUNCTIONISESE, LOOP
    buildFarmBtn->setEnabled(false);
    buildHQBtn->setEnabled(false);
    buildOutpostBtn->setEnabled(false);
    buildFishingHutBtn->setEnabled(false);
    buildEObtn->setEnabled(false);
    buildMineBtn->setEnabled(false);
    buildLMBtn->setEnabled(false);
    buildQuarryBtn->setEnabled(false);

   //GET BUILDING COSTS
    if(curPlayer.lock()->hasEnoughResourcesToBuild(
                Course::ConstResourceMaps::FARM_BUILD_COST))
    {
        qDebug() << "voidaan rakentaa FARM";
        buildFarmBtn->setEnabled(true);

    }

     if(curPlayer.lock()->hasEnoughResourcesToBuild(
                 Course::ConstResourceMaps::HQ_BUILD_COST))
    {
   qDebug() << "voidaan rakentaa HQ";
        buildHQBtn->setEnabled(true);

    }

    if(curPlayer.lock()->hasEnoughResourcesToBuild(Course::ConstResourceMaps::
                                                     OUTPOST_BUILD_COST))
    {
        buildOutpostBtn->setEnabled(true);
    }

    if(curPlayer.lock()->hasEnoughResourcesToBuild(Course::ConstResourceMaps::
                                                   FH_BUILD_COST))
    {
        buildFishingHutBtn->setEnabled(true);
    }

    if(curPlayer.lock()->hasEnoughResourcesToBuild(Course::ConstResourceMaps::
                                                   EMPLOYMENT_OFFICE_BUILD_COST))
    {
        buildEObtn->setEnabled(true);
    }

    if(curPlayer.lock()->hasEnoughResourcesToBuild(Course::ConstResourceMaps::
                                                   LM_BUILD_COST))
    {
        buildLMBtn->setEnabled(true);
    }

    if(curPlayer.lock()->hasEnoughResourcesToBuild(Course::ConstResourceMaps::
                                                   QUARRY_BUILD_COST))
    {
        buildQuarryBtn->setEnabled(true);
    }

    if(curPlayer.lock()->hasEnoughResourcesToBuild(Course::ConstResourceMaps::
                                                   MINE_BUILD_COST))
    {
        buildMineBtn->setEnabled(true);
    }

   this->update();
   //CHECK IF PLAYER HAS ENUF MANI

   //DISABLE IF SO

   //OTHERWISE ENABLE


}

void MapWindow::updateGameScene() {
    m_simplescene->update();
}

void MapWindow::updateProductionContext()
{
    Course::ResourceMap production = m_gameEventHandler.lock()->getCurrentPlayerTotalProduction();

    if(production.size() != 0) {
    for (Course::ResourceMap::iterator it = production.begin(); it != production.end(); ++it) {
        Course::BasicResource key = it->first;
        int amount = it->second;
        QString costStr;
        costStr.setNum(amount);
        switch(key) {
            case(Course::BasicResource::NONE):
                break;
            case(Course::BasicResource::MONEY):
                m_ui->goldTurnLabel->setText(costStr);
                break;
            case(Course::BasicResource::WOOD):
                m_ui->woodTurnLabel->setText(costStr);
                break;
            case(Course::BasicResource::STONE):
                m_ui->stoneTurnLabel->setText(costStr);
                break;
            case(Course::BasicResource::FOOD):
                m_ui->foodTurnLabel->setText(costStr);
                break;
            case(Course::BasicResource::ORE):
                m_ui->oreTurnLabel->setText(costStr);
                break;
        }
    }

    } else {
        m_ui->goldTurnLabel->setText("0");
        m_ui->woodTurnLabel->setText("0");
        m_ui->oreTurnLabel->setText("0");
        m_ui->stoneTurnLabel->setText("0");
        m_ui->foodTurnLabel->setText("0");
    }

    qDebug() << " saatiin total prodution";
}


void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj, std::pair<CursorInsertMode, CursorInsertTarget> type, MapItem *parentTile)
{
    m_simplescene->drawItem(obj, type, parentTile);
}

void MapWindow::on_endTurnBtn_clicked()
{
    m_gameEventHandler.lock()->endTurn();
}

void MapWindow::setBuildingMode(CursorInsertTarget mouseCursorIcon)  {


    if(currentCursorMode == CursorMode::Build) {
        return;
    }
    //TODO järkevämpi tapa viestiä mitä tekee, pois stringistä
    QPixmap icon;
    QPixmap buildTemplate;
    CursorInsertTarget buildTarget;

    switch(mouseCursorIcon) {

    case CursorInsertTarget::FARM: {
        icon =  QPixmap(":/images/sprites/farm.png");
        icon = icon.scaled(25,25, Qt::AspectRatioMode::IgnoreAspectRatio,
                            Qt::TransformationMode::SmoothTransformation);
        buildTemplate =  QPixmap(":/images/sprites/farm.png");
        buildTarget = CursorInsertTarget::FARM;
        break;
    }

    case CursorInsertTarget::HEADQUARTERS: {
        icon =  QPixmap(":/images/sprites/headquarters.png");
        icon = icon.scaled(25,25, Qt::AspectRatioMode::IgnoreAspectRatio,
                            Qt::TransformationMode::SmoothTransformation);
        buildTemplate =  QPixmap(":/images/sprites/headquarters.png");
         buildTarget = CursorInsertTarget::HEADQUARTERS;
        break;
    }

    case CursorInsertTarget::OUTPOST: {
        icon =  QPixmap(":/images/sprites/outpost.png");
        icon = icon.scaled(25,25, Qt::AspectRatioMode::IgnoreAspectRatio,
                            Qt::TransformationMode::SmoothTransformation);
        buildTemplate =  QPixmap(":/images/sprites/outpost.png");
        buildTarget = CursorInsertTarget::OUTPOST;
        break;
    }

    case CursorInsertTarget::FISHINGHUT: {
        icon =  QPixmap(":/images/sprites/fishinghut.png");
        icon = icon.scaled(25,25, Qt::AspectRatioMode::IgnoreAspectRatio,
                            Qt::TransformationMode::SmoothTransformation);
        buildTemplate =  QPixmap(":/images/sprites/fishinghut.png");
        buildTarget = CursorInsertTarget::FISHINGHUT;
        break;
    }

    case CursorInsertTarget::EMPLOYMENTOFFICE: {
        icon =  QPixmap(":/images/sprites/employmentoffice.png");
        icon = icon.scaled(25,25, Qt::AspectRatioMode::IgnoreAspectRatio,
                            Qt::TransformationMode::SmoothTransformation);
        buildTemplate =  QPixmap(":/images/sprites/employmentoffice.png");
        buildTarget = CursorInsertTarget::EMPLOYMENTOFFICE;
        break;
    }

    case CursorInsertTarget::QUARRY: {
        icon =  QPixmap(":/images/sprites/quarry.png");
        icon = icon.scaled(25,25, Qt::AspectRatioMode::IgnoreAspectRatio,
                            Qt::TransformationMode::SmoothTransformation);
        buildTemplate =  QPixmap(":/images/sprites/quarry.png");
        buildTarget = CursorInsertTarget::QUARRY;
        break;
    }

    case CursorInsertTarget::LUMBERMILL: {
        icon =  QPixmap(":/images/sprites/lumbermill.png");
        icon = icon.scaled(25,25, Qt::AspectRatioMode::IgnoreAspectRatio,
                            Qt::TransformationMode::SmoothTransformation);
        buildTemplate =  QPixmap(":/images/sprites/lumbermill.png");
        buildTarget = CursorInsertTarget::LUMBERMILL;
        break;
    }

    case CursorInsertTarget::MINE: {
        icon =  QPixmap(":/images/sprites/mine.png");
        icon = icon.scaled(25,25, Qt::AspectRatioMode::IgnoreAspectRatio,
                            Qt::TransformationMode::SmoothTransformation);
        buildTemplate =  QPixmap(":/images/sprites/mine.png");
        buildTarget = CursorInsertTarget::MINE;
        break;
    }

    }
    currentCursorMode = CursorMode::Build;
    m_simplescene->currentCursorMode = CursorMode::Build;
    m_simplescene->currentBuildTarget = buildTarget;
    buildTemplate = buildTemplate.scaled(48,48, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::FastTransformation);
   this->setCursor(QCursor(QPixmap(buildTemplate)));
}

//TODO ENUM WORKERTTYPE
void MapWindow::setInsertWorkerMode(CursorInsertTarget workerType)
{

    if(currentCursorMode == CursorMode::SetWorker) {
        return;
    }

    qDebug() << "alertaan inserttaamaan workeria: " << workerType;
    currentCursorMode = CursorMode::SetWorker;
    m_simplescene->currentCursorMode = CursorMode::SetWorker;
    m_simplescene->currentBuildTarget = workerType;

    QPixmap workerBuildIcon;
    switch(workerType) {
        case(CursorInsertTarget::MINER):
            workerBuildIcon = QPixmap(":/images/sprites/miner.png");
        break;

        case(CursorInsertTarget::FARMER):
            workerBuildIcon = QPixmap(":/images/sprites/farmer.png");
        break;

        case(CursorInsertTarget::STONEMASON):
            workerBuildIcon = QPixmap(":/images/sprites/stonemason.png");
        break;

        case(CursorInsertTarget::LUMBERJACK):
            workerBuildIcon = QPixmap(":/images/sprites/lumberjack.png");
        break;

        case(CursorInsertTarget::FISHER):
            workerBuildIcon = QPixmap(":/images/sprites/fisher.png");
        break;

        default:
            workerBuildIcon = QPixmap(":/images/sprites/worker.png");
        break;
    }

    workerBuildIcon = workerBuildIcon.scaled(32,32, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::FastTransformation);
    this->setCursor(QCursor(QPixmap(workerBuildIcon)));
}

void MapWindow::mousePressEvent(QMouseEvent *event)
{
     if(currentCursorMode == CursorMode::Build && event->button() == Qt::MouseButton::RightButton) {

        resetCursorMode();

     }

     if(currentCursorMode == CursorMode::SetWorker && event->button() == Qt::MouseButton::RightButton) {

        resetCursorMode();

     }


     QMainWindow::mousePressEvent(event);
}

void MapWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "tallennetaan peli";
    m_gameEventHandler.lock()->saveGame();
    QMainWindow::closeEvent(event);
}

void MapWindow::resetCursorMode() {
    qDebug() << "reset cursor mode";
    currentCursorMode = CursorMode::Normal;
    m_simplescene->currentCursorMode = CursorMode::Normal;
    m_simplescene->currentBuildTarget = CursorInsertTarget::NONE;
    QApplication::restoreOverrideCursor();
    this->updateProductionContext();
    updateWorkerLabels();
    updateWorkerButtons(m_gameEventHandler.lock()->getCurrentPlayer());
    this->setCursor(Qt::ArrowCursor);
    updatePlayerContext(m_gameEventHandler.lock()->getCurrentPlayer());
    m_simplescene->update();
}

void MapWindow::updateWorkerLabels()
{
    std::pair<int,int> workerAvailability = m_gameEventHandler.lock()->getWorkerAvailability();
    m_ui->workersAvailableLabel->setText((QString::number(workerAvailability.first)));
    m_ui->workersMaxLabel->setText(QString::number(workerAvailability.second));
}


