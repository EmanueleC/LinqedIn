#ifndef BUSINESS_H
#define BUSINESS_H
#include "utente.h"

class Business: public Utente
{
public:
    Business(const Utente &);
    Business(QString, QString, Profilo);
    int tipoUtente() const;
    QString userSearch(const SmartUtente &,bool) const;
    virtual int getMaxMessaggi() const;
};

#endif // BUSINESS_H
