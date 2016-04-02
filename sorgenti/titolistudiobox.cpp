#include "titolistudiobox.h"
#include <iostream>

TitoliStudioBox::TitoliStudioBox(Controller * c): controller(c), current(0)
{
    QVBoxLayout * TitoliLayout = new QVBoxLayout;
    QGroupBox * TitoliBox = new QGroupBox;
    layout = new QGridLayout;
    descrizioneTitolo = new QTextEdit;
    descrizioneTitolo->setOverwriteMode(true);
    descrizioneTitolo->setMinimumWidth(300);
    QLabel* titoliLabel = new QLabel("<b> Titoli di studio </b>");
    titoliLabel->setStyleSheet("font: 13pt");
    layout->addWidget(titoliLabel,0,1,1,1,Qt::AlignCenter);
    layout->addWidget(new QLabel("Descrizione\ntitolo di studio: "),2,0);
    layout->addWidget(descrizioneTitolo,1,1,6,3);
    layout->addWidget(new QLabel("Data\nconseguimento: "),2,5,1,1,Qt::AlignCenter);
    dataTitolo[0] = new QSpinBox;
    dataTitolo[0]->setRange(1,31);
    dataTitolo[1] = new QSpinBox;
    dataTitolo[1]->setRange(1,12);
    dataTitolo[2] = new QSpinBox;
    dataTitolo[2]->setRange(1900,2016);
    QLabel* data[6];
    data[0] = new QLabel("Giorno: ");
    data[1] = new QLabel("Mese: ");
    data[2] = new QLabel("Anno: ");
    for(int i = 0; i<3; ++i){
        layout->addWidget(data[i],3,i+4);
        layout->addWidget(dataTitolo[i],4,i+4);
    }
    titolo = new QLineEdit;
    istituzione = new QLineEdit;
    areaStudio = new QLineEdit;
    layout->addWidget(new QLabel("Titolo: "),7,0);
    layout->addWidget(titolo,7,1,1,3);
    layout->addWidget(new QLabel("Istituzione: "),8,0);
    layout->addWidget(istituzione,8,1,1,3);
    layout->addWidget(new QLabel("Area di studio: "),9,0);
    layout->addWidget(areaStudio,9,1,1,3);
    prec = new QPushButton("titolo\nprecedente");
    succ = new QPushButton("salva\ntitolo");
    cancella = new QPushButton("cancella\n titolo");
    layout->addWidget(prec,9,5);
    layout->addWidget(succ,9,6);
    layout->addWidget(cancella,9,4);
    connect(succ, SIGNAL(clicked()), this, SLOT(successivo()) );
    connect(prec, SIGNAL(clicked()), this, SLOT(precedente()) );
    connect(cancella,SIGNAL(clicked()),this,SLOT(cancellaCurrent()));
    prec->hide();
    TitoliBox->setLayout(layout);
    TitoliBox->setObjectName("titoliBox");
    TitoliBox->setStyleSheet(QString::fromUtf8("QWidget#titoliBox\n{\nborder: 3px groove grey;\n}\n"));
    TitoliLayout->addWidget(TitoliBox);
    setLayout(TitoliLayout);
}

void TitoliStudioBox::successivo(){
    if(descrizioneTitolo->toPlainText().size()!=0)
    {
        if(descrizioniTitoli.size()>current)
        { // i dati potrebbero essere stati modificati
            descrizioniTitoli[current] = descrizioneTitolo->toPlainText();
            Titoli[current] = titolo->text();
            istituzioni[current] = istituzione->text();
            areeStudio[current] = areaStudio->text();
            for(int i = 0; i<3; ++i) dateTitoli[current*3+i] = dataTitolo[i]->value();
        }
        else
        { // vanno salvati
            descrizioniTitoli.push_back(descrizioneTitolo->toPlainText());
            Titoli.push_back(titolo->text());
            istituzioni.push_back(istituzione->text());
            areeStudio.push_back(areaStudio->text());
            for(int i = 0; i<3; ++i) dateTitoli.push_back(dataTitolo[i]->value());
        }
        current++; prec->show();
        if(descrizioniTitoli.size()>current)
        { // vanno riempiti i campi con i dati corretti
            descrizioneTitolo->setText(descrizioniTitoli[current]);
            titolo->setText(Titoli[current]);
            istituzione->setText(istituzioni[current]);
            areaStudio->setText(areeStudio[current]);
            for(int i =0; i<3; ++i) dataTitolo[i]->setValue(dateTitoli[current*3+i]);
        }
        else
        { // i campi devono essere vuoti
            descrizioneTitolo->clear();
            istituzione->clear();
            titolo->clear();
            areaStudio->clear();
            dataTitolo[0]->setValue(1);
            dataTitolo[1]->setValue(1);
            dataTitolo[2]->setValue(1900);
        }
    }
    else{
        QMessageBox* errore = new QMessageBox;
        errore->setText("Manca la descrizione");
        errore->show();
    }
}

