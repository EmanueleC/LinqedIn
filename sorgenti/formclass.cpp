#include "formclass.h"
#include "homewindow.h"
#include <QDesktopWidget>

FormClass::FormClass(Controller* c, bool m, HomeWindow* h): controller(c), home(h), mode(m)
{
    QGroupBox* dati = new QGroupBox; // per i dati anagrafici
    QGroupBox* genere = new QGroupBox; // box per il genere
    QVBoxLayout* layout = new QVBoxLayout; // layout principale
    QFormLayout* dati_layout =new QFormLayout;
    QHBoxLayout* genere_layout = new QHBoxLayout;
    nome = new QLineEdit;
    cognome = new QLineEdit;
    username = new QLineEdit;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    password->setInputMethodHints(Qt::ImhHiddenText);
    email = new QLineEdit;
    provincia = new QLineEdit;
    telefono = new QLineEdit;
    sito = new QLineEdit;
    uomo = new QRadioButton("Uomo");
    donna = new QRadioButton("Donna");
    QLabel * genere_studente = new QLabel("Sesso * : ");
    genere_layout->addWidget(genere_studente);
    genere_layout->addWidget(uomo);
    genere_layout->addWidget(donna);
    genere->setLayout(genere_layout);
    dati_layout->addRow(new QLabel("Inserire nome *"), nome);
    dati_layout->addRow(new QLabel("Inserire cognome *"), cognome);
    // non è possibile modificare lo username una volta salvato
    if(mode) dati_layout->addRow(new QLabel("Inserire nome utente *"), username);
    dati_layout->addRow(new QLabel("Inserire password *"), password);
    dati_layout->addRow(new QLabel("Inserire e-mail"), email);
    dati_layout->addRow(new QLabel("Inserire provincia"), provincia);
    dati_layout->addRow(new QLabel("Inserire numero di telefono"), telefono);
    dati_layout->addRow(new QLabel("Inserire indirizzo sito web"), sito);
    dati_layout->addRow(genere);
    dati->setLayout(dati_layout);
    QGroupBox* griglia = new QGroupBox("Inserire la data di nascita");
    QGridLayout* layoutG = new QGridLayout;
    QLabel* label[3];
    label[0] = new QLabel("Giorno: ");
    datiNascita[0] = new QSpinBox;
    datiNascita[0]->setRange(1,31);
    label[1] = new QLabel("Mese: ");
    datiNascita[1] = new QSpinBox;
    datiNascita[1]->setRange(1,12);
    label[2] = new QLabel("Anno: ");
    datiNascita[2] = new QSpinBox;
    datiNascita[2]->setRange(1900, 2015);
    for(int i=0; i<3; ++i){
        layoutG->addWidget(label[i], 0, i+1);
        layoutG->addWidget(datiNascita[i], 1, i+1);
    }
    griglia->setLayout(layoutG);
    QGroupBox* formCurriculum = new QGroupBox;
    QGridLayout* curriculum_layout = new QGridLayout;
    lingueParlate = new QTextEdit;
    interessi = new QTextEdit;
    curriculum_layout->addWidget(new QLabel("Lingue conosciute: "),0,0);
    curriculum_layout->addWidget(lingueParlate,0,1);
    curriculum_layout->addWidget(new QLabel("Interessi: "),1,0);
    curriculum_layout->addWidget(interessi,1,1);
    formCurriculum->setLayout(curriculum_layout);
    QPushButton* iscriviti = new QPushButton("Iscriviti");
    iscriviti->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #3366CC, stop: 1 #FFFFFF);");
    QPushButton* salvaModifiche = new QPushButton("Salva Modifiche");
    QLabel* infoForm = new QLabel("<b> I campi contrassegnati con * sono obbligatori </b>");
    infoForm->setStyleSheet("color: red;");
    QLabel* titleForm = new QLabel("<b> Iscrizione a LinQedIn </b>");
    titleForm->setStyleSheet("color: blue;" "font: 12pt;");
    layout->addWidget(titleForm,0,Qt::AlignCenter);
    layout->addWidget(dati);
    layout->addWidget(griglia);
    layout->addWidget(formCurriculum);
    espBox = new EspLavoroBox(controller);
    titoliBox = new TitoliStudioBox(controller);
    QVBoxLayout* layoutEspTitoli = new QVBoxLayout;
    QGroupBox* EspTitoliBox = new QGroupBox;
    layoutEspTitoli->addWidget(titoliBox);
    layoutEspTitoli->addWidget(espBox);
    EspTitoliBox->setLayout(layoutEspTitoli);
    layout->addWidget(EspTitoliBox);
    layout->addWidget(infoForm,0,Qt::AlignCenter);
    if(mode)    layout->addWidget(iscriviti,0,Qt::AlignCenter);
    else layout->addWidget(salvaModifiche,0,Qt::AlignCenter);
    if(mode){ esci = new QPushButton("Torna\nalla Home");
    layout->addWidget(esci,0,Qt::AlignCenter);
    connect(esci,SIGNAL(clicked()),this,SLOT(ripristinaHome())); }
    connect(iscriviti, SIGNAL(clicked()), this, SLOT(salva()));
    connect(salvaModifiche, SIGNAL(clicked()), this, SLOT(salva()));
    setLayout(layout);
    if(mode) setWindowTitle("Iscrizione a LinqedIn");
    else{ // predispone i dati dell'utente corrente, in modo da facilitare la modifica delle informazioni
        setWindowTitle("Modifica profilo");
        nome->setText(controller->getNomeUtente());
        cognome->setText(controller->getProfiloUtente().getCognome());
        provincia->setText(controller->getProfiloUtente().getProvincia());
        email->setText(controller->getProfiloUtente().getEmail());
        telefono->setText(controller->getProfiloUtente().getTelefono());
        sito->setText(controller->getProfiloUtente().getSito());
        if(controller->getProfiloUtente().Uomo())   uomo->setChecked(true);
        else    donna->setChecked(true);
        interessi->setText(controller->getProfiloUtente().getInteressi());
        lingueParlate->setText(controller->getProfiloUtente().getLingue());
        datiNascita[0]->setValue(controller->getProfiloUtente().getGiornoNascita());
        datiNascita[1]->setValue(controller->getProfiloUtente().getMeseNascita());
        datiNascita[2]->setValue(controller->getProfiloUtente().getAnnoNascita());
        espBox->setEspBox(controller->getDescrizioniEsperienze(), controller->getAziende(), controller->getLuoghiLavoro(), controller->getCifreDateEsp(),true);
        titoliBox->setTitoliBox(controller->getTitoliStudio(), controller->getIstituzioni(), controller->getDescrizioniTitoli(), controller->getAreeStudio(), controller->getCifreDateTitoli(),true);
    }
    if(!mode)
    {
        scrollarea = new QScrollArea;
        scrollarea->setWidget(this);
        scrollarea->setFixedWidth(700);
        scrollarea->show();
    }
}


