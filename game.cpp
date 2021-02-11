#include "game.h"
#include "ui_game.h"
#include <QDebug>

Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
}

Game::~Game()
{
    delete ui;
}


void Game::on_playButton_clicked()
{
    this->chessboardPtr = new chessboard(NULL,1400,1000,80);
    chessboardPtr->show();
    //set up pawns
    //show menu

}

void Game::on_exitButton_clicked()
{
    // close application
    this->close();
}
