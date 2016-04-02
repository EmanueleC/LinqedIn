#include "database.h"
#include "basic.h"
#include "business.h"
#include "executive.h"

Database::Database(): caricato(false) {}


void Database::inserisciUtente(const SmartUtente & us){
    database.push_back(us);
}

void Database::eliminaUtente(QString username,int i){
    eliminaContattiIntEst(username);
    vector<SmartUtente>::iterator it = database.begin() + i;
    std::iter_swap(it,database.end().operator --());
    database.pop_back();
}

vector<QString> Database::cercaNome(QString nome) const{
    vector<QString> nomi;
    if(!nome.isEmpty()){
        for(unsigned int i=0; i<database.size(); ++i)
            if(QString::compare(database[i]->getProfilo().getNome(),nome,Qt::CaseInsensitive) == 0) nomi.push_back(database[i]->getUsername());
    }
    return nomi;
}

vector<QString> Database::cercaCognome(QString cognome) const{
    vector<QString> cognomi;
    if(!cognome.isEmpty()){
        for(unsigned int i=0; i<database.size(); ++i)
            if(QString::compare(database[i]->getProfilo().getCognome(),cognome,Qt::CaseInsensitive) == 0) cognomi.push_back(database[i]->getUsername());
    }
    return cognomi;
}

vector<QString> Database::cercaProvincia(QString provincia) const{
    vector<QString> province;
    if(!provincia.isEmpty()){
        for(unsigned int i=0; i<database.size(); ++i)
            if(QString::compare(database[i]->getProfilo().getProvincia(),provincia,Qt::CaseInsensitive) == 0) province.push_back(database[i]->getUsername());
    }
    return province;
}

vector<QString> Database::cercaAzienda(QString azienda) const{
    vector<QString> aziende;
    if(!azienda.isEmpty()){
        for(unsigned int i=0; i<database.size(); ++i){
            for(unsigned int j=0; j<database[i]->getProfilo().getEsp().size(); ++j)
                if(QString::compare(database[i]->getProfilo().getEsp()[j].getNomeAzienda(),azienda,Qt::CaseInsensitive) == 0)   aziende.push_back(database[i]->getUsername());
        }
    }
    return aziende;
}

vector<QString> Database::cercaTitolo(QString titolo) const{
    vector<QString> Titoli;
    if(!titolo.isEmpty()){
        for(unsigned int i=0; i<database.size(); ++i){
            for(unsigned int j=0; j<database[i]->getProfilo().getVecTitolo().size(); ++j)
                if(QString::compare(database[i]->getProfilo().getVecTitolo()[j].getTitolo(),titolo,Qt::CaseInsensitive) == 0)   Titoli.push_back(database[i]->getUsername());
        }
    }
    return Titoli;
}

vector<QString> Database::cercaArea(QString area) const{
    vector<QString> aree;
    if(!area.isEmpty()){
        for(unsigned int i=0; i<database.size(); ++i){
            for(unsigned int j=0; j<database[i]->getProfilo().getVecTitolo().size(); ++j)
                if(QString::compare(database[i]->getProfilo().getVecTitolo()[j].getAreaStudio(),area,Qt::CaseInsensitive) == 0)   aree.push_back(database[i]->getUsername());
        }
    }
    return aree;
}

SmartUtente Database::cercaUsername(QString username) const{
    for(unsigned int i=0; i<database.size(); ++i)
        if(QString::compare(database[i]->getUsername(),username,Qt::CaseSensitive) == 0) return database[i];
    return 0;
}

