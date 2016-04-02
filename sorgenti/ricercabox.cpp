#include "ricercabox.h"
#include "userwindow.h"

ricercabox::ricercabox(Controller * c, UserWindow* u, bool completa): controller(c), user(u), completa(completa)
{
    QGroupBox* rBox = new QGroupBox;
    QVBoxLayout* rLayout = new QVBoxLayout;
    QLabel* ricerca_nome = new QLabel("Nome: ");
    QLabel* ricerca_cognome = new QLabel("Cognome: ");
    QLabel* ricerca_username = new QLabel("Nome utente: ");
    QLabel* ricerca_provincia = new QLabel("Provincia: ");
    QLabel* ricerca_azienda = new QLabel("Azienda: ");
    QLabel* ricerca_titolo = new QLabel("Titolo di studio: ");
    QLabel* ricerca_area = new QLabel("Area di studio: ");
    ricercaLayout = new QGridLayout;
    nomeCercato = new QLineEdit;
    cognomeCercato = new QLineEdit;
    usernameCercato = new QLineEdit;
    provinciaCercata = new QLineEdit;
    aziendaCercata = new QLineEdit;
    titoloStudio = new QLineEdit;
    areaStudio = new QLineEdit;
    QPushButton* cercaNome_button = new QPushButton("cerca Utente");
    QPushButton* cercaCognome_button = new QPushButton("cerca Utente");
    QPushButton* cercaUsername_button = new QPushButton("cerca Utente");
    QPushButton* cercaProvincia_button = new QPushButton("cerca Utente");
    // solo per l'admin e gli account executive
    QPushButton* cerca = new QPushButton("Ricerca Combinata");
    QPushButton* cercaAzienda_button = new QPushButton("cerca Utente");
    QPushButton* cercaTitolo_button = new QPushButton("cerca Utente");
    QPushButton* cercaAreaStudio_button = new QPushButton("cerca Utente");
    nascondi = new QPushButton("Nascondi risultati ricerca");
    connect(cercaNome_button, SIGNAL(clicked()), this, SLOT(ricercaNome()));
    connect(cercaCognome_button, SIGNAL(clicked()), this, SLOT(ricercaCognome()));
    connect(cercaUsername_button, SIGNAL(clicked()), this, SLOT(ricercaUsername()));
    connect(cercaProvincia_button, SIGNAL(clicked()), this, SLOT(ricercaProvincia()));
    connect(cercaAzienda_button, SIGNAL(clicked()), this, SLOT(ricercaAzienda()));
    connect(cercaTitolo_button, SIGNAL(clicked()), this, SLOT(ricercaTitolo()));
    connect(cercaAreaStudio_button, SIGNAL(clicked()), this, SLOT(ricercaArea()));
    connect(cerca, SIGNAL(clicked()), this, SLOT(ricercaCombinata()));
    connect(nascondi, SIGNAL(clicked()), this, SLOT(nascondiTesto()));
    infoText = new QTextEdit;
    infoText->setReadOnly(true);
    infoText->setFrameStyle(QFrame::Box);
    QLabel* labelRicerca = new QLabel("<b> Ricerca Utente in LinQedIn </b>");
    labelRicerca->setStyleSheet("font: 12pt;");
    ricercaLayout->addWidget(labelRicerca,0,1,1,6,Qt::AlignCenter);
    ricercaLayout->addWidget(ricerca_nome,1,0);
    ricercaLayout->addWidget(ricerca_cognome,2,0);
    ricercaLayout->addWidget(ricerca_username,4,0);
    ricercaLayout->addWidget(nomeCercato,1,1,1,2);
    ricercaLayout->addWidget(cercaNome_button,1,3);
    ricercaLayout->addWidget(cognomeCercato,2,1,1,2);
    ricercaLayout->addWidget(cercaCognome_button,2,3);
    if(completa || (controller->utenteCaricato() && controller->getTipoUtente()>=2))
    {
        ricercaLayout->addWidget(ricerca_provincia,3,0);
        ricercaLayout->addWidget(provinciaCercata,3,1,1,2);
        ricercaLayout->addWidget(cercaProvincia_button,3,3);
        ricercaLayout->addWidget(ricerca_azienda,1,4);
        ricercaLayout->addWidget(aziendaCercata,1,5,1,2);
        ricercaLayout->addWidget(cercaAzienda_button,1,7);
        ricercaLayout->addWidget(ricerca_titolo,2,4);
        ricercaLayout->addWidget(titoloStudio,2,5,1,2);
        ricercaLayout->addWidget(cercaTitolo_button,2,7);
        ricercaLayout->addWidget(ricerca_area,3,4);
        ricercaLayout->addWidget(areaStudio,3,5,1,2);
        ricercaLayout->addWidget(cercaAreaStudio_button,3,7);

    }
    ricercaLayout->addWidget(usernameCercato,4,1,1,2);
    ricercaLayout->addWidget(cercaUsername_button,4,3);
    ricercaLayout->addWidget(infoText,5,0,1,6);
    if(completa || (controller->utenteCaricato() && controller->getTipoUtente()==3)) ricercaLayout->addWidget(cerca,5,6);
    ricercaLayout->addWidget(nascondi,6,6);
    rBox->setLayout(ricercaLayout);
    rBox->setObjectName("RicercaBox");
    rBox->setStyleSheet(QString::fromUtf8("QWidget#RicercaBox\n{\nborder: 3px groove grey;\n}\n"));
    rLayout->addWidget(rBox);
    setLayout(rLayout);
    infoText->hide();
    nascondi->hide();
}

