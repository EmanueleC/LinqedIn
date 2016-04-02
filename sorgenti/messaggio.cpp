#include "messaggio.h"

Messaggio::Messaggio(QString s, QString t): sender(s), text(t){}

QString Messaggio::getSender() const{
    return sender;
}

QString Messaggio::getText() const{
    return text;
}
