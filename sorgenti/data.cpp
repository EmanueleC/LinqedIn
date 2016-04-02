#include "data.h"

Data::Data() {}

Data::Data(int giorno, int mese, int anno): giorno(giorno), mese(mese), anno(anno) {}

QString Data::getStringaData() const{
    QString stringData = QString::number(giorno) + "-" + QString::number(mese) + "-" + QString::number(anno);
    return stringData;
}

int Data::getGiorno() const{
    return giorno;
}

int Data::getMese() const{
    return mese;
}

int Data::getAnno() const{
    return anno;
}
