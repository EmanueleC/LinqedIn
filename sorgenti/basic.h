#ifndef BASIC_H
#define BASIC_H
#include "utente.h"

class Basic: public Utente
{
public:
    Basic(const Utente &);
    Basic(QString, QString, Profilo);
    int tipoUtente() const;
    QString userSearch(const SmartUtente &, bool) const;
    virtual int getMaxMessaggi() const;
};

#endif // BASIC_H
