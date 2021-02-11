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
    void setOrginalColor(QColor color);
    void resetOrginalColor();
    // Przypisuje pole do koloru pionka ktory sie na nim znajduje
    void setColorOfPiece(QString);
    QString getColorOfPiece();
    void setHasChessPiece(bool value, ChessPiece* piece = 0);
    bool getHasChessPiece();
    //
    void checkForCheck();

    // Pionek znajdujacy sie na polu
    ChessPiece* currentPiece;
    // koordynaty pola na szachownicy
    int rowLoc;
    int colLoc;

private:
    QBrush brush;
    QColor originalColor;
    // kolor pionka na polu
    bool hasChessPiece;
    QString chessPieceColor;



};

#endif // CHESSFIELD_H
