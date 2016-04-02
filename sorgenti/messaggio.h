#ifndef MESSAGGIO_H
#define MESSAGGIO_H
#include <QString>

class Messaggio
{
private:
    QString sender;
    QString text;
public:
    Messaggio(QString, QString);
    QString getSender() const;
    QString getText() const;
};

#endif // MESSAGGIO_H
