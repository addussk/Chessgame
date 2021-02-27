#include <QDebug>
#include "chessfield.h"
#include "chesspiece.h"
#include "game.h"

extern Game* game;
// constructor
ChessField :: ChessField(QGraphicsItem *parent, int sizeField) : QGraphicsRectItem(parent){
    // create single field
    setRect(0,0,sizeField,sizeField);
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
    // Gdy gracz klika drugi raz na tego samego piona
    if((this->currentPiece == game->chessboardPtr->pieceToMove) && this->currentPiece){
        currentPiece->mousePressEvent(event);
        return;
    }
    //Jesli gracz wybral pionka ktorym chce ruszyc
    if(nullptr != game->chessboardPtr->pieceToMove){
        // W przypadku gdy wybierzemy pionka z naszej druzyny
        if(this->chessPieceColor == game->chessboardPtr->pieceToMove->getSide()){
            return;
        }
        //removing the eaten piece
        QList <ChessField*> movLoc = game->chessboardPtr->pieceToMove->moveLocation();
        //TO make sure the selected box is in move zone
        int check = 0;
        for(size_t i = 0, n = movLoc.size(); i < n;i++) {
            if(movLoc[i] == this) {
                check++;
            }
        }
        // if not prsent return
        if(check == 0)
            return;
        // reset pola na ktorym stoi pion
        game->chessboardPtr->pieceToMove->decolor();
        // dotyczy tylko pionkow
        game->chessboardPtr->pieceToMove->firstMove=false;

        if(this->getHasChessPiece()){
            this->currentPiece->setIsPlaced(false);
            this->currentPiece->setCurrentBox(NULL);
            game->chessboardPtr->placeInDeadPlace(this->currentPiece);
        }

        game->chessboardPtr->pieceToMove->getCurrentBox()->setHasChessPiece(false);
        game->chessboardPtr->pieceToMove->getCurrentBox()->currentPiece = NULL;
        game->chessboardPtr->pieceToMove->getCurrentBox()->resetOrginalColor();
        this->placePiece(game->chessboardPtr->pieceToMove, 80);
        game->chessboardPtr->pieceToMove = NULL;
        game->chessboardPtr->changeTurn();
        this->checkForCheck();
    }

    // Jesli gracz wskazal pole na ktorym znajduje sie figura ktora zamierza ruszyc
    else if(this->getHasChessPiece()){
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
    int tmp =0;
    QList <ChessPiece*> pList = game->chessboardPtr->alivePiece;

    for(size_t i=0, n=pList.size(); i<n ; i++){
        King* ptr = dynamic_cast<King*>(pList[i]);

        // dodac do ifa spr czy alivePiece zawiera na pewno zyjacego pionka lub ugarnac usuwanie
        if( NULL!=ptr ){
            continue;
        }else{
            //pList[i]->moves();
            pList[i]->decolor();

            QList <ChessField*> bList = pList[i]->moveLocation();

            for(size_t j=0, n = bList.size(); j < n; j++){
                ptr = dynamic_cast<King*>(bList[j]->currentPiece);

                if( NULL!=ptr ){
                    if(ptr->getSide() == pList[i]->getSide()){
                        continue;
                    }else{
                        bList[j]->setColor(Qt::blue);
                        pList[i]->getCurrentBox()->setColor(Qt::green);

                        if(!game->chessboardPtr->check->isVisible()){
                            game->chessboardPtr->check->setVisible(true);
                        }else{
                            bList[j]->resetOrginalColor();
                            pList[i]->getCurrentBox()->resetOrginalColor();
                            //game->gameOver();
                        }
                        tmp++;
                    }
                }
            }
        }


    }

    if(0 == tmp){
        game->chessboardPtr->check->setVisible(false);
    }
}
