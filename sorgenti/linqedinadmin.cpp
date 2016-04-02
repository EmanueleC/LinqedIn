#include "linqedinadmin.h"
#include "utente.h"

LinqedinAdmin::LinqedinAdmin() {}

LinqedinAdmin::LinqedinAdmin(Database * d): database(d) {}

QString LinqedinAdmin::admin = "Linq";
QString LinqedinAdmin::password = "admin";

void LinqedinAdmin::inserisci_utente(const SmartUtente & us){
    database->inserisciUtente(us);
}

void LinqedinAdmin::inserisci_coda(const SmartUtente & us){
    coda_utenti.push_back(us); // push_back(const SmartUtente&) causa l'invocazione
                               // del costruttore di copia dello SmartUtente
}

const vector<SmartUtente> & LinqedinAdmin::getCodaUtenti() const{
    return coda_utenti;
}

void LinqedinAdmin::rimuovi_coda(int i){
    vector<SmartUtente>::iterator it = coda_utenti.begin() + i;
    std::iter_swap(it,coda_utenti.end().operator --());
    coda_utenti.pop_back();
}

QString LinqedinAdmin::getAllDati(const SmartUtente & us) const{
    if(us!=SmartUtente(0))  return us->informazioni() + "\n" + "Password: " + "\t" + us->getPassword() + "\n" + "Rete: "+QString::number(us->getRete()->sizeRete());
    else return "Utente non presente nel database";
}

bool LinqedinAdmin::checkUsername(QString username) const{
    for(unsigned int i=0; i<coda_utenti.size(); ++i)
        if(coda_utenti[i]->getUsername() == username) return false;
    // se lo username è già stato scelto da un utente in attesa, nessun altro può usarlo
    return true;
}

void LinqedinAdmin::inserisci_cambio(QString username, int x){
    utenti_cambio.push_back(username);
    tipiTarget.push_back(x);
}

vector<QString> LinqedinAdmin::getUtenti_cambio() const{
    return utenti_cambio;
}

vector<int> LinqedinAdmin::getTipiTarget() const{
    return tipiTarget;
}

void LinqedinAdmin::rimuoviUtenteCambio(int i){
    vector<QString>::iterator it = utenti_cambio.begin() + i;
    std::iter_swap(it,utenti_cambio.end().operator --());
    utenti_cambio.pop_back();
}

void LinqedinAdmin::azzeraMex(QString username) const{
    database->cercaUsername(username)->setNumMessaggi(0);
}

void LinqedinAdmin::rimuoviTipo(int posizione){
    vector<int>::iterator it = tipiTarget.begin();
    int i = 0;
    for(; it!=tipiTarget.end(); ++it){
        if(i == posizione){  std::iter_swap(it,tipiTarget.end().operator --()); tipiTarget.pop_back(); return; }
        i++;
    }
}

bool LinqedinAdmin::caricaDatabase() const{
    return database->loadXML();
}

bool LinqedinAdmin::salvaDatabase() const{
    return database->writeXML();
}

void LinqedinAdmin::cambioTipoAccount(QString username, int x) const{
    database->cambiaTipoAccount(username,x);
}

bool LinqedinAdmin::checkIn(QString a, QString p) const{
    if(a == admin && p == password) return true;
    else return false;
}
