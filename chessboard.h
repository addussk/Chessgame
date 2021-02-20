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
    void checkForCheck();
    void addTextItem(QGraphicsTextItem* textItem, QPoint xy, QColor color, QString text, QGraphicsScene* pToScene);

    QString getTurn();
    void setTurn(QString);
    void changeTurn();

    // lista z pionkami majace zycia
    QList <ChessPiece*> alivePiece;
    // wskaznik na pionek ktory zostal zaznaczony
    ChessPiece* pieceToMove;
    //coordinates
    ChessField* collection[8][8];
    //
    QGraphicsTextItem *check;

private:
    Ui::chessboard* ui;
    QGraphicsScene* boardScene;

    QGraphicsTextItem* turnDisplay;
    QGraphicsRectItem* deadHolder;

    QGraphicsTextItem* whitePiece;
    QGraphicsTextItem* blackPiece;

    int widthWindow;
    int hightWindow;
    QList <ChessPiece*> white;
    QList <ChessPiece*> black;
    // dlugosc krawedzi pola na szachownicy
    int sizeField;
    // Wskazuje na kolor ktorego jest kolej
    QString turn;
};

#endif // CHESSBOARD_H
