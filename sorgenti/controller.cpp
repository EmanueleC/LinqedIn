#include "controller.h"

Controller::Controller(): utente(0), database(new Database)
{
   admin = new LinqedinAdmin(database);
}

Controller::~Controller(){
    delete database;
    delete admin;
}

bool Controller::checkUsername(QString username) const{
    return database->checkUsername(username) && admin->checkUsername(username);
}

bool Controller::checkIn(QString username, QString password) const{
    return database->checkIn(username, password);
}

void Controller::salvaUtente(int i) const
{
    admin->inserisci_utente(getListaAttesa()[i]);
    QString text = "Sei stato salvato nel database LinqedIn";
    Messaggio m("LinQedIn", text);
    getListaAttesa()[i]->inserisciMessaggio(m);
}

void Controller::eliminaUtente(QString username, int i) const{
    database->eliminaUtente(username,i);
}

void Controller::carica_nuovoUtente(QString nome, QString cognome, QString username, QString password, QString email, QString provincia, QString telefono, QString sito, bool uomo, int giorno, int mese, int anno, QString lingue, QString interessi, vector<QString> nomiTitoli, vector<QString> istituzioni, vector<QString> descTitoli, vector<QString> areeStudio, vector<int> dateTitoli,  vector<QString> esp, vector<QString> aziende, vector<QString> luoghi, vector<int> dateEsp){
    Data data_temp(giorno, mese, anno);
    Info info_temp(nome, cognome, email, provincia, uomo, telefono, data_temp);
    vector<titoli> v_titoli;
    for(unsigned int i=0; i<nomiTitoli.size(); ++i){
        QString titolo = nomiTitoli[i];
        QString descrizioneTitolo = descTitoli[i];
        QString istituzione = istituzioni[i];
        QString areaStudio= areeStudio[i];
        int giorno = dateTitoli[i*3];
        int mese = dateTitoli[i*3+1];
        int anno = dateTitoli[i*3+2];
        Data dataTitolo(giorno, mese, anno);
        titoli t(titolo, istituzione, descrizioneTitolo, areaStudio, dataTitolo);
        v_titoli.push_back(t);
    }
    vector<Esperienze> v_esp;
    for(unsigned int i=0; i<esp.size(); ++i){
        QString descrizione = esp[i];
        QString azienda = aziende[i];
        QString luogo = luoghi[i];
        int giorno_inizio = dateEsp[i*6];
        int mese_inizio = dateEsp[i*6+1];
        int anno_inizio = dateEsp[i*6+2];
        int giorno_fine = dateEsp[i*6+3];
        int mese_fine = dateEsp[i*6+4];
        int anno_fine = dateEsp[i*6+5];
        Data inizio(giorno_inizio, mese_inizio, anno_inizio);
        Data fine(giorno_fine, mese_fine, anno_fine);
        Esperienze e(descrizione, azienda, luogo, inizio, fine);
        v_esp.push_back(e);
    }
    Curriculum curriculum_temp(lingue, v_titoli, interessi, sito, v_esp);
    Profilo profilo_temp(info_temp, curriculum_temp);
    SmartUtente temp(new Basic(username, password, profilo_temp));
    utente = temp; // assegnazione SmartUtente
    admin->inserisci_coda(utente);
    QString text = "Benvenuto su LinQedIn. \nAttendi che l'amministratore ti registri nel database, per risultare visibile agli altri utenti.";
    Messaggio m("LinQedIn", text);
    utente->inserisciMessaggio(m);
}

