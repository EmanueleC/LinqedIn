#include "userwindow.h"

UserWindow::UserWindow(Controller* c): controller(c), ricercaBox(new ricercabox(controller,this))
{
    layout = new QVBoxLayout;
    QGridLayout* griglia = new QGridLayout;
    QGroupBox* boxDati = new QGroupBox;
    boxDati->setObjectName("BoxDati");
    QLabel* intestazione = new QLabel;
    notifiche = new QPushButton("Notifiche");
    notifiche->hide();
    QPushButton* aggiorna = new QPushButton("Aggiorna");
    aggiorna->setStyleSheet("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 green, stop: 1 white);");
    intestazione->setStyleSheet("font: 17pt;");
    if(controller->Uomo())
        intestazione->setText("Benvenuto, "+controller->getNomeUtente());
    else
        intestazione->setText("Benvenuta, "+controller->getNomeUtente());
    intestazione->setAlignment(Qt::AlignRight);
    QPushButton* mostraProfilo = new QPushButton("Mostra Profilo");
    connect(mostraProfilo, SIGNAL(clicked()), this, SLOT(mostraProfilo()));
    QPushButton* modificaProfilo = new QPushButton("Modifica Profilo");
    connect(modificaProfilo, SIGNAL(clicked()), this, SLOT(modifica()));
    mostraDati = new QTextEdit;
    mostraDati->setReadOnly(true);
    mostraDati->setFrameStyle(QFrame::Box);
    griglia->addWidget(intestazione,0,0);
    QLabel* labelDati = new QLabel("<b> Informazioni sul profilo </b>");
    labelDati->setStyleSheet("font: 12pt;");
    griglia->addWidget(labelDati,0,0,1,2,Qt::AlignCenter);
    griglia->addWidget(mostraProfilo,1,0);
    griglia->addWidget(modificaProfilo,2,0);
    griglia->addWidget(mostraDati,1,1,4,1);
    griglia->addWidget(notifiche,3,0);
    aggiungi = new QPushButton("aggiungi contatto");
    aggiungi->setStyleSheet("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 red, stop: 1 white);");
    aggiungi->hide();
    connect(aggiungi, SIGNAL(clicked()), this, SLOT(inserisciContatto()));
    connect(notifiche, SIGNAL(clicked()), this, SLOT(mostraNotifiche()));
    connect(aggiorna, SIGNAL(clicked()), this, SLOT(aggiorna()));
    QGroupBox* boxButtons = new QGroupBox;
    QHBoxLayout* hLayout = new QHBoxLayout;
    mostraRete = new QPushButton("Mostra Rete LinqedIn");
    nascondiRete = new QPushButton("Nascondi Rete LinqedIn");
    QPushButton* mostraContattiEst = new QPushButton("Nelle reti di... ");
    hLayout->addWidget(mostraRete,0,Qt::AlignCenter);
    hLayout->addWidget(nascondiRete,0,Qt::AlignCenter);
    hLayout->addWidget(mostraContattiEst,0,Qt::AlignCenter);
    boxButtons->setLayout(hLayout);
    connect(mostraRete, SIGNAL(clicked()), this, SLOT(mostraContatti()));
    connect(nascondiRete, SIGNAL(clicked()), this, SLOT(nascondiContatti()));
    connect(mostraContattiEst, SIGNAL(clicked()), this, SLOT(contattiEst()));
    mostraReteInfo = new QTextEdit;
    mostraReteInfo->setReadOnly(true);
    mostraReteInfo->setFrameStyle(QFrame::Box);
    reteBox = new ReteBox(controller);
    reteBox->hide();
    boxDati->setLayout(griglia);
    boxDati->setStyleSheet(QString::fromUtf8("QWidget#BoxDati\n{\nborder: 3px groove grey;\n}\n"));
    layout->addWidget(intestazione);
    layout->addWidget(boxDati);
    layout->addWidget(ricercaBox);
    layout->addWidget(aggiungi,0,Qt::AlignCenter);
    QLabel* reteLabel = new QLabel("<b> Rete LinQedIn </b>");
    reteLabel->setStyleSheet("font: 12pt");
    QGroupBox* ExtReteBox = new QGroupBox;
    QVBoxLayout* reteLayout = new QVBoxLayout;
    reteLayout->addWidget(reteLabel,0,Qt::AlignCenter);
    reteLayout->addWidget(boxButtons);
    reteLayout->addWidget(reteBox);
    ExtReteBox->setLayout(reteLayout);
    ExtReteBox->setObjectName("ExtReteBox");
    ExtReteBox->setStyleSheet(QString::fromUtf8("QWidget#ExtReteBox\n{\nborder: 3px groove grey;\n}\n"));
    layout->addWidget(ExtReteBox);
    QPushButton* cambiaTipo = new QPushButton("Cambia tipologia account");
    QPushButton* scrivi = new QPushButton("Scrivi un messaggio \n a un contatto LinQedIn");
    scrivi->setStyleSheet("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightyellow, stop: 1 white);");
    if(controller->getTipoUtente()<2) scrivi->hide();
    connect(cambiaTipo, SIGNAL(clicked()), this, SLOT(creaScelteBox()) );
    connect(scrivi, SIGNAL(clicked()), this, SLOT(scriviMessaggio()) );
    layout->addWidget(cambiaTipo,0,Qt::AlignCenter);
    layout->addWidget(aggiorna,0,Qt::AlignCenter);
    QLabel* tipo = new QLabel;
    tipo->setStyleSheet("font: 10pt; color: blue;");
    switch(controller->getTipoUtente()){
        case 1: tipo->setText("Account Basic"); break;
        case 2: tipo->setText("Account Business"); break;
        case 3: tipo->setText("Account Executive"); break;
    }
    layout->addWidget(scrivi,0,Qt::AlignRight);
    layout->addWidget(tipo,0,Qt::AlignBaseline);
    layout->addStretch();
    nascondiRete->hide();
    setLayout(layout);
    finestraMessaggi = new messaggiwindow(controller);
    UserWindow::aggiorna();
}