void ricercabox::ricercaUsername() const{
    if(user)    user->nascondiReteButton();
    if(!completa)    infoText->setText(controller->getDatiRicerca(controller->cercaUsername(usernameCercato->text())));
    else    infoText->setText(controller->getAllDati(controller->cercaUsername(usernameCercato->text())));
    if(user && infoText->toPlainText()!= "Utente non presente nel database" && QString::compare(usernameCercato->text(),controller->getUsername(),Qt::CaseSensitive) != 0 )
        // se la ricerca è stata effettuata da un utente e non dall'amministratore
        user->mostraReteButton();
    infoText->show();
    nascondi->show();
}

void ricercabox::ricercaNome() const{
    if(user) user->nascondiReteButton();
    QString nomi = "";
    vector<QString> n = controller->cercaNome(nomeCercato->text());
    if(n.size() == 0) nomi = "Utente non presente nel database.";
    else if(n.size() == 1 && !completa) nomi = controller->getDatiRicerca(controller->cercaUsername(n[0]));
    else if(n.size() == 1 && completa)  nomi = controller->getAllDati(controller->cercaUsername(n[0]));
    else if(n.size()>1){
    for(unsigned int i=0; i<n.size(); i++){
        nomi = nomi + "*****\n" + QString::number(i+1) + "° utente con nome specificato \n\n";
        if(!completa)   nomi = nomi + controller->getDatiRicerca(controller->cercaUsername(n[i])) + "\n\n";
        else            nomi = nomi + controller->getAllDati(controller->cercaUsername(n[i])) + "\n\n";
        }
    }
    infoText->show();
    nascondi->show();
    infoText->setText(nomi);
}

void ricercabox::ricercaCognome() const{
    if(user) user->nascondiReteButton();
    QString cognomi = "";
    vector<QString> c = controller->cercaCognome(cognomeCercato->text());
    if(c.size() == 0) cognomi = "Utente non presente nel database.";
    else if(c.size() == 1 && !completa) cognomi = controller->getDatiRicerca(controller->cercaUsername(c[0]));
    else if(c.size() == 1 && completa) cognomi = controller->getAllDati(controller->cercaUsername(c[0]));
    else if(c.size()>1){
    for(unsigned int i=0; i<c.size(); i++){
        cognomi = cognomi + "*****\n" + QString::number(i+1) + "° utente con cognome specificato \n\n";
                if(!completa)   cognomi = cognomi + controller->getDatiRicerca(controller->cercaUsername(c[i])) + "\n\n";
                else           cognomi = cognomi + controller->getAllDati(controller->cercaUsername(c[i])) + "\n\n";
        }
    }
    infoText->show();
    nascondi->show();
    infoText->setText(cognomi);
}

void ricercabox::ricercaProvincia() const{
    if(user) user->nascondiReteButton();
    QString province = "";
    vector<QString> p = controller->cercaProvincia(provinciaCercata->text());
    if(p.size() == 0) province = "Utente non presente nel database.";
    else if(p.size() == 1 && !completa) province = controller->getDatiRicerca(controller->cercaUsername(p[0]));
    else if(p.size() == 1 && completa)  province = controller->getAllDati(controller->cercaUsername(p[0]));
    else if(p.size()>1){
    for(unsigned int i=0; i<p.size(); i++){
        province = province + "*****\n" + QString::number(i+1) + "° utente con provincia specificata \n\n";
                if(!completa)   province = province + controller->getDatiRicerca(controller->cercaUsername(p[i])) + "\n\n";
                else           province = province + controller->getAllDati(controller->cercaUsername(p[i])) + "\n\n";
        }
    }
    infoText->show();
    nascondi->show();
    infoText->setText(province);
}

