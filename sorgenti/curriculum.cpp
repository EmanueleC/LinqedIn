#include "curriculum.h"

Curriculum::Curriculum() {}

Curriculum::Curriculum(QString lingue, vector<titoli> titoli, QString interessi, QString sito, vector<Esperienze> esp):
 esp_Lavorative(esp), titoliStudio(titoli), lingueParlate(lingue), interessi(interessi), sito_web(sito) {}

QString Curriculum::getLingue() const{
    return lingueParlate;
}

vector<titoli> Curriculum::getTitoli() const{
    return titoliStudio;
}

QString Curriculum::getInteressi() const{
    return interessi;
}

QString Curriculum::getSito() const{
    return sito_web;
}

vector<QString> Curriculum::getAzienda() const{
    vector<QString> aziende;
    for(unsigned int i = 0; i<esp_Lavorative.size(); ++i)
        aziende.push_back(esp_Lavorative[i].getNomeAzienda());
    return aziende;
}

vector<QString> Curriculum::getLuogoLavoro() const{
    vector<QString> luoghiLavoro;
    for(unsigned int i = 0; i<esp_Lavorative.size(); ++i)
        luoghiLavoro.push_back(esp_Lavorative[i].getLuogo());
    return luoghiLavoro;
}

vector<QString> Curriculum::getDescrizioneEsperienze() const{
    vector<QString> descrizioni;
    for(unsigned int i = 0; i<esp_Lavorative.size(); ++i)
            descrizioni.push_back(esp_Lavorative[i].getDescrizione());
    return descrizioni;
}

vector<int> Curriculum::getCifreDateEsp() const{
    vector<int> cifreDate;
    for(unsigned int i = 0; i<esp_Lavorative.size(); ++i){
            cifreDate.push_back(esp_Lavorative[i].getInizioLavoro().getGiorno());
            cifreDate.push_back(esp_Lavorative[i].getInizioLavoro().getMese());
            cifreDate.push_back(esp_Lavorative[i].getInizioLavoro().getAnno());
            cifreDate.push_back(esp_Lavorative[i].getFineLavoro().getGiorno());
            cifreDate.push_back(esp_Lavorative[i].getFineLavoro().getMese());
            cifreDate.push_back(esp_Lavorative[i].getFineLavoro().getAnno());
    }
    return cifreDate;
}

vector<Esperienze> Curriculum::getEsp() const{
    return esp_Lavorative;
}

vector<QString> Curriculum::getTitoliStudio() const{
    vector<QString> TitoliStudio;
    for(unsigned int i = 0; i<titoliStudio.size(); ++i)
            TitoliStudio.push_back(titoliStudio[i].getTitolo());
    return TitoliStudio;
}

vector<QString> Curriculum::getDescrizioniTitoli() const{
    vector<QString> DescrizioniTitoli;
    for(unsigned int i = 0; i<titoliStudio.size(); ++i)
            DescrizioniTitoli.push_back(titoliStudio[i].getDescrizione());
    return DescrizioniTitoli;
}

vector<QString> Curriculum::getIstituzioni() const{
    vector<QString> istituzioni;
    for(unsigned int i = 0; i<titoliStudio.size(); ++i)
            istituzioni.push_back(titoliStudio[i].getIstituzione());
    return istituzioni;
}

vector<QString> Curriculum::getAreeStudio() const{
    vector<QString> areeStudio;
    for(unsigned int i = 0; i<titoliStudio.size(); ++i)
            areeStudio.push_back(titoliStudio[i].getAreaStudio());
    return areeStudio;
}

vector<int> Curriculum::getCifreDateTitoli() const{
    vector<int> cifreDate;
    for(unsigned int i = 0; i<titoliStudio.size(); ++i){
            cifreDate.push_back(titoliStudio[i].getData().getGiorno());
            cifreDate.push_back(titoliStudio[i].getData().getMese());
            cifreDate.push_back(titoliStudio[i].getData().getAnno());
    }
    return cifreDate;
}
