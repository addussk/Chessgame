#include "chesspiece.h"
#include <QDebug>
#include "game.h"

extern Game* game;

ChessPiece::ChessPiece(QString team, QGraphicsItem* parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<< "ChessPiece::mousePressEvent ";
    //Deselect mode
    if(this == game->chessboardPtr->pieceToMove){
        qDebug()<< "ChessPiece::mousePressEvent: Deselect!";
        game->chessboardPtr->pieceToMove->decolor();
        game->chessboardPtr->pieceToMove->getCurrentBox()->resetOrginalColor();
        game->chessboardPtr->pieceToMove = NULL;
        return;
    }

    // Pomijamy ruch gdy gracz probuje wybrac piona koloru ktoremu nie przypada ruch lub gdy wybiera puste pole
    if( (!this->getIsPlaced()) || ((game->chessboardPtr->getTurn() != this->side) && (!game->chessboardPtr->pieceToMove)) ){
        qDebug()<< "ChessPiece::mousePressEvent: Nie twoja kolej, rusza przeciwnik!";
        return;
    }

    //Gdy gracz wybiera piona ktorym chce ruszyc.
    if(NULL == game->chessboardPtr->pieceToMove){
        qDebug()<< "ChessPiece::mousePressEvent Pionek zostal wybrany ";
        //Przypisz wybrany pionek jako gotowy do ruchu
        game->chessboardPtr->pieceToMove = this;
        //Zmieniamy kolor pola na ktorym stoi wybrany pion
        game->chessboardPtr->pieceToMove->getCurrentBox()->setColor(Qt::darkBlue);
        // pokaz mozliwe pola
        game->chessboardPtr->pieceToMove->moves();
    }
    // Gdy pion ktorym ruszamy jest wybrany, nastepnie wykonujemy zbicie piona przeciwnego koloru
    else if(this->getSide() != game->chessboardPtr->pieceToMove->getSide()){
        qDebug()<< "ChessPiece::mousePressEvent Nastepuje bicie";
        this->getCurrentBox()->mousePressEvent(event);
    }

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

QList<ChessField*> ChessPiece::moveLocation(){
    return location;
}

void ChessPiece::decolor(){
    for(size_t i=0, n=location.size(); i<n; i++){
        location[i]->resetOrginalColor();
    }
}

//zmienic nazwe
bool ChessPiece::fieldSetting(ChessField *field){

    if(field->getHasChessPiece()){

        King* ptr = dynamic_cast<King*>(location.last()->currentPiece);

        if(ptr){
            field->setColor(Qt::blue);
        }else{
            field->setColor(Qt::red);
        }
        return true;

    }else{
        location.last()->setColor(Qt::darkBlue);
    }
    return false;
}

void ChessPiece::moves(){
    qDebug() << "Move function in ChessPiece ";
}

void ChessPiece::setIsPlaced(bool value){
    isPlaced = value;
}

bool ChessPiece::getIsPlaced(){
    return isPlaced;
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

    location.clear();

    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;

    qDebug() << row << col;

    if(this->getSide() == "white"){
        qDebug() << "White Pawn is moving ";
        //Ruch do przodu bialym pionem
        if( row >0 && (!game->chessboardPtr->collection[row-1][col]->getHasChessPiece())){
            location.append(game->chessboardPtr->collection[row-1][col]);
            fieldSetting(location.last());
            // Jesli pionek ma pierwszy ruch, moze ruszyc sie o 2 pole, gdy nie ma nic przed nim
            if(this->firstMove && (!game->chessboardPtr->collection[row-2][col]->getHasChessPiece())){
                location.append(game->chessboardPtr->collection[row-2][col]);
                fieldSetting(location.last());
            }
        }
        // Zbicia pionem na lewo i prawo
        if(col > 0 && row>0 && game->chessboardPtr->collection[row-1][col-1]->getColorOfPiece() == "Black"){
            location.append(game->chessboardPtr->collection[row-1][col-1]);
            fieldSetting(location.last());
        }
        if(col <7  && row>0 && game->chessboardPtr->collection[row-1][col+1]->getColorOfPiece() == "Black"){
            location.append(game->chessboardPtr->collection[row-1][col+1]);
            fieldSetting(location.last());
        }

    }else{
        qDebug() << "Black Pawn is moving ";
        //Ruch do przodu czarnym pionem
        if( row <7 && (!game->chessboardPtr->collection[row+1][col]->getHasChessPiece())){
            location.append(game->chessboardPtr->collection[row+1][col]);
            fieldSetting(location.last());
            // Jesli pionek ma pierwszy ruch, moze ruszyc sie o 2 pole, gdy nie ma nic przed nim
            if(this->firstMove && (!game->chessboardPtr->collection[row+2][col]->getHasChessPiece())){
                location.append(game->chessboardPtr->collection[row+2][col]);
                fieldSetting(location.last());
            }
        }
        // Zbicia pionem na lewo i prawo
        if(col > 0 && row<7 && game->chessboardPtr->collection[row-1][col-1]->getColorOfPiece() == "Black"){
            location.append(game->chessboardPtr->collection[row+1][col-1]);
            fieldSetting(location.last());
        }
        if(col <7  && row<7 && game->chessboardPtr->collection[row-1][col+1]->getColorOfPiece() == "Black"){
            location.append(game->chessboardPtr->collection[row+1][col+1]);
            fieldSetting(location.last());
        }
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

void Rook::moves(){

    location.clear();

    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

    qDebug() << "Move function in Rook " << row << col;

    // Ruch do przodu
    for(int i = row-1,j = col; i >= 0 ; i--) {
       if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
           break;
       }
       else
       {
           location.append(game->chessboardPtr->collection[i][j]);
           if(fieldSetting(location.last()))
               break;
        }
    }

    // Ruch w dol
    for(int i = row+1,j = col; i <= 7 ; i++) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
            break;
        }
        else
        {
            location.append(game->chessboardPtr->collection[i][j]);
            if(fieldSetting(location.last())){
                break;
            }
        }
    }

    // Ruch w prawo
    for(int i = row,j = col+1; j <= 7 ; j++)
    {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
          break;
        }
        else
        {
          location.append(game->chessboardPtr->collection[i][j]);
          if(fieldSetting(location.last()))
              break;
        }

   }

    // Ruch w lewo
    for(int i = row,j = col-1; j >= 0 ; j--) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
         break;
        }
        else
        {
         location.append(game->chessboardPtr->collection[i][j]);
         if(fieldSetting(location.last()))
            break;
        }
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

