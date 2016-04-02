#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "linqedinadmin.h"
#include "basic.h"

class Controller
{
private:

    // mvc "parziale" : il controller è nella view

    SmartUtente utente;
    LinqedinAdmin* admin;
    Database* database;

public:
    Controller();
    ~Controller();

    // A - metodi che riguardano l'admin:

    // 1A - comunicazione modelAdmin --> viewAdmin

    const vector<SmartUtente> & getListaAttesa() const;
    vector<QString> getListaUsername() const;
    QString getAllDati(const SmartUtente &) const;
    bool checkInAdmin(QString,QString) const;
    bool dbCaricato() const;

    // 2A - comunicazione viewAdmin --> modelAdmin

    void salvaUtente(int) const;
    void eliminaUtente(QString,int) const;
    void rimuoviCodaAdmin(int) const;
    void inserisciUtenteCambio(int) const;
    void cambiaTipoAccount(QString, int) const;
    void rimuoviUtenteCambiato(int) const;
    void rimuoviTipo(int) const;
    void azzeraMex(QString) const;
    bool salvaDati() const;
    bool caricaDati() const;

    // C - metodi che riguardano l'utente:

    // 1C - comunicazione viewUtente --> modelUtente

    void carica_nuovoUtente(QString, QString, QString, QString, QString, QString, QString, QString, bool, int, int, int, QString, QString,vector<QString>, vector<QString>, vector<QString>, vector<QString>, vector<int>, vector<QString>, vector<QString>, vector<QString>, vector<int>);
    void modificaUtente(QString, QString, QString, QString, QString, QString, QString, QString, bool, int, int, int, QString, QString,vector<QString>, vector<QString>, vector<QString>, vector<QString>, vector<int>, vector<QString>, vector<QString>, vector<QString>, vector<int>);
    void scollega();
    void collega(const SmartUtente &);
    void cancellaMessaggi();
    void rimuoviContatto(const SmartUtente &);
    bool inserisciContatto(const SmartUtente &);

    // 2C - comunicazione modelUtente --> viewUtente

    vector<QString> getListaContatti() const;
    vector<QString> getListaCambio() const;
    vector<QString> getAziende() const;
    vector<QString> getLuoghiLavoro() const;
    vector<QString> getDescrizioniEsperienze() const;
    vector<QString> getTitoliStudio() const;
    vector<QString> getIstituzioni() const;
    vector<QString> getDescrizioniTitoli() const;
    vector<QString> getAreeStudio() const;
    vector<int> getCifreDateEsp() const;
    vector<int> getCifreDateTitoli() const;
    vector<int> getListaTipi() const;
    QString getDatiRicerca(const SmartUtente &, bool = true) const;
    QString getNomeUtente() const;
    QString getDatiUtente() const;
    QString getUsername() const;
    QString getMessaggi() const;
    QString getContattiEst() const;
    bool checkIn(QString,QString) const;
    bool checkUsername(QString) const;
    bool utenteCaricato() const;
    bool utenteSalvato() const;
    bool Uomo() const;
    int inviaMessaggio(QString, QString) const;
    int getTipoUtente() const;
    int sizeRete() const;
    int checkNotifiche() const;
    Profilo getProfiloUtente() const;

    // metodi per utente e admin:

    // per default il nuovo utente caricato è di tipo basic

    // comunicano tutti nella direzione model --> view

    vector<QString> cercaNome(QString) const;
    vector<QString> cercaCognome(QString) const;
    vector<QString> cercaProvincia(QString) const;
    vector<QString> cercaAzienda(QString) const;
    vector<QString> cercaTitolo(QString) const;
    vector<QString> cercaArea(QString) const;
    vector<QString> cerca(QString, QString, QString, QString, QString, QString) const;
    SmartUtente cercaUsername(QString) const;

    // metodo temporaneo

    Utente* getPunt() const{
        return utente.up;
    } 
};

#endif // CONTROLLER_H