vector<QString> Database::cerca(QString nome, QString cognome, QString provincia, QString azienda, QString titolo, QString area){
    vector<QString> risultati;
    if(!(nome.size() == 0 && cognome.size() == 0 && provincia.size() == 0 && azienda.size() == 0 && titolo.size() == 0 && area.size() == 0))
    {
    for(unsigned int i=0; i<database.size(); ++i){
            if((QString::compare(database[i]->getProfilo().getNome(),nome,Qt::CaseInsensitive)==0 || nome.size()==0) && (QString::compare(database[i]->getProfilo().getCognome(),cognome,Qt::CaseInsensitive)==0 || cognome.size()==0) && (QString::compare(database[i]->getProfilo().getProvincia(),provincia,Qt::CaseInsensitive)==0 || provincia.size()==0)){
                bool r1 = false;
                for(unsigned int j=0; j<cercaAzienda(azienda).size(); ++j){
                    if(QString::compare(database[i]->getUsername(),cercaAzienda(azienda)[j])==0)   r1=true;
                }
                if(r1 || azienda.size() == 0){
                    bool r2 = false;
                    for(unsigned int j=0; j<cercaTitolo(titolo).size(); ++j){
                        if(QString::compare(database[i]->getUsername(),cercaTitolo(titolo)[j])==0)   r2=true;
                    }
                    if(r2 || titolo.size() == 0){
                        bool r3 = false;
                        for(unsigned int j=0; j<cercaArea(area).size(); ++j){
                            if(QString::compare(database[i]->getUsername(),cercaArea(area)[j])==0)   r3=true;
                        }
                        if(r3 || area.size() == 0) risultati.push_back(database[i]->getUsername());
                    }
                }
            }
        }
    }
    return risultati;
}

bool Database::checkUsername(QString username) const{
    for(unsigned int i=0; i<database.size(); ++i){
        if(database[i]->getUsername() == username)  return false;
        }
    return true;
}

bool Database::checkIn(QString username, QString password) const{
    for(unsigned int i=0; i<database.size(); ++i){
        if(database[i]->getUsername() == username && database[i]->getPassword() == password) return true;
    }
    return false;
}

vector<QString> Database::listaUsername() const{
    vector<QString> username;
    for(unsigned int i=0; i<database.size(); ++i){
        username.push_back(database[i]->getUsername());
    }
    return username;
}

void Database::cambiaTipoAccount(QString username, int x){
    for(unsigned int i=0; i<database.size(); ++i){
        if(database[i]->getUsername() == username){
            QString text = "Il cambio di tipologia di account è andato a buon fine.";
            Messaggio m("LinQedIn", text);
            database[i]->inserisciMessaggio(m);
            switch(x){
                case 1: {
                    SmartUtente basic(new Basic(*database[i]));
                    database[i] = basic; // assegnazione tra SmartUtente
                    }
                    break;
                case 2: {
                    SmartUtente business(new Business(*database[i]));
                    database[i] = business; // assegnazione tra SmartUtente
                    }
                    break;
                case 3: {
                    SmartUtente executive(new Executive(*database[i]));
                    database[i] = executive; // assegnazione tra SmartUtente
                    }
                    break;
            }
        }
    }
}

void Database::eliminaContattiIntEst(QString username) const{
    for(unsigned int i=0; i<database.size(); ++i){
        for(unsigned int j=0; j<database[i]->getRete()->getListaContatti().size(); j++){
            if(database[i]->getRete()->getListaContatti()[j] == username) database[i]->getRete()->remove(username);
        }
        for(unsigned int k=0; k<database[i]->getContattiEst().size(); k++){
            if(database[i]->getContattiEst()[k] == username) database[i]->eliminaContattoEst(username);
        }
    }
}

