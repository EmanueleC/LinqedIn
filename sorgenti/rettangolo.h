#ifndef RETTANGOLO_H
#define RETTANGOLO_H
#include <QWidget>
#include <QtWidgets>

class Rettangolo: public QWidget
{
private:
    bool mode; // true se modalità client, false se modalità admin
public:
    Rettangolo(bool ,QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent* e);
};

#endif // RETTANGOLO_H
