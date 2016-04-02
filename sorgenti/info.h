#ifndef INFO_H
#define INFO_H
#include "data.h"

class Info
{
private:
    QString nome, cognome, e_mail, provincia, telefono;
    Data infoNascita;
    bool uomo; // true se uomo, false se donna
public:
    Info();
    Info(QString, QString, QString, QString, bool, QString, Data);
    QString getNome() const;
    QString getCognome() const;
    QString getEmail() const;
    QString getProvincia() const;
    QString getTelefono() const;
    QString getData() const;
    int getGiorno() const;
    int getMese() const;
    int getAnno() const;
    bool Uomo() const;
};

#endif // INFO_H