void Knight::moves(){

    location.clear();

    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
    int i ,j;

    qDebug() << "Move function in Knight" << row << col;

    // W przypadku gonca rozwazamy 8 miejsc:
    // Up Up Left
    i = row - 2;
    j = col - 1;
    if(i >=0 && j>=0 && (game->chessboardPtr->collection[i][j]->getColorOfPiece() != team) ) {
        location.append(game->chessboardPtr->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::blue);
    }

    // Up Up Right
    i = row - 2;
    j = col + 1;
    if(i >=0 && j<=7 && (game->chessboardPtr->collection[i][j]->getColorOfPiece() != team) ) {
        location.append(game->chessboardPtr->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::blue);
    }

    // Down Down Left
    i = row + 2;
    j = col - 1;
    if(i <= 7 && j>=0 && (game->chessboardPtr->collection[i][j]->getColorOfPiece() != team) ) {
        location.append(game->chessboardPtr->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::blue);
    }

    // Down Down Right
    i = row + 2;
    j = col + 1;
    if(i <=7 && j<=7 && (game->chessboardPtr->collection[i][j]->getColorOfPiece() != team) ) {
        location.append(game->chessboardPtr->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::blue);
    }

    // Left Left Up
    i = row - 1;
    j = col - 2;
    if(i >=0 && j>=0 && (game->chessboardPtr->collection[i][j]->getColorOfPiece() != team) ) {
        location.append(game->chessboardPtr->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::blue);
    }

    // Left Left Down
    i = row + 1;
    j = col - 2;
    if(i <=7 && j>=0 && (game->chessboardPtr->collection[i][j]->getColorOfPiece() != team) ) {
        location.append(game->chessboardPtr->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::blue);
    }

    // Rigt Right Up
    i = row - 1;
    j = col + 2;
    if(i >=0 && j<=7 && (game->chessboardPtr->collection[i][j]->getColorOfPiece() != team) ) {
        location.append(game->chessboardPtr->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::blue);
    }

    // Right Right Down
    i = row + 1;
    j = col +  2;
    if(i <=7 && j<=7 && (game->chessboardPtr->collection[i][j]->getColorOfPiece() != team) ) {
        location.append(game->chessboardPtr->collection[i][j]);
        if(location.last()->getHasChessPiece())
            location.last()->setColor(Qt::yellow);
        else
            location.last()->setColor(Qt::blue);
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

void Bishop::moves(){
    location.clear();

    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

    qDebug() << "Move function in Bishop:" << row << col;

    // Lewy gorny wierzcholek
    for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
           break;

        }
        else {
           location.append(game->chessboardPtr->collection[i][j]);
           if(fieldSetting(location.last()) ){
               break;
           }
        }
    }

    // Prawy gorny wierzcholek
    for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
            break;

        }
        else
        {
            location.append(game->chessboardPtr->collection[i][j]);
            if(fieldSetting(location.last())){
                break;
            }
        }
    }

    // Prawy dolny wierzcholek

    for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
            break;
        }
        else {
            location.append(game->chessboardPtr->collection[i][j]);
            if(fieldSetting(location.last())){
                break;
            }
        }
    }

    // Lewy dolny wierzcholek

    for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
            break;
        }
        else {
            location.append(game->chessboardPtr->collection[i][j]);
            if(fieldSetting(location.last())){
              break;
            }
        }
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

