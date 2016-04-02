#ifndef CURRICULUM_H
#define CURRICULUM_H
#include "esperienze.h"
#include "titoli.h"
#include <vector>
using namespace std;


class Curriculum
{
private:
    vector<Esperienze> esp_Lavorative;
    vector<titoli> titoliStudio;
    QString lingueParlate, interessi, sito_web;
public:
    Curriculum();
    Curriculum(QString , vector<titoli>, QString , QString, vector<Esperienze>);
    QString getLingue() const;
    QString getInteressi() const;
    QString getSito() const;
    vector<QString> getAzienda() const;
    vector<QString> getLuogoLavoro() const;
    vector<QString> getDescrizioneEsperienze() const;
    vector<int> getCifreDateEsp() const;
    vector<Esperienze> getEsp() const;
    vector<QString> getTitoliStudio() const;
    vector<QString> getIstituzioni() const;
    vector<QString> getDescrizioniTitoli() const;
    vector<QString> getAreeStudio() const;
    vector<int> getCifreDateTitoli() const;
    vector<titoli> getTitoli() const;
};

#endif // CURRICULUM_H