void Controller::modificaUtente(QString nome, QString cognome, QString username, QString password, QString email, QString provincia, QString telefono, QString sito, bool uomo, int giorno, int mese, int anno, QString lingue, QString interessi, vector<QString> nomiTitoli, vector<QString> istituzioni, vector<QString> descTitoli, vector<QString> areeStudio, vector<int> dateTitoli,  vector<QString> esp, vector<QString> aziende, vector<QString> luoghi, vector<int> dateEsp){
    Data data_temp(giorno, mese, anno);
    Info info_temp(nome, cognome, email, provincia, uomo, telefono, data_temp);
    vector<titoli> v_titoli;
    for(unsigned int i=0; i<nomiTitoli.size(); ++i){
        QString titolo = nomiTitoli[i];
        QString descrizioneTitolo = descTitoli[i];
        QString istituzione = istituzioni[i];
        QString areaStudio= areeStudio[i];
        int giorno = dateTitoli[i*3];
        int mese = dateTitoli[i*3+1];
        int anno = dateTitoli[i*3+2];
        Data dataTitolo(giorno, mese, anno);
        titoli t(titolo, istituzione, descrizioneTitolo, areaStudio, dataTitolo);
        v_titoli.push_back(t);
    }
    vector<Esperienze> v_esp;
    for(unsigned int i=0; i<esp.size(); ++i){
        QString descrizione = esp[i];
        QString azienda = aziende[i];
        QString luogo = luoghi[i];
        int giorno_inizio = dateEsp[i*6];
        int mese_inizio = dateEsp[i*6+1];
        int anno_inizio = dateEsp[i*6+2];
        int giorno_fine = dateEsp[i*6+3];
        int mese_fine = dateEsp[i*6+4];
        int anno_fine = dateEsp[i*6+5];
        Data inizio(giorno_inizio, mese_inizio, anno_inizio);
        Data fine(giorno_fine, mese_fine, anno_fine);
        Esperienze e(descrizione, azienda, luogo, inizio, fine);
        v_esp.push_back(e);
    }
    Curriculum curriculum_temp(lingue, v_titoli, interessi, sito, v_esp);
    Profilo profilo_temp(info_temp, curriculum_temp);
    utente->setProfilo(profilo_temp);
    utente->setUsername(username);
    utente->setPassword(password);
}

const vector<SmartUtente> & Controller::getListaAttesa() const{
    return admin->getCodaUtenti();
}

vector<QString> Controller::getListaContatti() const{
    return utente->getRete()->getListaContatti();
}

vector<QString> Controller::getListaUsername() const{
    return database->listaUsername();
}

void Controller::azzeraMex(QString username) const{
    admin->azzeraMex(username);
}

bool Controller::utenteCaricato() const{
    // ritorna true se l'utente è stato caricato
    if(utente == 0) return false;
    else return true;
}

QString Controller::getNomeUtente() const{
    return utente->getProfilo().getNome();
}

QString Controller::getDatiUtente() const{
    return utente->informazioni();
}

Profilo Controller::getProfiloUtente() const{
    return utente->getProfilo();
}

vector<QString> Controller::cercaNome(QString nome) const{
    return database->cercaNome(nome);
}

vector<QString> Controller::cercaCognome(QString cognome) const{
    return database->cercaCognome(cognome);
}

vector<QString> Controller::cercaProvincia(QString provincia) const{
    return database->cercaProvincia(provincia);
}

SmartUtente Controller::cercaUsername(QString username) const{
    return database->cercaUsername(username);
}

bool Controller::Uomo() const{
    return utente->getProfilo().Uomo();
}

QString Controller::getDatiRicerca(const SmartUtente & us, bool m) const{
    if(us != SmartUtente(0))  return utente->userSearch(us,m);
    else return "Utente non presente nel database";
}

bool Controller::inserisciContatto(const SmartUtente & us){
    // ritorna true solo se l'utente da inserire è presente nel database
    if(us!=SmartUtente(0))
    {
        if(!utente->getRete()->contattoPresente(us->getUsername()))
        {
            utente->getRete()->add(us->getUsername());
            QString text = utente->getUsername() + " ti ha inserito fra i suoi contatti";
            Messaggio m("LinQedIn", text);
            us->inserisciMessaggio(m);
            us->inserisciContattoEst(utente->getUsername());
            return true;
        }
        else return false;
    }
    else  return false;
}

void Controller::rimuoviContatto(const SmartUtente  & us){
    if(us!=SmartUtente(0))
    {
        utente->getRete()->remove(us->getUsername());
        QString text = utente->getUsername() + " ti ha rimosso dai suoi contatti";
        Messaggio m("LinQedIn", text);
        us->inserisciMessaggio(m);
        us->eliminaContattoEst(utente->getUsername());
    }
}

int Controller::sizeRete() const{
    return utente->getRete()->sizeRete();
}

void Controller::scollega(){
    utente = 0; // assegnazione SmartUtente
}

void Controller::collega(const SmartUtente & us){
    utente = us; // assegnazione SmartUtente
}

void Controller::rimuoviCodaAdmin(int i) const{
    admin->rimuovi_coda(i);
}

QString Controller::getAllDati(const SmartUtente & us) const{
    return admin->getAllDati(us);
}