void Queen::moves(){
    location.clear();

    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

    qDebug() << "Move function in Queen " << row << col;

    // Lewy gorny wierzcholek
    for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
           break;

        }
        else {
           location.append(game->chessboardPtr->collection[i][j]);
           if(fieldSetting(location.last()) ){
               break;
           }
        }
    }

    // Prawy gorny wierzcholek
    for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
            break;

        }
        else
        {
            location.append(game->chessboardPtr->collection[i][j]);
            if(fieldSetting(location.last())){
                break;
            }
        }
    }

    // Prawy dolny wierzcholek

    for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
            break;
        }
        else {
            location.append(game->chessboardPtr->collection[i][j]);
            if(fieldSetting(location.last())){
                break;
            }
        }
    }

    // Lewy dolny wierzcholek

    for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
            break;
        }
        else {
            location.append(game->chessboardPtr->collection[i][j]);
            if(fieldSetting(location.last())){
              break;
            }
        }
    }

    // Ruch do przodu
    for(int i = row-1,j = col; i >= 0 ; i--) {
       if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
           break;
       }
       else
       {
           location.append(game->chessboardPtr->collection[i][j]);
           if(fieldSetting(location.last()))
               break;
        }
    }

    // Ruch w dol
    for(int i = row+1,j = col; i <= 7 ; i++) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
            break;
        }
        else
        {
            location.append(game->chessboardPtr->collection[i][j]);
            if(fieldSetting(location.last())){
                break;
            }
        }
    }

    // Ruch w prawo
    for(int i = row,j = col+1; j <= 7 ; j++)
    {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
          break;
        }
        else
        {
          location.append(game->chessboardPtr->collection[i][j]);
          if(fieldSetting(location.last()))
              break;
        }

   }

    // Ruch w lewo
    for(int i = row,j = col-1; j >= 0 ; j--) {
        if(game->chessboardPtr->collection[i][j]->getColorOfPiece() == team ) {
         break;
        }
        else
        {
         location.append(game->chessboardPtr->collection[i][j]);
         if(fieldSetting(location.last()))
            break;
        }
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

void King::moves(){

    location.clear();

    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

    qDebug() << "Move function in King " << row << col;
    qDebug() << game->chessboardPtr->collection[row-1][col]->getColorOfPiece() << team;
    // Up
    if(row>0 && !(game->chessboardPtr->collection[row-1][col]->getColorOfPiece() == team)) {//up
        location.append(game->chessboardPtr->collection[row-1][col]);
        game->chessboardPtr->collection[row-1][col]->setColor(Qt::blue);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::yellow);
        }
    }

    // Down
    if(row<7 && !(game->chessboardPtr->collection[row+1][col]->getColorOfPiece() == team)) {//down
        location.append(game->chessboardPtr->collection[row+1][col]);
        game->chessboardPtr->collection[row+1][col]->setColor(Qt::blue);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::yellow);
        }
    }

    // Left
    if(col>0 && !(game->chessboardPtr->collection[row][col-1]->getColorOfPiece() == team)) {// left
        location.append(game->chessboardPtr->collection[row][col-1]);
        game->chessboardPtr->collection[row][col-1]->setColor(Qt::blue);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::yellow);
        }
    }

    // Right
    if(col<7 && !(game->chessboardPtr->collection[row][col+1]->getColorOfPiece() == team)) {//right
        location.append(game->chessboardPtr->collection[row][col+1]);
        game->chessboardPtr->collection[row][col+1]->setColor(Qt::blue);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::yellow);
        }
    }

    // Up Left
    if(col > 0 && row > 0 && !(game->chessboardPtr->collection[row-1][col-1]->getColorOfPiece() == team)) {
        location.append(game->chessboardPtr->collection[row-1][col-1]);
        game->chessboardPtr->collection[row-1][col-1]->setColor(Qt::blue);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::yellow);
        }
    }

    // Up Right
    if(col < 7 && row > 0 && !(game->chessboardPtr->collection[row-1][col+1]->getColorOfPiece() == team)) {
        location.append(game->chessboardPtr->collection[row-1][col+1]);
        game->chessboardPtr->collection[row-1][col+1]->setColor(Qt::blue);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::yellow);
        }
    }

    // Down Left
    if(col > 0 && row < 7  && !(game->chessboardPtr->collection[row+1][col-1]->getColorOfPiece() == team)) {
        location.append(game->chessboardPtr->collection[row+1][col-1]);
        game->chessboardPtr->collection[row+1][col-1]->setColor(Qt::blue);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::yellow);
        }
    }

    // Down Right
    if(col < 7 && row < 7 && !(game->chessboardPtr->collection[row+1][col+1]->getColorOfPiece() == team)) {
        location.append(game->chessboardPtr->collection[row+1][col+1]);
        game->chessboardPtr->collection[row+1][col+1]->setColor(Qt::blue);
        if(location.last()->getHasChessPiece()){
            location.last()->setColor(Qt::yellow);
        }
    }


}
