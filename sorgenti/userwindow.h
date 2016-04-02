#ifndef USERWINDOW_H
#define USERWINDOW_H
#include "controller.h"
#include "retebox.h"
#include "formclass.h"
#include "messaggiwindow.h"
#include "ricercabox.h"
using namespace std;

class UserWindow: public QWidget
{
    Q_OBJECT

private:
    int tipoTarget;
    Controller* controller;
    QTextEdit* mostraDati, *mostraRisultati, *mostraReteInfo;
    QLineEdit* nome_cercato, *cognome_cercato, *username_cercato, *provincia_cercata;
    QPushButton* aggiungi,* notifiche, * mostraRete, * nascondiRete;
    ReteBox* reteBox;
    QVBoxLayout* layout;
    void scriviRisultati(QString);
    messaggiwindow* finestraMessaggi;
    ricercabox* ricercaBox;
public:
    UserWindow(Controller*);
    void mostraReteButton() const; // utilizzato da RicercaBox
    void nascondiReteButton() const; // utilizzato da RicercaBox
private slots:
    void mostraProfilo() const;
    void inserisciContatto();
    void mostraContatti() const;
    void nascondiContatti() const;
    void modifica();
    void creaScelteBox() const;
    void cambiaTipo() const;
    void tipoTargetBasic();
    void tipoTargetBusiness();
    void tipoTargetExecutive();
    void aggiorna() const;
    void mostraNotifiche() const;
    void scriviMessaggio() const;
    void contattiEst();
};

#endif // USERWINDOW_H
