#include "rete.h"

Rete::Rete() {}

void Rete::add(QString username){
    if(!contattoPresente(username))
    {
        rete.push_back(username);
    }
}

void Rete::remove(QString username){
    vector<QString>::iterator it = rete.begin();
    for(; it!=rete.end(); ++it)
        if(QString::compare((*it),username) == 0) { std::iter_swap(it,rete.end().operator --()); rete.pop_back(); return; }
}

int Rete::sizeRete() const{
    return rete.size();
}

vector<QString> Rete::getListaContatti() const{
    return rete;
}

bool Rete::contattoPresente(QString username) const{
    bool presente = false;
    for(unsigned int i=0; i<rete.size(); ++i) if(rete[i] == username) presente = true;
    return presente;
}

void Rete::setRete(vector<QString> vec_rete){
    rete = vec_rete;
}