bool Database::writeXML(){
    QXmlStreamWriter xmlWriter;
    QFile file("Output.xml");
    if((file.open(QFile::WriteOnly))){
          xmlWriter.setDevice(&file);
          xmlWriter.setAutoFormatting(true);
          xmlWriter.writeStartDocument();
          xmlWriter.writeStartElement("Utenti");
          for(unsigned int i=0; i<database.size(); ++i)
          {
            xmlWriter.writeStartElement("Utente");
            xmlWriter.writeStartElement("Tipo");
            xmlWriter.writeCharacters(QString::number(database[i]->tipoUtente()));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Nome");
            xmlWriter.writeCharacters(database[i]->getProfilo().getNome());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Cognome");
            xmlWriter.writeCharacters(database[i]->getProfilo().getCognome());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Username");
            xmlWriter.writeCharacters(database[i]->getUsername());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Password");
            xmlWriter.writeCharacters(database[i]->getPassword());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Sesso");
            xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().Uomo()));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Giorno");
            xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getGiornoNascita()));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Mese");
            xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getMeseNascita()));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Anno");
            xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getAnnoNascita()));
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Provincia");
            xmlWriter.writeCharacters(database[i]->getProfilo().getProvincia());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("E-Mail");
            xmlWriter.writeCharacters(database[i]->getProfilo().getEmail());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Telefono");
            xmlWriter.writeCharacters(database[i]->getProfilo().getTelefono());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Sito");
            xmlWriter.writeCharacters(database[i]->getProfilo().getSito());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Lingue");
            xmlWriter.writeCharacters(database[i]->getProfilo().getLingue());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Interessi");
            xmlWriter.writeCharacters(database[i]->getProfilo().getInteressi());
            xmlWriter.writeEndElement();
            xmlWriter.writeStartElement("Titoli");
            xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getVecTitolo().size()));
            xmlWriter.writeEndElement();
            for(unsigned int k=0; k<database[i]->getProfilo().getVecTitolo().size(); ++k)
            {
                xmlWriter.writeStartElement("Titolo"+QString::number(k));
                xmlWriter.writeCharacters(database[i]->getProfilo().getVecTitolo()[k].getTitolo());
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("Istituzione"+QString::number(k));
                xmlWriter.writeCharacters(database[i]->getProfilo().getVecTitolo()[k].getIstituzione());
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("AreaStudio"+QString::number(k));
                xmlWriter.writeCharacters(database[i]->getProfilo().getVecTitolo()[k].getAreaStudio());
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("Descrizione"+QString::number(k));
                xmlWriter.writeCharacters(database[i]->getProfilo().getVecTitolo()[k].getDescrizione());
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("Giorno"+QString::number(k));
                xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getVecTitolo()[k].getData().getGiorno()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("Mese"+QString::number(k));
                xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getVecTitolo()[k].getData().getMese()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("Anno"+QString::number(k));
                xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getVecTitolo()[k].getData().getAnno()));
                xmlWriter.writeEndElement();
            }
            xmlWriter.writeStartElement("Esperienze");
            xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getEsp().size()));
            xmlWriter.writeEndElement();
            for(unsigned int k=0; k<database[i]->getProfilo().getEsp().size(); ++k)
            {
                xmlWriter.writeStartElement("Esperienza"+QString::number(k));
                xmlWriter.writeCharacters(database[i]->getProfilo().getEsp()[k].getDescrizione());
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("NomeAzienda"+QString::number(k));
                xmlWriter.writeCharacters(database[i]->getProfilo().getEsp()[k].getNomeAzienda());
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("Luogo"+QString::number(k));
                xmlWriter.writeCharacters(database[i]->getProfilo().getEsp()[k].getLuogo());
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("GiornoInizio"+QString::number(k));
                xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getEsp()[k].getInizioLavoro().getGiorno()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("MeseInizio"+QString::number(k));
                xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getEsp()[k].getInizioLavoro().getMese()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("AnnoInizio"+QString::number(k));
                xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getEsp()[k].getInizioLavoro().getAnno()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("GiornoFine"+QString::number(k));
                xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getEsp()[k].getFineLavoro().getGiorno()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("MeseFine"+QString::number(k));
                xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getEsp()[k].getFineLavoro().getMese()));
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement("AnnoFine"+QString::number(k));
                xmlWriter.writeCharacters(QString::number(database[i]->getProfilo().getEsp()[k].getFineLavoro().getAnno()));
                xmlWriter.writeEndElement();
            }
            xmlWriter.writeStartElement("Contatti");
            xmlWriter.writeCharacters(QString::number(database[i]->getRete()->sizeRete()));
            xmlWriter.writeEndElement();
            for(unsigned int j=0; j<database[i]->getRete()->sizeRete(); ++j){
                xmlWriter.writeStartElement("Contatto"+QString::number(j));
                xmlWriter.writeCharacters(database[i]->getRete()->getListaContatti()[j]);
                xmlWriter.writeEndElement();
            }
            xmlWriter.writeStartElement("ContattiEst");
            xmlWriter.writeCharacters(QString::number(database[i]->getContattiEst().size()));
            xmlWriter.writeEndElement();
            for(unsigned int k=0; k<database[i]->getContattiEst().size(); ++k){
                xmlWriter.writeStartElement("ContattoEst"+QString::number(k));
                xmlWriter.writeCharacters(database[i]->getContattiEst()[k]);
                xmlWriter.writeEndElement();
            }
            xmlWriter.writeStartElement("NumMessaggi");
            xmlWriter.writeCharacters(QString::number(database[i]->getNumMessaggi()));
            xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndDocument();
        return true;
    }
    else{
        return false;
    }
}

