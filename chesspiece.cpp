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
    // spr czy mozna usunac
    firstMove = true;
}

void Pawn::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap("F:/Chess-master/pawn1.png"));
    }else{
        setPixmap(QPixmap("F:/Chess-master/pawn.png"));
    }
}

// Rook part
Rook::Rook(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    // spr czy mozna usunac
    firstMove = true;
}

void Rook::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap("F:/Chess-master/rook1.png"));
    }else{
        setPixmap(QPixmap("F:/Chess-master/rook.png"));
    }
}

// Knight part
Knight::Knight(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    // spr czy mozna usunac
    firstMove = true;
}

void Knight::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap("F:/Chess-master/horse1.png"));
    }else{
        setPixmap(QPixmap("F:/Chess-master/horse.png"));
    }
}

// Bishop part
Bishop::Bishop(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    // spr czy mozna usunac
    firstMove = true;
}

void Bishop::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap("F:/Chess-master/bishop1.png"));
    }else{
        setPixmap(QPixmap("F:/Chess-master/bishop.png"));
    }
}

// Queen part
Queen::Queen(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    // spr czy mozna usunac
    firstMove = true;
}

void Queen::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap("F:/Chess-master/queen1.png"));
    }else{
        setPixmap(QPixmap("F:/Chess-master/queen.png"));
    }
}

// King part
King::King(QString team, QGraphicsItem* parent):ChessPiece(team,parent){
    setImage();
    // spr czy mozna usunac
    firstMove = true;
}

void King::setImage(){

    if(ChessPiece::side == "white"){
        setPixmap(QPixmap("F:/Chess-master/king1.png"));
    }else{
        setPixmap(QPixmap("F:/Chess-master/king.png"));
    }
}
