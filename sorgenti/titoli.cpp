#include "titoli.h"

titoli::titoli() {}

titoli::titoli(QString t, QString i, QString de, QString a, Data da):
    titolo(t), istituzione(i), descrizione(de), areaStudio(a), data(da) {}

QString titoli::getStringTitolo() const{
    QString datiTitolo = "";
    if(titolo.size()!=0)   datiTitolo = "Titolo: " + titolo;
    if(istituzione.size()!=0)   datiTitolo = datiTitolo + "\nRilasciato da: " + istituzione;
    if(areaStudio.size()!=0)    datiTitolo = datiTitolo + "\nArea di studio: " + areaStudio;
    if(descrizione.size()!=0)   datiTitolo = datiTitolo + "\nDescrizione: " + descrizione;
    datiTitolo = datiTitolo + "\nData rilascio:\t" + data.getStringaData();
    return datiTitolo;
}

QString titoli::getTitolo() const{
    return titolo;
}

QString titoli::getDescrizione() const{
    return descrizione;
}

QString titoli::getIstituzione() const{
    return istituzione;
}

QString titoli::getAreaStudio() const{
    return areaStudio;
}

Data titoli::getData() const{
    return data;
}
