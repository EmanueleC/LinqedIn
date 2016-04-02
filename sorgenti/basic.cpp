#include "basic.h"

Basic::Basic(const Utente & u): Utente(u) {}

Basic::Basic(QString username, QString password, Profilo pf): Utente(username, password, pf) {}

int Basic::tipoUtente() const{
    return 1;
}

QString Basic::userSearch(const SmartUtente & us, bool m) const{
    SearchFunctor f(1);
    return f(us,m);
}

int Basic::getMaxMessaggi() const{
    return 0;
}
