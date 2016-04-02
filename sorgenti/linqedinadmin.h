#ifndef LINQEDINADMIN_H
#define LINQEDINADMIN_H
#include "database.h"
#include "basic.h"
#include "business.h"
#include "executive.h"

class LinqedinAdmin
{
private:
    Database* database;
    vector<SmartUtente> coda_utenti; // utenti da salvare, è un vector con gli username
    vector<QString> utenti_cambio; // utenti che hanno richiesto il cambio di account
    vector<int> tipiTarget; // l'i-esimo intero contenuto in tipiTarget corrisponde
                            // al tipo di accuont "target" dell'i-esimo utente in utenti_cambio
    static QString admin, password;
public:
    LinqedinAdmin();
    LinqedinAdmin(Database *);
    void inserisci_utente(const SmartUtente &);
    void inserisci_coda(const SmartUtente &);
    void inserisci_cambio(QString, int);
    void rimuovi_coda(int);
    void rimuoviTipo(int);
    void rimuoviUtenteCambio(int);
    void cambioTipoAccount(QString, int) const;
    void azzeraMex(QString) const;
    bool caricaDatabase() const;
    bool salvaDatabase() const;
    bool checkIn(QString, QString) const;
    bool checkUsername(QString) const;
    const vector<SmartUtente> &getCodaUtenti() const;
    vector<QString> getUtenti_cambio() const;
    vector<int> getTipiTarget() const;
    QString getAllDati(const SmartUtente &) const;
};

#endif // LINQEDINADMIN_H
