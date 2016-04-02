#include "executive.h"

Executive::Executive(const Utente & u): Utente(u) {}

Executive::Executive(QString username, QString password, Profilo profilo): Utente(username, password, profilo) {}

int Executive::tipoUtente() const{
    return 3;
}

QString Executive::userSearch(const SmartUtente & us, bool m) const{
    SearchFunctor f(3);
    return f(us,m);
}

int Executive::getMaxMessaggi() const{
    return 25;
}