void FormClass::salva(){
    if(nome->text().trimmed().isEmpty() || cognome->text().trimmed().isEmpty() || (username->text().trimmed().isEmpty() && mode) || password->text().trimmed().isEmpty() || (!uomo->isChecked() && !donna->isChecked()))
    {
        QMessageBox errorMessage;
        errorMessage.setText("Ci sono dei campi dati incompleti");
        errorMessage.exec();
    }
    else
    {
        if(controller->checkUsername(username->text()))
        {
            if(mode){
                controller->carica_nuovoUtente(nome->text(),cognome->text(),username->text(),password->text(),email->text(),provincia->text(), telefono->text(), sito->text(),
                                    uomo->isChecked(),datiNascita[0]->value(),datiNascita[1]->value(),datiNascita[2]->value(), lingueParlate->toPlainText(), interessi->toPlainText(), titoliBox->getTitoli(), titoliBox->getIstituzioni(), titoliBox->getDescrizioniTitoli(), titoliBox->getAreeStudio(), titoliBox->getDate(), espBox->getEsp(), espBox->getAziende(), espBox->getLuoghi(), espBox->getDate());
                home->ripristina();
            }
            else{
                controller->modificaUtente(nome->text(), cognome->text(), controller->getUsername(), password->text(), email->text(), provincia->text(), telefono->text(), sito->text(),
                                       uomo->isChecked(),datiNascita[0]->value(),datiNascita[1]->value(),datiNascita[2]->value(), lingueParlate->toPlainText(), interessi->toPlainText(), titoliBox->getTitoli(), titoliBox->getIstituzioni(), titoliBox->getDescrizioniTitoli(), titoliBox->getAreeStudio(), titoliBox->getDate(), espBox->getEsp(), espBox->getAziende(), espBox->getLuoghi(), espBox->getDate());
                close();
                scrollarea->close();
            }
        }
        else
        {
            QMessageBox errorMessage;
            errorMessage.setText("Nome utente non valido, riprovare");
            username->clear();
            errorMessage.exec();
        }
    }
}

void FormClass::ripristinaHome(){
    if(home)    home->ripristina();
}


