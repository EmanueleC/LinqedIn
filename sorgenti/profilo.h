#ifndef PROFILO_H
#define PROFILO_H
#include "info.h"
#include "curriculum.h"

class Profilo
{
    // contiene le informazioni anagrafiche e il curriculum
private:
    Info datiAnagrafici;
    Curriculum curriculum;
public:
    Profilo();
    Profilo(Info, Curriculum);
    QString getNome() const;
    QString getCognome() const;
    QString getEmail() const;
    QString getProvincia() const;
    QString getTelefono() const;
    QString getData() const;
    QString getLingue() const;
    QString getTitoli() const;
    QString getInteressi() const;
    QString getSito() const;
    QString getEsperienze() const;
    int getGiornoNascita() const;
    int getMeseNascita() const;
    int getAnnoNascita() const;
    bool Uomo() const;
    vector<Esperienze> getEsp() const;
    vector<titoli> getVecTitolo() const;
    Curriculum getCurriculum() const;
};

#endif // PROFILO_H
