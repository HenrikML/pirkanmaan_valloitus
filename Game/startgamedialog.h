#ifndef STARTGAMEDIALOG_H
#define STARTGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class StartGameDialog;
}

class StartGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartGameDialog(QWidget *parent = nullptr);
    ~StartGameDialog();

private:
    Ui::StartGameDialog *ui;
};

#endif // STARTGAMEDIALOG_H
