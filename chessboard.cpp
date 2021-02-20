#include "chessboard.h"
#include "ui_chessboard.h"
#include "chesspiece.h"
#include <QAbstractScrollArea>

chessboard::chessboard(QWidget *parent, int w_Window, int h_Window, int edgeLen ) :
    QMainWindow(parent),
    ui(new Ui::chessboard)
{
    ui->setupUi(this);

    // Inicjalizacja dlugosci krawedzi 1 pola
    this->sizeField = edgeLen;

    // Ustawienie na stale wymiarow okna
    this->setFixedSize(w_Window, h_Window);

    // Dodanie widoku do obiektu centralwidget
    QGraphicsView* view = new QGraphicsView(ui->centralwidget);

    // Dezaktywowanie scrollbarow
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Stworzenie sceny na ktorej zostanie umieszczona szachownica
    this->boardScene = new QGraphicsScene(this);

    // Ustawienie tla elementu graphics view
    view->setBackgroundBrush(setColor(Qt::gray, Qt::SolidPattern));
    // Ustawienie na stale wielkosci okna
    view->setFixedSize(w_Window, h_Window);

    // Narysowanie pol na szachownicy
    drawBoard(edgeLen);

    addDeadHolder(QPoint(0,0), Qt::blue);
    addDeadHolder(QPoint(940,0), Qt::blue);
    
    placeOnBoard();

    this->whitePiece = new QGraphicsTextItem();
    this->blackPiece = new QGraphicsTextItem();
    this->turnDisplay = new QGraphicsTextItem();

    this->addTextItem(this->whitePiece, QPoint(80, 10),Qt::white, "WHITE PIECES", boardScene);
    this->addTextItem(this->blackPiece, QPoint(1020, 10),Qt::black, "BLACK PIECE", boardScene);
    this->addTextItem(this->turnDisplay, QPoint(width()/2-100,10),Qt::white, "Turn : WHITE", boardScene);

    // Umieszczenie na obiekcie view, obiekt grapgicsScene
    view->setScene(boardScene);

    // Wyswietlenie go w oknie
    view->show();
}

chessboard::~chessboard()
{
    delete ui;
}

void chessboard::addTextItem(QGraphicsTextItem* textItem, QPoint xy, QColor color, QString text, QGraphicsScene* pToScene){

    textItem->setPos(xy);
    textItem->setZValue(1);
    textItem->setDefaultTextColor(color);
    textItem->setFont(QFont("",18));
    textItem->setPlainText(text);
    pToScene->addItem(textItem);

}

void chessboard::addDeadHolder(QPoint xy, QColor color ){

    deadHolder = new QGraphicsRectItem(xy.x(), xy.y(), 300, 800);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    deadHolder->setBrush(brush);
    this->boardScene->addItem(deadHolder);
}

QBrush chessboard::setColor(QColor color, QBrush brush){
    brush.setColor(color);
    return brush;
}

void chessboard::setUpPieces(QString team){
    ChessPiece *piece;
    QList<ChessPiece*> *pVector;

    if(team == "white"){
        pVector = &white;
    }else if(team == "black"){
        pVector = &black;
    }

    // Ustawienie pionkow dla danego koloru
    for (int i=0; i<8; i++){
        piece = new Pawn(team);
        pVector->append(piece);
    }

    piece = new Rook(team);
    pVector->append(piece);
    piece = new Knight(team);
    pVector->append(piece);
    piece = new Bishop(team);
    pVector->append(piece);
    piece = new Queen(team);
    pVector->append(piece);
    piece = new King(team);
    pVector->append(piece);
    piece = new Bishop(team);
    pVector->append(piece);
    piece = new Knight(team);
    pVector->append(piece);
    piece = new Rook(team);
    pVector->append(piece);

}

void chessboard::setTurn(QString team){
    turn = team;
}

QString chessboard::getTurn(){
    return turn;
}

void chessboard::changeTurn(){
    turn = turn == "white" ? "black" : "white";
    QColor color = turn == "white" ? Qt::white : Qt::black;

    this->turnDisplay->setDefaultTextColor(color);

    this->turnDisplay->setPlainText("Turn: " + getTurn().toUpper());
}

void chessboard::placeOnBoard(){

    setUpPieces("white");
    setUpPieces("black");
    this->pieceToMove = NULL;
    // Rozpoczyna gracz bialymi
    this->setTurn("white");
    
    int tmp_whiteIter = 0;
    int tmp_blackIter = 15;

    for(int i = 0; i<8; i++){
        for(int j=0; j<8; j++){

            ChessField* field = collection[i][j];
            if(i<2){
                field->placePiece(black[tmp_blackIter], this->sizeField);
                alivePiece.append(black[tmp_blackIter]);
                boardScene->addItem(black[tmp_blackIter--]);
            }

            if(i>5){
                field->placePiece(white[tmp_whiteIter], this->sizeField);
                alivePiece.append(white[tmp_whiteIter]);
                boardScene->addItem(white[tmp_whiteIter++]);
            }
        }
    }
}

void chessboard::drawBoard(int edgeLen){
    // Tworzenie szachownicy
    int SHIFT = this->sizeField;
    for(int c=0; c<8; c++){
        for (int r=0; r<8; r++) {
            // Stworzenie pojedynczego pola na szachownicy
            ChessField *field = new ChessField(NULL, edgeLen);
            this->collection[r][c] = field;

            //Ustawienie pozycji kazdego pola
            field->rowLoc = r;
            field->colLoc = c;
            field->setPos(300+SHIFT*c,100+SHIFT*r);

            if( (c+r)%2 == 0 ){
                field->setOrginalColor(Qt::lightGray);
            }
            else{
                field->setOrginalColor(Qt::darkRed);
            }

            // Umiesc pole w view
            boardScene->addItem(field);
        }
    }
}
