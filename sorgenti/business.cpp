#include "business.h"

Business::Business(const Utente & u): Utente(u) {}

Business::Business(QString username, QString password, Profilo profilo): Utente(username, password, profilo) {}

int Business::tipoUtente() const{
    return 2;
}
QString Business::userSearch(const SmartUtente & us, bool m) const{
    SearchFunctor f(2);
    return f(us,m);
}

int Business::getMaxMessaggi() const{
    return 5;
}
