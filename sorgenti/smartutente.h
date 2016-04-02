#ifndef SMARTUTENTE_H
#define SMARTUTENTE_H

class Utente;

class SmartUtente
{ friend class Controller;
private:
    Utente* up; // up è un puntatore polimorfo
public:
    SmartUtente();
    SmartUtente(Utente*);

    // ridefinisce costruttore di copia, distruttore e assegnazione

    SmartUtente(const SmartUtente&);
    ~SmartUtente();
    SmartUtente& operator = (const SmartUtente &);

    // ridefinisce operatore di dereferenziazione e accesso

    Utente& operator * () const;
    Utente* operator -> () const;


    bool operator == (const SmartUtente &) const;
    bool operator != (const SmartUtente &) const;
};

#endif // SMARTUTENTE_H