bool Database::loadXML(){
    QXmlStreamReader xmlReader;
    QFile file("Output.xml");
    if((file.open(QFile::ReadOnly))){
    xmlReader.setDevice(&file);
    int nmax= 10000, i=0;
    QString nome, cognome, username, password, provincia, email, telefono, sito, lingue, interessi, esp, azienda, luogo, titolo, istituzione, descTitolo, areaStudio;
    int giorno, mese, anno, gi, mi, ai, gf, mf, af, gt, mt, at;
    unsigned int sizeEsp, sizeTitoli, tipo, num_mex;
    bool uomo;
    int sizeRete, sizeContattiEst; QString usernameContatto, usernameContattoEst; vector<QString> rete, contattiEst;
    vector<Esperienze> v;
    vector<titoli> vt;
    while(!xmlReader.atEnd() && i<nmax)
    {
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="Tipo") tipo = xmlReader.readElementText().toInt();
            if(xmlReader.name()=="Nome") nome = xmlReader.readElementText();
            if(xmlReader.name()=="Cognome") cognome = xmlReader.readElementText();
            if(xmlReader.name()=="Username") username = xmlReader.readElementText();
            if(xmlReader.name()=="Password") password = xmlReader.readElementText();
            if(xmlReader.name()=="Sesso") uomo = xmlReader.readElementText().toInt();
            if(xmlReader.name()=="Giorno") giorno = xmlReader.readElementText().toInt();
            if(xmlReader.name()=="Mese") mese = xmlReader.readElementText().toInt();
            if(xmlReader.name()=="Anno") anno = xmlReader.readElementText().toInt();
            if(xmlReader.name()=="Provincia") provincia = xmlReader.readElementText();
            if(xmlReader.name()=="E-Mail") email = xmlReader.readElementText();
            if(xmlReader.name()=="Telefono") telefono = xmlReader.readElementText();
            if(xmlReader.name()=="Sito") sito = xmlReader.readElementText();
            if(xmlReader.name()=="Lingue") lingue = xmlReader.readElementText();
            if(xmlReader.name()=="Interessi") interessi = xmlReader.readElementText();
            if(xmlReader.name()=="Titoli"){
                sizeTitoli = xmlReader.readElementText().toInt();
            xmlReader.readNext(); xmlReader.readNext();
            for(unsigned int k=0; k<sizeTitoli; ++k){
                titolo = xmlReader.readElementText(); xmlReader.readNext(); xmlReader.readNext();
                istituzione = xmlReader.readElementText(); xmlReader.readNext(); xmlReader.readNext();
                areaStudio = xmlReader.readElementText(); xmlReader.readNext(); xmlReader.readNext();
                descTitolo = xmlReader.readElementText(); xmlReader.readNext(); xmlReader.readNext();
                gt = xmlReader.readElementText().toInt(); xmlReader.readNext(); xmlReader.readNext();
                mt = xmlReader.readElementText().toInt(); xmlReader.readNext(); xmlReader.readNext();
                at = xmlReader.readElementText().toInt(); xmlReader.readNext(); xmlReader.readNext();
                Data dataTitolo(gt,mt,at);
                vt.push_back(titoli(titolo, istituzione, descTitolo, areaStudio, dataTitolo));
                }
            }
            if(xmlReader.name()=="Esperienze"){ sizeEsp = xmlReader.readElementText().toInt();
            xmlReader.readNext(); xmlReader.readNext();
            for(unsigned int k=0; k<sizeEsp; ++k){
                esp = xmlReader.readElementText(); xmlReader.readNext(); xmlReader.readNext();
                azienda = xmlReader.readElementText(); xmlReader.readNext(); xmlReader.readNext();
                luogo = xmlReader.readElementText(); xmlReader.readNext(); xmlReader.readNext();
                gi = xmlReader.readElementText().toInt();  xmlReader.readNext(); xmlReader.readNext();
                mi = xmlReader.readElementText().toInt();  xmlReader.readNext(); xmlReader.readNext();
                ai = xmlReader.readElementText().toInt();  xmlReader.readNext(); xmlReader.readNext();
                gf = xmlReader.readElementText().toInt();  xmlReader.readNext(); xmlReader.readNext();
                mf = xmlReader.readElementText().toInt();  xmlReader.readNext(); xmlReader.readNext();
                af = xmlReader.readElementText().toInt();  xmlReader.readNext(); xmlReader.readNext();
                Data inizio(gi,mi,ai); Data fine(gf,mf,af);
                v.push_back(Esperienze(esp, azienda, luogo, inizio,fine));
                }
            }
            if(xmlReader.name()=="Contatti"){ sizeRete = xmlReader.readElementText().toInt(); xmlReader.readNext();xmlReader.readNext();
                for(unsigned int j=0; j<sizeRete; ++j){
                    if(xmlReader.name()=="Contatto"+QString::number(j)){ usernameContatto = xmlReader.readElementText(); rete.push_back(usernameContatto); }
                    xmlReader.readNext(); xmlReader.readNext();
                }
            }
            if(xmlReader.name()=="ContattiEst"){ sizeContattiEst = xmlReader.readElementText().toInt(); xmlReader.readNext();xmlReader.readNext();
                for(unsigned int k=0; k<sizeContattiEst; ++k){
                    if(xmlReader.name()=="ContattoEst"+QString::number(k)){ usernameContattoEst = xmlReader.readElementText(); contattiEst.push_back(usernameContattoEst); }
                    xmlReader.readNext(); xmlReader.readNext();
                }
            }
            if(xmlReader.name()=="NumMessaggi") num_mex = xmlReader.readElementText().toInt();
        }
        if(xmlReader.isEndElement() && xmlReader.name()=="Utente"){
            Data data_temp(giorno, mese, anno);
            Info info_temp(nome, cognome, email, provincia, uomo, telefono, data_temp);
            Curriculum curriculum_temp(lingue, vt, interessi, sito, v);
            Profilo profilo_temp(info_temp, curriculum_temp);
            switch(tipo){
                case 1: {  SmartUtente temp = SmartUtente(new Basic(username, password, profilo_temp)); temp->setRete(rete); temp->setNumMessaggi(num_mex); temp->setContattiEst(contattiEst); database.push_back(temp); break; }
                case 2: {  SmartUtente temp = SmartUtente(new Business(username, password, profilo_temp)); temp->setRete(rete); temp->setNumMessaggi(num_mex); temp->setContattiEst(contattiEst); database.push_back(temp); break; }
                case 3: {  SmartUtente temp = SmartUtente(new Executive(username, password, profilo_temp)); temp->setRete(rete); temp->setNumMessaggi(num_mex); temp->setContattiEst(contattiEst); database.push_back(temp); break; }
            }
            vt.clear();
            v.clear();
            rete.clear();
            contattiEst.clear();
            // istruzioni importanti!
        }
        xmlReader.readNext();
    }
    caricato = true;
    return true;
   }
    else    return false;
}

bool Database::getCaricato() const{
    return caricato;
}
