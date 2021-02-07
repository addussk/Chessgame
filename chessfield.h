#ifndef CHESSFIELD_H
#define CHESSFIELD_H

#include <QBrush>
#include <QGraphicsRectItem>

class ChessField :public QGraphicsRectItem
{

public:
    // constructor
    ChessField(QGraphicsItem *parent = 0);
    ChessField(QGraphicsItem*parent = 0, int = 100);

    //desctructor
    ~ChessField();

    void setColor(QColor value);

    int rowLoc;
    int colLoc;

private:
    QBrush brush;


};

#endif // CHESSFIELD_H