void ricercabox::ricercaAzienda() const{
    if(user) user->nascondiReteButton();
    QString aziende = "";
    vector<QString> a = controller->cercaAzienda(aziendaCercata->text());
    if(a.size() == 0) aziende = "Utente non presente nel database.";
    else if(a.size() == 1 && !completa) aziende = controller->getDatiRicerca(controller->cercaUsername(a[0]));
    else if(a.size() == 1 && completa)  aziende = controller->getAllDati(controller->cercaUsername(a[0]));
    else if(a.size()>1){
    for(unsigned int i=0; i<a.size(); i++){
        aziende = aziende + "*****\n" + QString::number(i+1) + "° utente con provincia specificata \n\n";
                if(!completa)   aziende = aziende + controller->getDatiRicerca(controller->cercaUsername(a[i])) + "\n\n";
                else           aziende = aziende + controller->getAllDati(controller->cercaUsername(a[i])) + "\n\n";
        }
    }
    infoText->show();
    nascondi->show();
    infoText->setText(aziende);
}

void ricercabox::ricercaTitolo() const{
    if(user) user->nascondiReteButton();
    QString Titoli = "";
    vector<QString> t = controller->cercaTitolo(titoloStudio->text());
    if(t.size() == 0) Titoli = "Utente non presente nel database.";
    else if(t.size() == 1 && !completa) Titoli = controller->getDatiRicerca(controller->cercaUsername(t[0]));
    else if(t.size() == 1 && completa)  Titoli = controller->getAllDati(controller->cercaUsername(t[0]));
    else if(t.size()>1){
    for(unsigned int i=0; i<t.size(); i++){
        Titoli = Titoli + "*****\n" + QString::number(i+1) + "° utente con titolo specificato \n\n";
                if(!completa)   Titoli = Titoli + controller->getDatiRicerca(controller->cercaUsername(t[i])) + "\n\n";
                else           Titoli = Titoli + controller->getAllDati(controller->cercaUsername(t[i])) + "\n\n";
        }
    }
    infoText->show();
    nascondi->show();
    infoText->setText(Titoli);
}

void ricercabox::ricercaArea() const{
    if(user) user->nascondiReteButton();
    QString aree = "";
    vector<QString> a = controller->cercaArea(areaStudio->text());
    if(a.size() == 0) aree = "Utente non presente nel database.";
    else if(a.size() == 1 && !completa) aree = controller->getDatiRicerca(controller->cercaUsername(a[0]));
    else if(a.size() == 1 && completa)  aree = controller->getAllDati(controller->cercaUsername(a[0]));
    else if(a.size()>1){
    for(unsigned int i=0; i<a.size(); i++){
        aree = aree + "*****\n" + QString::number(i+1) + "° utente con titolo specificato \n\n";
                if(!completa)   aree = aree + controller->getDatiRicerca(controller->cercaUsername(a[i])) + "\n\n";
                else           aree = aree + controller->getAllDati(controller->cercaUsername(a[i])) + "\n\n";
        }
    }
    infoText->show();
    nascondi->show();
    infoText->setText(aree);
}

void ricercabox::ricercaCombinata() const{
    if(user) user->nascondiReteButton();
    QString risultati = "";
    vector<QString> r  = controller->cerca(nomeCercato->text(), cognomeCercato->text(), provinciaCercata->text(), aziendaCercata->text(), titoloStudio->text(), areaStudio->text());
    if(r.size() == 0) risultati = "Utente non presente nel database.";
    else if(r.size() == 1 && !completa) risultati = controller->getDatiRicerca(controller->cercaUsername(r[0]));
    else if(r.size() == 1 && completa)  risultati = controller->getAllDati(controller->cercaUsername(r[0]));
    else if(r.size()>1){
    for(unsigned int i=0; i<r.size(); i++){
        risultati = risultati + "*****\n" + QString::number(i+1) + "° utente con dati specificati \n\n";
                if(!completa)   risultati = risultati + controller->getDatiRicerca(controller->cercaUsername(r[i])) + "\n\n";
                else           risultati = risultati + controller->getAllDati(controller->cercaUsername(r[i])) + "\n\n";
        }
    }
    infoText->show();
    nascondi->show();
    infoText->setText(risultati);
}

void ricercabox::nascondiTesto() const{
    infoText->hide();
    nascondi->hide();
}

QString ricercabox::getText() const{
    return infoText->toPlainText();
}

QString ricercabox::getUsername() const{
    return usernameCercato->text();
}
