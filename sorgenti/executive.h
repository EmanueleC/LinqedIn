#ifndef EXECUTIVE_H
#define EXECUTIVE_H
#include "utente.h"

class Executive: public Utente
{
public:
    Executive(const Utente &);
    Executive(QString, QString, Profilo);
    int tipoUtente() const;
    QString userSearch(const SmartUtente &,bool) const;
    virtual int getMaxMessaggi() const;
};

#endif // EXECUTIVE_H
