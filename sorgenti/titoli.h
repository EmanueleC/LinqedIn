#ifndef TITOLI_H
#define TITOLI_H
#include "data.h"

class titoli
{
private:
    QString titolo, istituzione, descrizione, areaStudio;
    Data data; // anno in cui è stato rilasciato il diploma/certificazione
public:
    titoli();
    titoli(QString, QString, QString, QString, Data);
    QString getStringTitolo() const;
    QString getTitolo() const;
    QString getIstituzione() const;
    QString getDescrizione() const;
    QString getAreaStudio() const;
    Data getData() const;
};

#endif // TITOLI_H
