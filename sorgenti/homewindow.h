#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H
#include "formclass.h"
#include "userwindow.h"
#include "rettangolo.h"
using namespace std;

class HomeWindow: public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
    FormClass* iscrizioneUtente; // puntatore alla finestra per l'iscrizione
    QPushButton* entra, *iscrizione, *accesso, *logOut;
    QLabel * titolo, *infoLinqedIn;
    QVBoxLayout* layout, *layoutHome;
    UserWindow* userWindow;
    QGroupBox* homeBox, * accesso_box;
    QLineEdit* userName, *password;
    Rettangolo* rett;
    QScrollArea * scrollarea, *scrollarea2;
    void caricaHome();
public:
    HomeWindow(Controller*);
    void ripristina();
private slots:
    void createFormClass(); // crea una finestra per l'iscrizione
    void caricaPaginaUtente();
    void esci() const; // esci dalla pagina utente (log out)
    void accedi();
};

#endif // HOMEWINDOW_H
