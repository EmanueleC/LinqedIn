#include "profilo.h"

Profilo::Profilo() {}

Profilo::Profilo(Info info, Curriculum curriculum): datiAnagrafici(info), curriculum(curriculum) {}

QString Profilo::getNome() const{
    return datiAnagrafici.getNome();
}

QString Profilo::getCognome() const{
    return datiAnagrafici.getCognome();
}

QString Profilo::getEmail() const{
    return datiAnagrafici.getEmail();
}

QString Profilo::getProvincia() const{
    return datiAnagrafici.getProvincia();
}

QString Profilo::getTelefono() const{
    return datiAnagrafici.getTelefono();
}

QString Profilo::getData() const{
    return datiAnagrafici.getData();
}

bool Profilo::Uomo() const{
    return datiAnagrafici.Uomo();
}

QString Profilo::getLingue() const{
    return curriculum.getLingue();
}

QString Profilo::getTitoli() const{
    QString datiTitolo = "------\n";
    for(unsigned int i=0; i<curriculum.getTitoli().size(); ++i){
        datiTitolo = datiTitolo + curriculum.getTitoli()[i].getStringTitolo() + "\n------\n";
    }
    return datiTitolo;
}

QString Profilo::getInteressi() const{
    return curriculum.getInteressi();
}

QString Profilo::getSito() const{
    return curriculum.getSito();
}

QString Profilo::getEsperienze() const{
    QString datiEsp = "------\n";
    for(unsigned int i=0; i<curriculum.getEsp().size(); ++i){
        datiEsp = datiEsp + curriculum.getEsp()[i].getStringEsperienza() + "\n------\n";
    }
    return datiEsp;
}

int Profilo::getGiornoNascita() const{
    return datiAnagrafici.getGiorno();
}

int Profilo::getMeseNascita() const{
    return datiAnagrafici.getMese();
}

int Profilo::getAnnoNascita() const{
    return datiAnagrafici.getAnno();
}

vector<Esperienze> Profilo::getEsp() const{
    return curriculum.getEsp();
}

vector<titoli> Profilo::getVecTitolo() const{
    return curriculum.getTitoli();
}

Curriculum Profilo::getCurriculum() const{
    return curriculum;
}

