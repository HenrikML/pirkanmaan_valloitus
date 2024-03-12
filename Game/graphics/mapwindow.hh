#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <map>
#include "graphics/mapitem.h"
#include "objectbutton.h"

#include "graphics/simplegamescene.h"
#include "gamescene.h"
#include "gamestate.h"


namespace Ui {
class MapWindow;

}
class GameEventHandler;


/**
 * @brief The MapWindow class is the main window of the game.
 */
class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0,     
                       int width = 8,
                       int height = 8,
                       const std::shared_ptr<GameEventHandler>& ghandler = {}
                       );
    ~MapWindow();

    void setGEHandler(const std::shared_ptr<GameEventHandler>& nHandler);


    void updateGameScene();
 //   void drawItem( std::shared_ptr<Course::GameObject> obj, std::pair<CursorInsertMode, CursorInsertTarget> type);

    void updatePlayerContext(const std::weak_ptr<Player>& curPlayer);
    void resetCursorMode();

    void updateWorkerLabels();
    void setGameStateContext(const std::shared_ptr<GameState> &gameState);
    void updateProductionContext();

    void setGameMessage(std::string message);

    void setCostLabels(Course::ResourceMap resourceMap);
    void setWorkerLabels(int row, Course::ResourceMapDouble productionMap);
    void resetCostLabels();
    ObjectButton* createObjectButton(QString label, Course::ResourceMap resourceMap, QString = "");

    void updateWorkerButtons(const std::shared_ptr<Player> &player);
public slots:
    void drawItem(std::shared_ptr<Course::GameObject> obj, std::pair<CursorInsertMode, CursorInsertTarget> type, MapItem* parentTile = nullptr);
private slots:
    void on_endTurnBtn_clicked();

private:
    Ui::MapWindow* m_ui;
    std::weak_ptr<GameEventHandler> m_gameEventHandler;
    std::shared_ptr<GameScene> m_simplescene = nullptr;

    CursorMode currentCursorMode = CursorMode::Normal;

    //updates build buttons, compares current resources
    //and either disables or enables button
    void updateBuildButtons(const std::weak_ptr<Player>& curPlayer);

    void setBuildingMode(CursorInsertTarget mouseCursorIcon);
    void setInsertWorkerMode(CursorInsertTarget workerType);

    ObjectButton *buildHQBtn, *buildFarmBtn, *buildOutpostBtn, *buildFishingHutBtn, *buildEObtn, *buildLMBtn, *buildQuarryBtn, *buildMineBtn;
    ObjectButton *buildFarmerBtn, *buildFisherBtn,  *buildLumberjackBtn, *buildMinerBtn, *buildStonemasonBtn;


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MapWINDOW_HH

