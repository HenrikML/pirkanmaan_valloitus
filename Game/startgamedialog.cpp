#include "startgamedialog.h"
#include "ui_startGameDialog.h"

StartGameDialog::StartGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartGameDialog)
{
    ui->setupUi(this);
}

StartGameDialog::~StartGameDialog()
{
    delete ui;
}
