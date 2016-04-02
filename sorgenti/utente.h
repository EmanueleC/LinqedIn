#ifndef UTENTE_H
#define UTENTE_H
#include "profilo.h"
#include "smartutente.h"
#include "rete.h"
#include "messaggio.h"

class Utente
{
    friend class SmartUtente;
    // E' la base astratta della gerarchia di utenti LinqedIn
private:
    QString username, password; // username unico per ogni utente
    Profilo profilo;
    Rete* rete;
    int riferimenti;
    vector<Messaggio> messaggi;
    int numMessaggi;
    vector<QString> contattiEst;
protected:
    class SearchFunctor {
        public:
            int searchType;
            SearchFunctor(int x=0): searchType(x) {}
            QString operator() (const SmartUtente & x, bool m) const { // tipo di ritorno era void prima
                QString provincia = x->getProfilo().getProvincia();
                QString email = x->getProfilo().getEmail();
                QString dati;
                switch(searchType) {
                case 1:
                    if(m){ dati = "Nome: " + x->getProfilo().getNome() + "\nCongome: " + x->getProfilo().getCognome() + "\nData di nascita: " + x->getProfilo().getData(); if(!provincia.isEmpty()) dati = dati + "\nProvincia: " + provincia; }
                    else{  dati = "Nome: " + x->getProfilo().getNome() + "\nCongome: " + x->getProfilo().getCognome() + "\nData di nascita: " + x->getProfilo().getData(); if(!provincia.isEmpty()) dati = dati + "\nProvincia: " + x->getProfilo().getProvincia(); if(!email.isEmpty()) dati = dati + "\nE-mail: " + x->getProfilo().getEmail(); }
                    return dati;
                    break;
                case 2:
                    if(m){ dati = "Nome: " + x->getProfilo().getNome() + "\nCongome: " + x->getProfilo().getCognome() + "\nData di nascita: " + x->getProfilo().getData(); if(!provincia.isEmpty()) dati = dati + "\nProvincia: " + x->getProfilo().getProvincia(); if(!email.isEmpty()) dati = dati + "\nE-mail: " + x->getProfilo().getEmail(); return dati; }
                    else return x->informazioni();
                    break;
                case 3:
                    return x->informazioni();
                    break;
                default:
                    return "Default: " + x->getProfilo().getNome();
                    break;
                }
            }
    };
public:
    Utente();
    Utente(const Utente &);
    Utente(QString, QString, Profilo);
    QString getUsername() const;
    QString getPassword() const;
    Profilo getProfilo() const; // permette di accedere ai dati nel profilo
    Rete* getRete() const;
    virtual int tipoUtente() const = 0;
    virtual QString userSearch(const SmartUtente &, bool) const = 0;
    virtual ~Utente() { delete rete; } // distruttore virtuale
    QString informazioni() const;
    void setProfilo(Profilo);
    void setUsername(QString);
    void setPassword(QString);
    void setRete(vector<QString>);
    void setContattiEst(vector<QString>);
    void setNumMessaggi(int);
    void inserisciMessaggio(Messaggio);
    const vector<Messaggio> getMessaggi() const;
    void cancellaMessaggi();
    virtual int getMaxMessaggi() const = 0;
    int getNumMessaggi() const;
    void messaggiUp();
    void inserisciContattoEst(QString);
    void eliminaContattoEst(QString);
    vector<QString> getContattiEst() const;
};

#endif // UTENTE_H
