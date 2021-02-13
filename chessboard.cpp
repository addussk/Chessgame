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

void chessboard::setTurn(QString team){
    turn = team;
}

QString chessboard::getTurn(){
    return turn;
}

void chessboard::changeTurn(){
    turn = turn == "white" ? "black" : "white";
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
            field->setPos(SHIFT*c,SHIFT*r);

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