void TitoliStudioBox::precedente(){
    if(descrizioniTitoli.size()<=current && descrizioneTitolo->toPlainText().size()!=0) // non sono stati salvati i dati del titolo corrente
    { // vanno salvati i nuovi dati inseriti
        descrizioniTitoli.push_back(descrizioneTitolo->toPlainText());
        Titoli.push_back(titolo->text());
        istituzioni.push_back(istituzione->text());
        areeStudio.push_back(areaStudio->text());
        for(int i = 0; i<3; ++i) dateTitoli.push_back(dataTitolo[i]->value());
    }
    current--; // current è maggiore di zero
    descrizioneTitolo->setText(descrizioniTitoli[current]);
    titolo->setText(Titoli[current]);
    istituzione->setText(istituzioni[current]);
    areaStudio->setText(areeStudio[current]);
    for(int i =0; i<3; ++i) dataTitolo[i]->setValue(dateTitoli[current*3+i]);
    if(current==0) prec->hide();
}

vector<QString> TitoliStudioBox::getDescrizioniTitoli() const{
    return descrizioniTitoli;
}

vector<int> TitoliStudioBox::getDate() const{
    return dateTitoli;
}

vector<QString> TitoliStudioBox::getTitoli() const{
    return Titoli;
}

vector<QString> TitoliStudioBox::getIstituzioni() const{
    return istituzioni;
}

vector<QString> TitoliStudioBox::getAreeStudio() const{
    return areeStudio;
}

void TitoliStudioBox::setTitoliBox(vector<QString> V_titoli, vector<QString> V_istituzioni, vector<QString> V_descrizioniTitoli, vector<QString> V_areeStudio, vector<int> V_date, bool m){
    if(m){
        for(unsigned int i = 0; i<V_titoli.size(); i++)
        {
            Titoli.push_back(V_titoli[i]);
            istituzioni.push_back(V_istituzioni[i]);
            descrizioniTitoli.push_back(V_descrizioniTitoli[i]);
            areeStudio.push_back(V_areeStudio[i]);
            for(int j =0; j<3; ++j) dateTitoli.push_back(V_date[3*i+j]);
        }
    }
    if(current<Titoli.size()){
            titolo->setText(Titoli[current]);
            istituzione->setText(istituzioni[current]);
            descrizioneTitolo->setText(descrizioniTitoli[current]);
            areaStudio->setText(areeStudio[current]);
            for(int i =0; i<3; ++i) dataTitolo[i]->setValue(dateTitoli[i+current*3]);
    }
}

void TitoliStudioBox::cancellaCurrent(){
    if(Titoli.size()>0 && descrizioneTitolo->toPlainText().size()!=0){
        Titoli.erase(Titoli.begin()+current);
        istituzioni.erase(istituzioni.begin()+current);
        descrizioniTitoli.erase(descrizioniTitoli.begin()+current);
        areeStudio.erase(areeStudio.begin()+current);
        for(int i =0; i<3; ++i) dateTitoli.erase(dateTitoli.begin());
        titolo->clear();
        istituzione->clear();
        descrizioneTitolo->clear();
        areaStudio->clear();
        for(int i =0; i<3; ++i) dataTitolo[i]->clear();
        if(current>0) current = current - 1;
        if(current==0) prec->hide();
        setTitoliBox(Titoli,istituzioni,descrizioniTitoli,areeStudio,dateTitoli,false);
    }
    else{
        QMessageBox* errore = new QMessageBox;
        errore->setText("Nessun titolo da eliminare");
        errore->show();
    }
}
