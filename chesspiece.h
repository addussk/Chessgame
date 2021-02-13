#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "chessfield.h"

class ChessField;
class ChessPiece: public QGraphicsPixmapItem{
public:
    ChessPiece(QString team="", QGraphicsItem* parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    // odczytujemy kolor bierki
    QString getSide();
    // ustawiamy kolor bierki
    void setSide(QString);
    // ustawiamy do bierki pole na ktorym aktualnie sie znajduje
    void setCurrentBox(ChessField* field);
    // Otrzymujemy wskaznik na pole na ktorym jest bierka
    ChessField* getCurrentBox();
    // funkcja odpowiedzialna za ruch pionem
    virtual void moves();
    //zmienic nazwe
    bool fieldSetting(ChessField* field);
    //
    void decolor();
    QList<ChessField*> moveLocation();
    bool firstMove;
    //
    void setIsPlaced(bool value);
    bool getIsPlaced();

protected:
    QString side;
    bool isPlaced;
    ChessField* currentBox;
    QList <ChessField*> location;
};


class Pawn:public ChessPiece
{
public:
    Pawn(QString team,QGraphicsItem *parent = 0);
    void setImage();
    virtual void moves();

 private:


};

class Rook:public ChessPiece{
public:
    Rook(QString team,QGraphicsItem *parent = 0);
    void setImage();
    void moves();

 private:
};

class Knight:public ChessPiece{
public:
    Knight(QString team,QGraphicsItem *parent = 0);
    void setImage();
    void moves();

 private:
};

class Bishop:public ChessPiece{
public:
    Bishop(QString team,QGraphicsItem *parent = 0);
    void setImage();
    void moves();

 private:
};

class Queen:public ChessPiece{
public:
    Queen(QString team,QGraphicsItem *parent = 0);
    void setImage();
    void moves();

 private:
};

class King:public ChessPiece{
public:
    King(QString team,QGraphicsItem *parent = 0);
    void setImage();
    void moves();

 private:
};

#endif // CHESSPIECE_H
