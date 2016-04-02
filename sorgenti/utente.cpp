#include "utente.h"

Utente::Utente(): rete(new Rete), riferimenti(0), numMessaggi(0) {}

Utente::Utente(QString username, QString password, Profilo pf):
    username(username), password(password), profilo(pf), rete(new Rete), riferimenti(0), numMessaggi(0) {}

Utente::Utente(const Utente & u): username(u.username), password(u.password), profilo(u.profilo), riferimenti(0), messaggi(u.messaggi), numMessaggi(u.numMessaggi), contattiEst(u.contattiEst) {
    rete = new Rete(*u.rete);
    // è stato ridefinito per evitare incongruenze nel campo riferimenti del nuovo Utente costruito di copia
}

QString Utente::getUsername() const{
    return username;
}

QString Utente::getPassword() const{
    return password;
}

Profilo Utente::getProfilo() const{
    return profilo;
}

QString Utente::informazioni() const{
    QString info;
    info = "Nome: " + profilo.getNome() + "\nCognome: " + profilo.getCognome() + "\nData di nascita: " + profilo.getData() + "\n";
    if(profilo.getProvincia().size()!=0)    info = info + "Provincia: " + profilo.getProvincia() + "\n";
    if(profilo.getEmail().size()!=0)        info = info + "Email: " + profilo.getEmail() + "\n";
    if(profilo.getTelefono().size()!=0)     info = info + "Telefono: " + profilo.getTelefono() + "\n";
    info = info + "\n --- Curriculum --- \n";
    if(profilo.getLingue().size()!=0)       info = info + "\nLingue parlate: " + "\n" + profilo.getLingue() + "\n";
    if(profilo.getTitoli().size()!=0)       info = info + "\nTitoli di studio: " + "\n" + profilo.getTitoli() + "\n";
    if(profilo.getInteressi().size()!=0)    info = info + "\nInteressi: " + "\n" + profilo.getInteressi() + "\n";
    if(profilo.getEsperienze().size()!=0)   info = info + "\nEsperienze Lavorative: \n" + profilo.getEsperienze();
    return info;
}

Rete* Utente::getRete() const{
    return rete;
}

void Utente::setProfilo(Profilo pf){
    profilo = pf;
}

void Utente::setUsername(QString nuovoUsername){
    username = nuovoUsername;
}

void Utente::setPassword(QString nuovaPassword){
    password = nuovaPassword;
}

void Utente::setRete(vector<QString> vec_rete){
    rete->setRete(vec_rete);
}

void Utente::inserisciMessaggio(Messaggio m){
    messaggi.push_back(m);
}

const vector<Messaggio> Utente::getMessaggi() const{
    return messaggi;
}

void Utente::cancellaMessaggi(){
    messaggi.clear();
}

int Utente::getNumMessaggi() const{
    return numMessaggi;
}

void Utente::messaggiUp(){
    numMessaggi = numMessaggi + 1;
}

void Utente::inserisciContattoEst(QString username){
    for(unsigned int i=0; i<contattiEst.size(); ++i)
        if(contattiEst[i]==username)    return;
    contattiEst.push_back(username);
}

vector<QString> Utente::getContattiEst() const{
    return contattiEst;
}

void Utente::eliminaContattoEst(QString username){
    vector<QString>::iterator it=contattiEst.begin();
    for(; it!=contattiEst.end(); ++it){
        if(*it==username){ std::iter_swap(it,contattiEst.end().operator --()); contattiEst.pop_back(); return; }
    }
}

void Utente::setContattiEst(vector<QString> VcontattiEst){
    for(unsigned int i = 0; i<VcontattiEst.size(); ++i){
        contattiEst.push_back(VcontattiEst[i]);
    }
}

void Utente::setNumMessaggi(int n){
    numMessaggi = n;
}
