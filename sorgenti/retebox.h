#ifndef RETEBOX_H
#define RETEBOX_H
#include "controller.h"
#include <QWidget>
#include <QtWidgets>

class ReteBox: public QWidget
{
    Q_OBJECT

private:
    Controller* controller;
    QScrollArea* scrollArea;
    QGridLayout * griglia;
    QTextEdit * infoText;
    vector<QLabel*> contatto;
    vector<QPushButton*> infoButton;
    vector<QPushButton*> elimina;
    int currentRow, currentColumn, rowCount;
    void creaGrigliaContatti();
public:
    ReteBox(Controller* controller);
    void aggiorna();
private slots:
    void mostraInfo();
    void rimuovi();
};

#endif // RETEBOX_H
