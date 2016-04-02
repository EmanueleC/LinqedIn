#ifndef DATABASE_H
#define DATABASE_H
#include "smartutente.h"
#include <vector>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
using namespace std;

class Database
{
    friend class SmartUtente;
private:
    vector<SmartUtente> database;
    bool caricato; // true se il db è stato caricato
    void eliminaContattiIntEst(QString) const;
public:
    Database();
    vector<QString> cerca(QString, QString, QString, QString, QString, QString);
    vector<QString> cercaNome(QString) const;
    vector<QString> cercaCognome(QString) const;
    vector<QString> cercaProvincia(QString) const;
    vector<QString> cercaAzienda(QString) const;
    vector<QString> cercaTitolo(QString) const;
    vector<QString> cercaArea(QString) const;
    vector<QString> listaUsername() const;
    SmartUtente cercaUsername(QString) const;
    void inserisciUtente(const SmartUtente &);
    void eliminaUtente(QString,int);
    void cambiaTipoAccount(QString, int);
    bool getCaricato() const;
    bool writeXML();
    bool loadXML();
    bool checkUsername(QString) const;
    bool checkIn(QString,QString) const;
};

#endif // DATABASE_H
