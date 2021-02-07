#include "game.h"
#include "ui_game.h"
#include "chessfield.h"
#include "chessboard.h"
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

void Game::addToWindow(QGraphicsItem *item){

}

void Game::removeFromWindow(QGraphicsItem *item){

}

void Game::on_playButton_clicked()
{

    chessboard *chessBoardPtr = new chessboard(NULL,1920,1080,80);

    chessBoardPtr->show();


    //set up pawns
    //show menu

}

void Game::on_exitButton_clicked()
{
    // close application
    this->close();
}
