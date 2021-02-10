#ifndef CHESSFIELD_H
#define CHESSFIELD_H

#include <QBrush>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "chesspiece.h"

class ChessPiece;
class ChessField :public QGraphicsRectItem
{

public:
    // constructor
    ChessField(QGraphicsItem *parent = 0);
    ChessField(QGraphicsItem*parent = 0, int = 100);

    //desctructor
    ~ChessField();

    //public function
    // ustawia pole na kolor value
    void setColor(QColor value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void placePiece(ChessPiece* piece, int lenEdge);

    ChessPiece* currentPiece;
    // koordynaty pola na szachownicy
    int rowLoc;
    int colLoc;

private:
    QBrush brush;


};

#endif // CHESSFIELD_H
