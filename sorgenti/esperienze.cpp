#include "esperienze.h"

Esperienze::Esperienze() {}

Esperienze::Esperienze(QString descrizione, QString azienda, QString luogo, Data inizio, Data fine):
descrizione(descrizione), luogo(luogo), nomeAzienda(azienda), inizioLavoro(inizio), fineLavoro(fine) {}

QString Esperienze::getStringEsperienza() const{
    QString datiEsp = "";
    if(nomeAzienda.size()!=0)   datiEsp = datiEsp + "Ha lavorato presso " + nomeAzienda;
    if(luogo.size()!=0)   datiEsp = datiEsp + "\nA " + luogo + "\n";
    datiEsp = datiEsp + "Descrizione:\t" + descrizione + "\nDal " + inizioLavoro.getStringaData() + " al " + fineLavoro.getStringaData();
    return datiEsp;
}

Data Esperienze::getInizioLavoro() const{
    return inizioLavoro;
}

Data Esperienze::getFineLavoro() const{
    return fineLavoro;
}

QString Esperienze::getDescrizione() const{
    return descrizione;
}

QString Esperienze::getNomeAzienda() const{
    return nomeAzienda;
}

QString Esperienze::getLuogo() const{
    return luogo;
}
