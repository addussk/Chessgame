#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "chessboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

    chessboard* chessboardPtr;

private slots:
    void on_playButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::Game *ui;
};
#endif // GAME_H
