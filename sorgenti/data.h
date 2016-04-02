#ifndef DATA_H
#define DATA_H
#include <QString>

class Data
{
private:
    unsigned int giorno, mese, anno;
public:
    Data();
    Data(int , int , int );
    QString getStringaData() const;
    int getGiorno() const;
    int getMese() const;
    int getAnno() const;
};

#endif // DATA_H
