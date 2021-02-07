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
    // setHasChessPiece(false);
    // setChessPieceColor("NONE");
    // currentPiece = NULL;

}

// destructor
ChessField :: ~ChessField(){
    delete this;
}


void ChessField :: setColor(QColor color){
    brush.setColor(color);
    setBrush(color);
}
