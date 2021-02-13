#include <QDebug>
#include "chessfield.h"
#include "chesspiece.h"
#include "game.h"

extern Game* game;
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
    qDebug()<< "ChessField::mousePressEvent ";
    //Jesli gracz wybral pionka ktorym chce ruszyc
    if(game->chessboardPtr->pieceToMove){
        // W przypadku gdy wybierzemy pionka z naszej druzyny
        if(this->chessPieceColor == game->chessboardPtr->pieceToMove->getSide()){
            return;
        }
        // reset pola na ktorym stoi pion
        game->chessboardPtr->pieceToMove->decolor();
        // dotyczy tylko pionkow
        game->chessboardPtr->pieceToMove->firstMove=false;

        if(this->getHasChessPiece()){
            this->currentPiece->setCurrentBox(NULL);
        }
        game->chessboardPtr->pieceToMove->getCurrentBox()->setHasChessPiece(false);
        game->chessboardPtr->pieceToMove->getCurrentBox()->currentPiece = NULL;
        game->chessboardPtr->pieceToMove->getCurrentBox()->resetOrginalColor();
        placePiece(game->chessboardPtr->pieceToMove, 80);
        game->chessboardPtr->pieceToMove = NULL;
        game->chessboardPtr->changeTurn();

    }

    // Jesli gracz wskazal pole na ktorym znajduje sie figura ktora zamierza ruszyc
    if(this->getHasChessPiece()){
        this->currentPiece->mousePressEvent(event);
    }


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

bool ChessField::getHasChessPiece(){
    return hasChessPiece;
}

void ChessField::placePiece(ChessPiece* piece, int lenEdge){
    piece->setPos(x()+ (lenEdge/2)-piece->pixmap().width()/2, y()+(lenEdge/2)-piece->pixmap().height()/2);
    piece->setCurrentBox(this);
    setHasChessPiece(true, piece);
    currentPiece = piece;

}

void ChessField::checkForCheck(){
//    int tmp =0;
//    QList <ChessPiece*> pList = game->chessboardPtr->alivePiece;

//    for(size_t i=0; i<pList.size(); i++){


//    }
}
