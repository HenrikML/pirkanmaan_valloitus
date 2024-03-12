#ifndef DIALOGGAMESTART_H
#define DIALOGGAMESTART_H

#include <QDialog>

namespace Ui {
/**
 * @brief DialogGameStart class is a dialog used for setting up the game.
 */
class DialogGameStart;
}

struct GameStartSettings {
    int playerCount;
    std::vector<std::string> playerNames;
    std::pair<int,int> mapSize;
};

class DialogGameStart : public QDialog
{
    Q_OBJECT

public:
    GameStartSettings getGameSettings();
    explicit DialogGameStart(QWidget *parent = nullptr);
    /**
     * @brief Destructor.
     */
    ~DialogGameStart();

private:
    Ui::DialogGameStart *ui;
    GameStartSettings m_gameSettings;

    // QDialog interface

private slots:
    void on_exitGameBtn_clicked();
    void on_startGameBtn_clicked();
};

#endif // DIALOGGAMESTART_H
