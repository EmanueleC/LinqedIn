#ifndef FORMCLASS_H
#define FORMCLASS_H
#include "controller.h"
#include "esplavorobox.h"
#include "titolistudiobox.h"
using namespace std;


class HomeWindow;

class FormClass: public QWidget
{
    Q_OBJECT

private:
    Controller* controller;
    QLineEdit *nome, *cognome, *username, *password, *email, *provincia, *telefono, *sito;
    QTextEdit *lingueParlate, *interessi;
    QRadioButton *uomo, *donna;
    QSpinBox* datiNascita[3];
    QPushButton* esci;
    EspLavoroBox* espBox;
    TitoliStudioBox* titoliBox;
    HomeWindow* home;
    QScrollArea * scrollarea;
    bool mode; // true se la modalità è iscrizione, false se la modalità è modifica dati
public:
    FormClass(Controller * , bool, HomeWindow*);
public slots:
    void salva();
    void ripristinaHome();
};

#endif // FORMCLASS_H
