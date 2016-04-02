#ifndef ESPLAVOROBOX_H
#define ESPLAVOROBOX_H
#include <QWidget>
#include <QtWidgets>
#include "controller.h"

class EspLavoroBox: public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
    QGridLayout* layout;
    QSpinBox* dateEsp[6];
    QTextEdit* esperienze;
    QLineEdit* luogo, *azienda;
    QPushButton *prec, *succ, *cancella;
    vector<QString> luoghi;
    vector<QString> aziende;
    vector<QString> esp;
    vector<int> date;
    unsigned int current;
public:
    EspLavoroBox(Controller*);
    vector<QString> getEsp() const;
    vector<QString> getLuoghi() const;
    vector<QString> getAziende() const;
    vector<int> getDate() const;
    void setEspBox(vector<QString>, vector<QString>, vector<QString>, vector<int>, bool);
private slots:
    void successivo();
    void precedente();
    void cancellaCurrent();
};

#endif // ESPLAVOROBOX_H
