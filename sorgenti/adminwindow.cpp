#include "adminwindow.h"
#include <iostream>

AdminWindow::AdminWindow(Controller* c): controller(c), ricercaBox(new ricercabox(controller,0,true))
{
    QVBoxLayout* layout = new QVBoxLayout;
    creaDatabaseBox();
    creaCambioBox();
    QPushButton* aggiorna_button = new QPushButton("Aggiorna");
    salvaDatabase = new QPushButton("Salva il database");
    caricaDatabase = new QPushButton("Carica database");
    aggiorna_button->setStyleSheet("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightgreen, stop: 1 white);");
    connect(aggiorna_button, SIGNAL(clicked()), this, SLOT(aggiorna()));
    connect(salvaDatabase,SIGNAL(clicked()), this, SLOT(salvaDati()));
    connect(caricaDatabase, SIGNAL(clicked()), this, SLOT(caricaDati()));
    layout->addWidget(gestioneDatabase);
    layout->addWidget(ricercaBox);
    layout->addWidget(cambioAccount);
    layout->addWidget(aggiorna_button,0,Qt::AlignCenter);
    layout->addWidget(salvaDatabase,0,Qt::AlignCenter);
    layout->addWidget(caricaDatabase,0,Qt::AlignCenter);
    layout->addStretch();
    if(!controller->dbCaricato())    salvaDatabase->hide(); // se il db non è caricato non permette il salvataggio
    else    caricaDatabase->hide();
    setLayout(layout);
    aggiorna();
}

void AdminWindow::creaDatabaseBox(){
    gestioneDatabase = new QGroupBox;
    databaseLayout = new QGridLayout;
    QLabel * titolo = new QLabel("LinQedIn - Lato Amministratore");
    QLabel* labelGestioneDB = new QLabel("<b> Gestione Database </b>");
    labelGestioneDB->setStyleSheet("font: 12pt;");
    titolo->setAlignment(Qt::AlignCenter);
    titolo->setStyleSheet("font: 30pt;");
    QLabel* salva = new QLabel("Seleziona utente da salvare");
    utenti_attesa = new QComboBox;
    QLabel* elimina = new QLabel("Seleziona utente da eliminare");
    utenti_presenti = new QComboBox;
    QPushButton* salvaButton = new QPushButton("Salva utente selezionato");
    QPushButton* eliminaButton = new QPushButton("Elimina utente selezionato");
    QPushButton* aggiorna = new QPushButton("Aggiorna");
    QPushButton* azzeraMex = new QPushButton("Azzera messaggi");
    aggiorna->setStyleSheet("background: green");
    connect(aggiorna, SIGNAL(clicked()), this, SLOT(aggiorna()));
    connect(salvaButton, SIGNAL(clicked()), this, SLOT(salvaUtente()));
    connect(eliminaButton, SIGNAL(clicked()), this, SLOT(eliminaUtente()));
    connect(azzeraMex, SIGNAL(clicked()), this, SLOT(azzeraMessaggi()));
    databaseLayout->addWidget(labelGestioneDB,0,0,1,2,Qt::AlignCenter);
    databaseLayout->addWidget(salva,1,0);
    databaseLayout->addWidget(utenti_attesa,2,0);
    databaseLayout->addWidget(salvaButton,3,0);
    databaseLayout->addWidget(elimina,1,1);
    databaseLayout->addWidget(utenti_presenti,2,1);
    databaseLayout->addWidget(eliminaButton,3,1);
    databaseLayout->addWidget(azzeraMex,4,1);
    gestioneDatabase->setLayout(databaseLayout);
    gestioneDatabase->setObjectName("GestioneDatabase");
    gestioneDatabase->setStyleSheet(QString::fromUtf8("QWidget#GestioneDatabase\n{\nborder: 3px groove grey;\n}\n"));
}

