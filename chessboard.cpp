#include "chessboard.h"
#include "ui_chessboard.h"
#include "chesspiece.h"

chessboard::chessboard(QWidget *parent, int w_Window, int h_Window, int edgeLen ) :
    QMainWindow(parent),
    ui(new Ui::chessboard)
{
    ui->setupUi(this);

    // Dlugosc krawedzi poa
    this->sizeField = edgeLen;
    int tmp_edgeView = 8*edgeLen + 10;

    // Rozdzielczosc main window
    this->setFixedSize(w_Window,h_Window);

    // Stworzenie sceny na ktorej zostanie umieszczona szachownica
    boardScene = new QGraphicsScene(this);

    // Narysowanie pol na szachownicy
    drawBoard(edgeLen);

    placeOnBoard();


    // Dodanie widoku do obiektu centralwidget
    QGraphicsView* view = new QGraphicsView(ui->centralwidget);
    // Umieszczenie na obiekcie view, obiekt grapgicsScene
    view->setScene(boardScene);
    // Ustawienie polozenia obiektu, oraz wymiary(szerokosc, wysokosc)
    view->setGeometry(QRect(100, 200, tmp_edgeView, tmp_edgeView));
    // Ustawienie tla elementu graphics view
    view->setBackgroundBrush(setColor(Qt::black, Qt::SolidPattern));
    // Wyswietlenie go w oknie
    view->show();
}

chessboard::~chessboard()
{
    delete ui;
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

void chessboard::placeOnBoard(){

    setUpPieces("white");
    setUpPieces("black");
    int tmpIter = 0;

    for (qsizetype i = 0; i < white.size(); ++i){


        ChessPiece* ptrWhite = white.at(i);
        if( tmpIter<8 ){
            ptrWhite->setPos(sizeField*tmpIter, sizeField);
        }else if (tmpIter<16){
            ptrWhite->setPos(sizeField*(tmpIter-8), 0);
        }else{
            //error, throw exception
        }

        boardScene->addItem(ptrWhite);
        tmpIter+=1;
    }

    tmpIter = 0;

    for (qsizetype i = 0; i < black.size(); ++i){

        ChessPiece* ptrBlack = black.at(i);
        if( tmpIter<8 ){
            ptrBlack->setPos(sizeField*tmpIter, 6*sizeField);
        } else if(tmpIter<16){
            ptrBlack->setPos(sizeField*(tmpIter-8), 7*sizeField);
        }else{
            //error, throw exception
        }

        boardScene->addItem(ptrBlack);
        tmpIter+=1;
    }

}

void chessboard::drawBoard(int edgeLen){
    // Tworzenie szachownicy
    int SHIFT = this->sizeField;
    for(int r=0; r<8; r++){
        for (int c=0; c<8; c++) {
            // Stworzenie pojedynczego pola na szachownicy
            ChessField *field = new ChessField(NULL, edgeLen);
            coordinates[r][c] = field;

            //Ustawienie pozycji kazdego pola
            field->rowLoc = r;
            field->colLoc = c;
            field->setPos(SHIFT*r,SHIFT*c);

            if( (c+r)%2 == 0 ){
                field->setColor(Qt::lightGray);
            }
            else{
                field->setColor(Qt::darkRed);
            }

            // Umiesc pole w view
            boardScene->addItem(field);
        }
    }
}
