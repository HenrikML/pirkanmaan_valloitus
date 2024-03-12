#ifndef DIALOGGAMEEND_H
#define DIALOGGAMEEND_H

#include <QDialog>
#include <vector>
#include "player.h"

/**
  @brief The DialogGameEnd class is a dialog shown at the end of the game. It displays
  the players' stats and shows who the winner is.
  */

//typedef std::map<Course::BasicResource, int> PlayerResource;
namespace Ui {
class DialogGameEnd;
}

class DialogGameEnd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGameEnd(QWidget *parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~DialogGameEnd();

    void setStats(const std::shared_ptr<std::vector<std::shared_ptr<Player>>> playerList,
                  std::vector<std::shared_ptr<Course::TileBase>> tileList);
    void addLabel(int row, int column, QString text);
    void setWinnerText();


private:
    Ui::DialogGameEnd *ui;
    int m_maxPoints;
    std::vector<std::string> m_winners;

private slots:
    void on_exitBtn_clicked();
};

#endif // DIALOGGAMEEND_H