void AdminWindow::creaCambioBox(){
    cambioAccount = new QGroupBox("Gestione cambio account");
    utenti_cambio = new QComboBox;
    QHBoxLayout* cambioLayout = new QHBoxLayout;
    QPushButton* cambia = new QPushButton("Cambia");
    QPushButton* ignora = new QPushButton("Ignora richiesta");
    connect(cambia, SIGNAL(clicked()), this, SLOT(cambiaTipoAccount()));
    connect(ignora, SIGNAL(clicked()), this, SLOT(annullaCambio()));
    cambioLayout->addWidget(new QLabel("Utenti da controllare: "));
    cambioLayout->addWidget(utenti_cambio);
    cambioLayout->addWidget(cambia);
    cambioLayout->addWidget(ignora);
    cambioAccount->setLayout(cambioLayout);
}

void AdminWindow::aggiorna(){
    utenti_attesa->clear();
    utenti_cambio->clear();
    vector<SmartUtente> v = controller->getListaAttesa();
  for(unsigned int i = 0; i<v.size(); ++i)
     utenti_attesa->addItem(v[i]->getUsername());
    utenti_presenti->clear();
  for(unsigned int i = 0; i<controller->getListaUsername().size(); ++i)
      utenti_presenti->addItem(controller->getListaUsername()[i]);
  for(unsigned int i = 0; i<controller->getListaCambio().size(); ++i)
  {
      QString tipo;
      switch(controller->getListaTipi()[i]){
        case 1: tipo = "basic"; break;
        case 2: tipo = "business"; break;
        case 3: tipo = "executive"; break;
      }
      utenti_cambio->addItem(controller->getListaCambio()[i] + " cambio -> " + tipo);
  }
}

void AdminWindow::salvaUtente(){
    if(!utenti_attesa->currentText().isEmpty()){
        controller->salvaUtente(utenti_attesa->currentIndex());
        controller->rimuoviCodaAdmin(utenti_attesa->currentIndex());
        // rimuove lo user name dalla combo box una volta che ha salvato l'utente
        utenti_attesa->removeItem(utenti_attesa->currentIndex());
    }
    else{
        QMessageBox* errore = new QMessageBox;
        errore->setText("Nessun utente da salvare.");
        errore->show();
    }
    aggiorna();
}

void AdminWindow::eliminaUtente(){
    if(!utenti_presenti->currentText().isEmpty()){
        controller->eliminaUtente(utenti_presenti->currentText(),utenti_presenti->currentIndex());
        // rimuove lo user name dalla combo box una volta che ha eliminato l'utente
        utenti_presenti->removeItem(utenti_presenti->currentIndex());
        aggiorna();
        return;
    }
    else{
        QMessageBox* errore = new QMessageBox;
        errore->setText("Nessun utente da eliminare.");
        errore->show();
    }
}

void AdminWindow::azzeraMessaggi() const{
    controller->azzeraMex(utenti_presenti->currentText());
}

void AdminWindow::cambiaTipoAccount(){
    if(!utenti_cambio->currentText().isEmpty())
    {
        int i = utenti_cambio->currentIndex(); cout<<i<<endl; cout<<controller->getListaTipi()[i]<<endl;
        controller->cambiaTipoAccount(controller->getListaCambio()[i], controller->getListaTipi()[i]);
        controller->rimuoviUtenteCambiato(i);
        controller->rimuoviTipo(i);
        utenti_cambio->removeItem(i);
        return;
    }
    else{
        QMessageBox* errore = new QMessageBox;
        errore->setText("Nessun utente da cambiare.");
        errore->show();
    }
    aggiorna();
}

void AdminWindow::annullaCambio(){
    if(!utenti_cambio->currentText().isEmpty())
    {
        int i = utenti_cambio->currentIndex();
        controller->rimuoviUtenteCambiato(i);
        controller->rimuoviTipo(i);
        utenti_cambio->removeItem(i);
        aggiorna(); // altrimenti l'ordine non coincide
        return;
    }
    else{
        QMessageBox* errore = new QMessageBox;
        errore->setText("Nessuna richiesta da ignorare.");
        errore->show();
    }
}

void AdminWindow::salvaDati() const{
    if(!controller->salvaDati()){
        QMessageBox* errore = new QMessageBox;
        errore->setText("Errore durante il salvataggio dei dati");
        errore->show();
    }
}

void AdminWindow::caricaDati(){
    controller->caricaDati();
    caricaDatabase->setDisabled(true);
    caricaDatabase->hide();
    salvaDatabase->show();
    aggiorna();
}