void UserWindow::mostraProfilo() const{
    mostraDati->setText(controller->getDatiUtente());
}

void UserWindow::mostraReteButton() const{
    aggiungi->show();
}

void UserWindow::nascondiReteButton() const{
    aggiungi->hide();
}

void UserWindow::inserisciContatto(){
    if(controller->inserisciContatto(controller->cercaUsername(ricercaBox->getUsername())))
     reteBox->aggiorna();
    else{
        QMessageBox* message = new QMessageBox;
        message->setText("Si è verificato un errore. Utente già presente nella rete o non presente nel database. ");
        message->show();
    }
    aggiungi->hide();
}

void UserWindow::mostraContatti() const{
    reteBox->aggiorna();
    reteBox->setVisible(true);
    nascondiRete->show();
    mostraRete->hide();
}

void UserWindow::nascondiContatti() const{
    reteBox->hide();
    nascondiRete->hide();
    mostraRete->show();
}

void UserWindow::modifica(){
    FormClass* modificaDati = new FormClass(controller, false,0);
}

void UserWindow::creaScelteBox() const{
    if(!controller->utenteSalvato()){
        QMessageBox* message = new QMessageBox;
        message->setText("Impossibile cambiare tipo di account. Riprova più tardi.");
        message->show();
    }
    else
    {
        QGroupBox* scelte = new QGroupBox;
        QHBoxLayout* scelteLayout = new QHBoxLayout;
        QPushButton* basic = new QPushButton("Basic");
        QPushButton* business = new QPushButton("Business");
        QPushButton* executive = new QPushButton("Executive");
        switch(controller->getTipoUtente())
        {
            case 1: basic->setDisabled(true); break;
            case 2: business->setDisabled(true); break;
            case 3: executive->setDisabled(true); break;
        }
        scelteLayout->addWidget(new QLabel("Scegli tipo di account: "));
        scelteLayout->addWidget(basic, QDialogButtonBox::AcceptRole);
        scelteLayout->addWidget(business, QDialogButtonBox::AcceptRole);
        scelteLayout->addWidget(executive, QDialogButtonBox::AcceptRole);
        connect(basic, SIGNAL(clicked()), scelte, SLOT(close()));
        connect(basic, SIGNAL(clicked()), this, SLOT(tipoTargetBasic()));
        connect(basic, SIGNAL(clicked()), this, SLOT(cambiaTipo()));
        connect(business, SIGNAL(clicked()), scelte, SLOT(close()));
        connect(business, SIGNAL(clicked()), this, SLOT(tipoTargetBusiness()));
        connect(business, SIGNAL(clicked()), this, SLOT(cambiaTipo()));
        connect(executive, SIGNAL(clicked()), scelte, SLOT(close()));
        connect(executive, SIGNAL(clicked()), this, SLOT(tipoTargetExecutive()));
        connect(executive, SIGNAL(clicked()), this, SLOT(cambiaTipo()));
        scelte->setLayout(scelteLayout);
        scelte->show();
    }
}

void UserWindow::tipoTargetBasic(){
    tipoTarget = 1;
}

void UserWindow::tipoTargetBusiness(){
    tipoTarget = 2;
}

void UserWindow::tipoTargetExecutive(){
    tipoTarget = 3;
}

void UserWindow::cambiaTipo() const{
    controller->inserisciUtenteCambio(tipoTarget);
    QMessageBox* message = new QMessageBox;
    message->setText("<b> Attenzione, la preghiamo di uscire affinché il suo account possa essere cambiato dall'amministratore. </b> ");
    message->show();
}

void UserWindow::aggiorna() const{
    if(controller->checkNotifiche()!=0){
        notifiche->show();
        notifiche->setText("Hai "+QString::number(controller->checkNotifiche())+" nuove notifiche");
        notifiche->setStyleSheet("background-color: red");
    }
}

void UserWindow::mostraNotifiche() const{
    notifiche->show();
    notifiche->setText("Notifiche");
    notifiche->hide();
    QString notificheText = controller->getMessaggi();
    mostraDati->setText(notificheText);
    controller->cancellaMessaggi();
}

void UserWindow::scriviMessaggio() const{
    finestraMessaggi->aggiorna();
    finestraMessaggi->show();
}

void UserWindow::contattiEst(){
    QGroupBox* contattiEst = new QGroupBox;
    QVBoxLayout* contattiEstLayout = new QVBoxLayout;
    QLabel * t = new QLabel("<b> Ti hanno inserito fra i loro contatti: </b>");
    QLabel * c = new QLabel(controller->getContattiEst());
    contattiEstLayout->addWidget(t);
    contattiEstLayout->addWidget(c);
    contattiEst->setLayout(contattiEstLayout);
    contattiEst->show();
}
