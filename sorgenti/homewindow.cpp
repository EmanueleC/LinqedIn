#include "homewindow.h"


HomeWindow::HomeWindow(Controller * c): controller(c), iscrizioneUtente(0)
{
    layoutHome = new QVBoxLayout;
    rett = new Rettangolo(true);
    QGroupBox* rettBox = new QGroupBox;
    QHBoxLayout* rettLayout = new QHBoxLayout;
    rettLayout->addWidget(rett);
    rettBox->setFixedSize(750,90);
    rettBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 blue, stop: 1 #FFFFFF);");
    rettBox->setLayout(rettLayout);
    layoutHome->addWidget(rettBox,0,Qt::AlignTop|Qt::AlignCenter);
    caricaHome();
    layoutHome->addWidget(homeBox,0,Qt::AlignHCenter);
    infoLinqedIn = new QLabel("LinqedIn è una rete sociale che permette la condivisione di informazioni tra gli utenti. \n Sono disponibili 3 tipi di account: Basic (gratuito), Business ed Executive ");
    infoLinqedIn->setAlignment(Qt::AlignCenter);
    infoLinqedIn->setStyleSheet("font: 11pt; color: blue;");
    layoutHome->addWidget(infoLinqedIn,0,Qt::AlignCenter);
    setLayout(layoutHome);
}

void HomeWindow::caricaHome(){
    homeBox = new QGroupBox;
    layout = new QVBoxLayout;
    iscrizione = new QPushButton("Iscriviti a Linqedin");
    QFormLayout * logInLayout = new QFormLayout;
    accesso_box = new QGroupBox("Log In");
    userName = new QLineEdit;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    password->setInputMethodHints(Qt::ImhHiddenText);
    accesso = new QPushButton("Accedi");
    logInLayout->addRow(new QLabel("Nome Utente: "), userName);
    logInLayout->addRow(new QLabel("Password: "), password);
    accesso_box->setLayout(logInLayout);
    accesso_box->setStyleSheet("background-color: white");
    entra = new QPushButton("Entra");
    iscrizione->setStyleSheet("background-color: yellow");
    accesso->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #3366CC, stop: 1 #FFFFFF);");
    entra->setStyleSheet("background-color: green");
    entra->hide();
    layout->addWidget(iscrizione,0,Qt::AlignCenter);
    layout->addWidget(entra,0,Qt::AlignCenter);
    layout->addWidget(accesso_box,0,Qt::AlignCenter);
    layout->addWidget(accesso,0,Qt::AlignCenter);
    connect(entra,SIGNAL(clicked()),this,SLOT(caricaPaginaUtente()));
    connect(iscrizione,SIGNAL(clicked()),this,SLOT(createFormClass()));
    connect(accesso, SIGNAL(clicked()),this,SLOT(accedi()));
    homeBox->setLayout(layout);
    homeBox->setFixedSize(QSize(250,500));
    homeBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6787E7, stop: 1 #FFFFFF);");
}

void HomeWindow::createFormClass(){
    iscrizioneUtente = new FormClass(controller,true,this); // true: modalità iscrizione
    scrollarea = new QScrollArea;
    scrollarea->setWidget(iscrizioneUtente);
    homeBox->hide();
    infoLinqedIn->hide();
    layoutHome->addWidget(scrollarea);
}

void HomeWindow::caricaPaginaUtente(){
        homeBox->hide();
        userWindow = new UserWindow(controller);
        userWindow->setMinimumWidth(750);
        scrollarea2 = new QScrollArea;
        scrollarea2->setWidget(userWindow);
        logOut = new QPushButton("log out");
        connect(logOut, SIGNAL(clicked()), this, SLOT(esci()));
        layoutHome->addWidget(scrollarea2);
        layoutHome->addWidget(logOut,0,Qt::AlignCenter);
        infoLinqedIn->hide();
}

void HomeWindow::esci() const{
    controller->scollega(); // scollega l'utente
    logOut->hide();
    delete userWindow;
    delete scrollarea2;
    homeBox->setVisible(true);
    entra->hide();
    infoLinqedIn->setVisible(true);
}

void HomeWindow::accedi(){
    if(controller->checkIn(userName->text(),password->text())){
        // lascia lo userName scritto
        password->clear();
        controller->collega(controller->cercaUsername(userName->text()));
        caricaPaginaUtente();
    }
    else{
        QMessageBox errorMessage;
        errorMessage.setText("Username o password errati.");
        errorMessage.exec();
    }
}

void HomeWindow::ripristina(){
    if(iscrizioneUtente){
        delete iscrizioneUtente;
        delete scrollarea;
    } // elimina il form per l'inserimento dati
    homeBox->show();
    if(controller->utenteCaricato()) entra->show();
    infoLinqedIn->show();
}