int Controller::getTipoUtente() const{
    return utente->tipoUtente();
}

bool Controller::utenteSalvato() const{
    if(database->cercaUsername(utente->getUsername())!=SmartUtente(0)) return true;
    else return false;
}

vector<QString> Controller::getListaCambio() const{
    return admin->getUtenti_cambio();
}

vector<int> Controller::getListaTipi() const{
    return admin->getTipiTarget();
}

void Controller::inserisciUtenteCambio(int tipo) const{
    admin->inserisci_cambio(utente->getUsername(), tipo);
}

void Controller::cambiaTipoAccount(QString username, int x) const{
    admin->cambioTipoAccount(username,x);
}

void Controller::rimuoviUtenteCambiato(int i) const{
    admin->rimuoviUtenteCambio(i);
}

void Controller::rimuoviTipo(int pos) const{
    admin->rimuoviTipo(pos);
}

QString Controller::getUsername() const{
    return utente->getUsername();
}

bool Controller::salvaDati() const{
    return admin->salvaDatabase();
}

bool Controller::caricaDati() const{
    return admin->caricaDatabase();
}

int Controller::checkNotifiche() const{
    return utente->getMessaggi().size();
}

QString Controller::getMessaggi() const{
    QString mex;
    for(unsigned int i =0; i<utente->getMessaggi().size(); i++)
        mex = mex + "*****" + "\n" + "Messaggio da " + utente->getMessaggi()[i].getSender() + "\n" + "Messaggio: " + utente->getMessaggi()[i].getText() + "\n";
    return mex;
}

void Controller::cancellaMessaggi(){
    utente->cancellaMessaggi();
}

int Controller::inviaMessaggio(QString username, QString text) const{
    if(database->cercaUsername(username)!=SmartUtente(0) && utente->getNumMessaggi()<utente->getMaxMessaggi()){
        Messaggio m(utente->getUsername(), text);
        (database->cercaUsername(username))->inserisciMessaggio(m);
        utente->messaggiUp();
        return 1; // segnala che il messaggio è stato inviato
    }
    else if (utente->getNumMessaggi()>=utente->getMaxMessaggi())  return -1; // quota messaggi superata
    else return 0; // il destinatario non è presente nel database linQedIn
}

QString Controller::getContattiEst() const{
    QString contattiEst = "";
    for(unsigned int i = 0; i<utente->getContattiEst().size(); i++){ 
        contattiEst = contattiEst + utente->getContattiEst()[i] + "\n";
    }
    return contattiEst;
}

vector<QString> Controller::cerca(QString nome, QString cognome, QString provincia, QString azienda, QString titolo, QString area) const{
    return database->cerca(nome,cognome,provincia,azienda,titolo,area);
}

vector<QString> Controller::cercaAzienda(QString azienda) const{
    return database->cercaAzienda(azienda);
}

vector<QString> Controller::cercaTitolo(QString titolo) const{
    return database->cercaTitolo(titolo);
}

vector<QString> Controller::cercaArea(QString area) const{
    return database->cercaArea(area);
}

vector<QString> Controller::getAziende() const{
    return utente->getProfilo().getCurriculum().getAzienda();
}

vector<QString> Controller::getDescrizioniEsperienze() const{
    return utente->getProfilo().getCurriculum().getDescrizioneEsperienze();
}

vector<QString> Controller::getLuoghiLavoro() const{
    return utente->getProfilo().getCurriculum().getLuogoLavoro();
}

vector<int> Controller::getCifreDateEsp() const{
    return utente->getProfilo().getCurriculum().getCifreDateEsp();
}

vector<QString> Controller::getTitoliStudio() const{
    return utente->getProfilo().getCurriculum().getTitoliStudio();
}

vector<QString> Controller::getDescrizioniTitoli() const{
    return utente->getProfilo().getCurriculum().getDescrizioniTitoli();
}

vector<QString> Controller::getIstituzioni() const{
    return utente->getProfilo().getCurriculum().getIstituzioni();
}

vector<QString> Controller::getAreeStudio() const{
    return utente->getProfilo().getCurriculum().getAreeStudio();
}

vector<int> Controller::getCifreDateTitoli() const{
    return utente->getProfilo().getCurriculum().getCifreDateTitoli();
}

bool Controller::checkInAdmin(QString a, QString password) const{
    return admin->checkIn(a,password);
}

bool Controller::dbCaricato() const{
    return database->getCaricato();
}


