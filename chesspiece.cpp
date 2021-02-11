#include "chesspiece.h"
#include <QDebug>

ChessPiece::ChessPiece(QString team, QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPaced = true;
    firstMove = true;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    this->currentBox->setColor(Qt::yellow);
    qDebug() << "jestem";
    this->moves();
    return;
}

void ChessPiece::setCurrentBox(ChessField* field){
    currentBox = field;
}

ChessField* ChessPiece::getCurrentBox(){
    return currentBox;
}

void ChessPiece::setSide(QString val){
    side = val;
}

QString ChessPiece::getSide(){
    return side;
}

void ChessPiece::moves(){
    qDebug() << "Move function in ChessPiece ";
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

void Pawn::moves(){
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;

    qDebug() << row << col;
    qDebug() << "Move function in Pawn ";


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

void Rook::moves(){
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;

    qDebug() << row << col;
    qDebug() << "Move function in Rook ";


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

void Knight::moves(){
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;

    qDebug() << row << col;
    qDebug() << "Move function in Knight";


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

void Bishop::moves(){
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;

    qDebug() << row << col;
    qDebug() << "Move function in Bishop";


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

void Queen::moves(){
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;

    qDebug() << row << col;
    qDebug() << "Move function in Queen ";


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

void King::moves(){
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;

    qDebug() << row << col;
    qDebug() << "Move function in King ";


}
