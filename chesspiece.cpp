#include "chesspiece.h"
#include <QDebug>

ChessPiece::ChessPiece(QString team, QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPaced = true;
    firstMove = true;
}



// Pawn part
Pawn::Pawn(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    firstMove = true;
}

void Pawn::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap(":/resources/images/pawn1.png"));
    }else{
        setPixmap(QPixmap(":/resources/images/pawn.png"));
    }
}

// Rook part
Rook::Rook(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    firstMove = true;
}

void Rook::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap(":/resources/images/rook1.png"));
    }else{
        setPixmap(QPixmap(":/resources/images/rook.png"));
    }
}

// Knight part
Knight::Knight(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    firstMove = true;
}

void Knight::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap(":/resources/images/horse1.png"));
    }else{
        setPixmap(QPixmap(":/resources/images/horse.png"));
    }
}

// Bishop part
Bishop::Bishop(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    firstMove = true;
}

void Bishop::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap(":/resources/images/bishop1.png"));
    }else{
        setPixmap(QPixmap(":/resources/images/bishop.png"));
    }
}

// Queen part
Queen::Queen(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    firstMove = true;
}

void Queen::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap(":/resources/images/queen1.png"));
    }else{
        setPixmap(QPixmap(":/resources/images/queen.png"));
    }
}

// King part
King::King(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    firstMove = true;
}

void King::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap(":/resources/images/king1.png"));
    }else{
        setPixmap(QPixmap(":/resources/images/king.png"));
    }
}
