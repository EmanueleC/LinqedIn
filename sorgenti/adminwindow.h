#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H
#include "controller.h"
#include "ricercabox.h"

class AdminWindow: public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
    QGroupBox* gestioneDatabase, *cambioAccount;
    QGridLayout* databaseLayout, *ricercaLayout;
    QComboBox* utenti_attesa, *utenti_presenti, *utenti_cambio;
    QPushButton* caricaDatabase, * salvaDatabase;
    ricercabox* ricercaBox;
    QString usernameCambio;
    QString tipoCambio;
    void creaDatabaseBox();
    void creaCambioBox();
public:
    AdminWindow(Controller*);
private slots:
    void aggiorna();
    void salvaUtente();
    void eliminaUtente();
    void cambiaTipoAccount();
    void annullaCambio();
    void salvaDati() const;
    void caricaDati();
    void azzeraMessaggi() const;
};

#endif // ADMINWINDOW_H
