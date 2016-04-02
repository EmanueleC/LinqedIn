#ifndef TITOLISTUDIOBOX_H
#define TITOLISTUDIOBOX_H
#include "controller.h"
#include <QWidget>
#include <QtWidgets>

class TitoliStudioBox: public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
    QGridLayout* layout;
    QSpinBox* dataTitolo[3];
    QTextEdit* descrizioneTitolo;
    QLineEdit* titolo, *istituzione, *areaStudio;
    QPushButton *prec, *succ, *cancella;
    vector<QString> Titoli;
    vector<QString> istituzioni;
    vector<QString> areeStudio;
    vector<QString> descrizioniTitoli;
    vector<int> dateTitoli;
    unsigned int current;
public:
    TitoliStudioBox(Controller*);
    vector<QString> getDescrizioniTitoli() const;
    vector<QString> getTitoli() const;
    vector<QString> getIstituzioni() const;
    vector<QString> getAreeStudio() const;
    vector<int> getDate() const;
    void setTitoliBox(vector<QString>, vector<QString>, vector<QString>, vector<QString>, vector<int>, bool);
private slots:
    void successivo();
    void precedente();
    void cancellaCurrent();
};

#endif // TITOLISTUDIOBOX_H
