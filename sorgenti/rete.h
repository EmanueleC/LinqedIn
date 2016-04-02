#ifndef RETE_H
#define RETE_H
#include <QString>
#include <vector>
using namespace std;

class Rete
{
private:
    vector<QString> rete; // la rete è un vector di username
public:
    Rete();
    void add(QString);
    void remove(QString);
    void setRete(vector<QString>);
    int sizeRete() const;
    vector<QString> getListaContatti() const;
    bool contattoPresente(QString username) const;
};

#endif // RETE_H
