#include "chessfield.h"
#include <QDebug>

// constructor
ChessField :: ChessField(QGraphicsItem *parent, int sizeField) : QGraphicsRectItem(parent){
    int edge = sizeField;

    // create single field
    setRect(0,0,edge,edge);
    // use standard style for filling
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
    setColorOfPiece("NONE");
    currentPiece = NULL;

}

// destructor
ChessField :: ~ChessField(){
    delete this;
}

void ChessField::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    event->scenePos();
//    qDebug() << this->colLoc << " row: " << this->rowLoc;

//    if(currentPiece){
//        currentPiece->moves();
//    }

    return;
}

void ChessField :: setColor(QColor color){
    brush.setColor(color);
    setBrush(color);
}

void ChessField::setOrginalColor(QColor color){
    originalColor = color;
    setColor(color);
}

void ChessField::resetOrginalColor(){
    setColor(originalColor);
}

void ChessField::setColorOfPiece(QString team){
    chessPieceColor = team;
}

QString ChessField::getColorOfPiece(){
    return chessPieceColor;
}

void ChessField::setHasChessPiece(bool value, ChessPiece *piece){
    hasChessPiece = value;
    if(value){
        setColorOfPiece(piece->getSide());
    }else{
        setColorOfPiece("NONE");
    }
}

void ChessField::placePiece(ChessPiece* piece, int lenEdge){
    qDebug() << x()<< " " << piece->pixmap().height();
    piece->setPos(x()+ (lenEdge/2)-piece->pixmap().width()/2, y()+(lenEdge/2)-piece->pixmap().height()/2);
    piece->setCurrentBox(this);
    setHasChessPiece(true, piece);
    currentPiece = piece;

}
