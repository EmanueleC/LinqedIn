#ifndef ESPERIENZE_H
#define ESPERIENZE_H
#include <QString>
#include "data.h"

class Esperienze
{
private:
    Data inizioLavoro, fineLavoro;
    QString descrizione, luogo, nomeAzienda;
public:
    Esperienze();
    Esperienze(QString, QString, QString, Data, Data);
    QString getStringEsperienza() const;
    QString getDescrizione() const;
    QString getNomeAzienda() const;
    QString getLuogo() const;
    Data getInizioLavoro() const;
    Data getFineLavoro() const;
};

#endif // ESPERIENZE_H
