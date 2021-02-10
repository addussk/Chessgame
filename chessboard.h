#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "chessfield.h"
#include "chesspiece.h"

namespace Ui {
class chessboard;
}

class chessboard : public QMainWindow
{
    Q_OBJECT

public:
    // Konstruktory
    explicit chessboard(QWidget *parent = nullptr);
    chessboard(QWidget*, int,int,int);

    // Destruktor
    ~chessboard();

    // Methods
    QBrush setColor(QColor, QBrush);
    void drawBoard(int);
    void setUpPieces(QString team);
    void placeOnBoard();

protected:
    int sizeField;

    //coordinates
    ChessField *collection[8][8];
    // lista z pionkami majace zycia
    QList <ChessPiece *> alivePiece;

private:
    Ui::chessboard *ui;
    QGraphicsScene *boardScene;
    int widthWindow;
    int hightWindow;
    QList <ChessPiece *> white;
    QList <ChessPiece *> black;
};

#endif // CHESSBOARD_H
