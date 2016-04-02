#include "homeadmin.h"

HomeAdmin::HomeAdmin(Controller* c): controller(c)
{
    homeLayout = new QVBoxLayout;
    QGroupBox* rettBox = new QGroupBox;
    QHBoxLayout* rettLayout = new QHBoxLayout;
    rettangolo = new Rettangolo(false);
    rettLayout->addWidget(rettangolo);
    rettBox->setFixedSize(750,90);
    rettBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 darkred, stop: 1 #FFFFFF);");
    rettBox->setLayout(rettLayout);
    homeLayout->addWidget(rettBox,0,Qt::AlignTop|Qt::AlignCenter);
    CaricaHomeAdmin();
    homeLayout->addWidget(homeBox,0,Qt::AlignCenter);
    connect(accesso,SIGNAL(clicked()),this,SLOT(accedi()));
    infoLinqedIn = new QLabel("Parte riservata all'amministratore.");
    infoLinqedIn->setAlignment(Qt::AlignCenter);
    infoLinqedIn->setStyleSheet("font: 11pt; color: blue;");
    homeLayout->addWidget(infoLinqedIn,0,Qt::AlignCenter);
    setLayout(homeLayout);
}

void HomeAdmin::CaricaHomeAdmin(){
    homeBox = new QGroupBox;
    QVBoxLayout* hBoxLayout = new QVBoxLayout;
    QFormLayout* logInLayout = new QFormLayout;
    QGroupBox* accesso_box = new QGroupBox("Log In Admin");
    admin = new QLineEdit;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    password->setInputMethodHints(Qt::ImhHiddenText);
    accesso = new QPushButton("Accedi");
    logInLayout->addRow(new QLabel("Amministratore: "), admin);
    logInLayout->addRow(new QLabel("Password: "), password);
    accesso_box->setLayout(logInLayout);
    accesso_box->setStyleSheet("background-color: white");
    accesso->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #A52A2A, stop: 1 #FFFFFF);");
    hBoxLayout->addWidget(accesso_box,0,Qt::AlignCenter);
    hBoxLayout->addWidget(accesso,0,Qt::AlignCenter);
    homeBox->setLayout(hBoxLayout);
    homeBox->setFixedSize(QSize(250,500));
    homeBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FF6347, stop: 1 #FFFFFF);");
}

void HomeAdmin::accedi(){
    if(controller->checkInAdmin(admin->text(),password->text()))
    {
        adminWindow = new AdminWindow(controller);
        homeBox->hide();
        infoLinqedIn->hide();
        homeLayout->addWidget(adminWindow);
        logOut = new QPushButton("Esci");
        homeLayout->addWidget(logOut,0,Qt::AlignCenter);
        connect(logOut,SIGNAL(clicked()),this,SLOT(esci()));
    }
    else{
        QMessageBox errorMessage;
        errorMessage.setText("Admin o password errati.");
        errorMessage.exec();
    }
}

void HomeAdmin::esci(){
    QMessageBox exitMessage;
    exitMessage.setText("Le modifiche apportate al database non salvate verranno perse.");
    exitMessage.setInformativeText("Salvare le modifiche?");
    exitMessage.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    exitMessage.setDefaultButton(QMessageBox::Save);
    int ret = exitMessage.exec();
    switch (ret) {
      case QMessageBox::Save:
          // Save was clicked
          if(!controller->dbCaricato()){ // deve verificare che prima il database sia stato caricato
            QMessageBox* errore = new QMessageBox;
            errore->setText("Database non caricato. Impossibile salvare i dati.");
            errore->show();
           }
          else{
            if(!controller->salvaDati()){
                QMessageBox* errore = new QMessageBox;
                errore->setText("Errore durante il salvataggio dei dati.");
                errore->show();
            }
          }
          break;
      case QMessageBox::Cancel:
          // Cancel was clicked
          break;
      default:
          // should never be reached
          break;
    }
    delete adminWindow;
    logOut->hide();
    homeBox->show();
    infoLinqedIn->show();
    password->clear();
}
