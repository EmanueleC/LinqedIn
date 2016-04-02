#include "info.h"

Info::Info() {}

Info::Info(QString nome, QString cognome, QString e_mail, QString provincia, bool uomo, QString telefono, Data data):
nome(nome), cognome(cognome), e_mail(e_mail), provincia(provincia), telefono(telefono), infoNascita(data), uomo(uomo) {}


QString Info::getNome() const{
    return nome;
}

QString Info::getCognome() const{
    return cognome;
}

QString Info::getEmail() const{
    return e_mail;
}

QString Info::getProvincia() const{
    return provincia;
}

QString Info::getTelefono() const{
    return telefono;
}

QString Info::getData() const{
    return infoNascita.getStringaData();
}

bool Info::Uomo() const{
    return uomo;
}

int Info::getGiorno() const{
    return infoNascita.getGiorno();
}

int Info::getMese() const{
    return infoNascita.getMese();
}

int Info::getAnno() const{
    return infoNascita.getAnno();
}

