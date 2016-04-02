#include "esplavorobox.h"

EspLavoroBox::EspLavoroBox(Controller* c): controller(c), current(0)
{
    QVBoxLayout* esperienzeLayout = new QVBoxLayout;
    QGroupBox * esperienzeBox = new QGroupBox;
    layout = new QGridLayout;
    esperienze = new QTextEdit;
    esperienze->setOverwriteMode(true);
    esperienze->setMinimumWidth(300);
    QLabel* esperienzeLabel = new QLabel("<b> Esperienze Lavorative </b>");
    esperienzeLabel->setStyleSheet("font: 13pt");
    layout->addWidget(esperienzeLabel,0,1,1,1,Qt::AlignCenter);
    layout->addWidget(new QLabel("Descrizione\nesperienza\nlavorativa: "),3,0);
    layout->addWidget(esperienze,1,1,6,3);
    layout->addWidget(new QLabel("Data di inizio: "),1,5);
    dateEsp[0] = new QSpinBox;
    dateEsp[0]->setRange(1,31);
    dateEsp[1] = new QSpinBox;
    dateEsp[1]->setRange(1,12);
    dateEsp[2] = new QSpinBox;
    dateEsp[2]->setRange(1900,2016);
    dateEsp[3] = new QSpinBox;
    dateEsp[3]->setRange(1,31);
    dateEsp[4] = new QSpinBox;
    dateEsp[4]->setRange(1,12);
    dateEsp[5] = new QSpinBox;
    dateEsp[5]->setRange(1900,2016);
    QLabel* data[6];
    data[0] = new QLabel("Giorno: ");
    data[1] = new QLabel("Mese: ");
    data[2] = new QLabel("Anno: ");
    data[3] = new QLabel("Giorno: ");
    data[4] = new QLabel("Mese: ");
    data[5] = new QLabel("Anno: ");
    for(int i = 0; i<3; ++i){
        layout->addWidget(data[i],2,i+4);
        layout->addWidget(dateEsp[i],3,i+4);
    }
    layout->addWidget(new QLabel("Data di fine: "),4,5);
    for(int i = 3; i<6; ++i){
        layout->addWidget(data[i],5,i+1);
        layout->addWidget(dateEsp[i],6,i+1);
    }
    luogo = new QLineEdit;
    azienda = new QLineEdit;
    layout->addWidget(new QLabel("Luogo: "),7,0);
    layout->addWidget(luogo,7,1,1,3);
    layout->addWidget(new QLabel("Nome Azienda\nSettore: "),8,0);
    layout->addWidget(azienda,8,1,1,3);
    prec = new QPushButton("esperienza\nprecedente");
    succ = new QPushButton("salva\nesperienza");
    cancella = new QPushButton("cancella\nesperienza");
    layout->addWidget(prec,9,5);
    layout->addWidget(succ,9,6);
    layout->addWidget(cancella,9,4);
    connect(succ, SIGNAL(clicked()), this, SLOT(successivo()) );
    connect(prec, SIGNAL(clicked()), this, SLOT(precedente()) );
    connect(cancella,SIGNAL(clicked()),this,SLOT(cancellaCurrent()));
    prec->hide();
    esperienzeBox->setLayout(layout);
    esperienzeBox->setObjectName("esperienzeBox");
    esperienzeBox->setStyleSheet(QString::fromUtf8("QWidget#esperienzeBox\n{\nborder: 3px groove grey;\n}\n"));
    esperienzeLayout->addWidget(esperienzeBox);
    setLayout(esperienzeLayout);
}

void EspLavoroBox::successivo(){
    if(esperienze->toPlainText().size()!=0)
    {
        if(esp.size()>current)
        {
            esp[current] = esperienze->toPlainText();
            luoghi[current] = luogo->text();
            aziende[current] = azienda->text();
            for(int i = 0; i<6; ++i) date[current*6+i] = dateEsp[i]->value();
        }
        else
        {
            esp.push_back(esperienze->toPlainText());
            luoghi.push_back(luogo->text());
            aziende.push_back(azienda->text());
            for(int i = 0; i<6; ++i) date.push_back(dateEsp[i]->value());
        }
        current++; prec->show();
        if(esp.size()>current)
        {
            esperienze->setText(esp[current]);
            luogo->setText(luoghi[current]);
            azienda->setText(aziende[current]);
            for(int i =0; i<6; ++i) dateEsp[i]->setValue(date[current*6+i]);
        }
        else
        {
            esperienze->clear();
            luogo->clear();
            azienda->clear();
            dateEsp[0]->setValue(1);
            dateEsp[1]->setValue(1);
            dateEsp[2]->setValue(1900);
            dateEsp[3]->setValue(1);
            dateEsp[4]->setValue(1);
            dateEsp[5]->setValue(1900);
        }
    }
    else{
        QMessageBox* errore = new QMessageBox;
        errore->setText("Manca la descrizione");
        errore->show();
    }
}

void EspLavoroBox::precedente(){
    if(esp.size()<=current && esperienze->toPlainText().size()!=0) // non sono stati salvati i dati dell'esp corrente
    {
        esp.push_back(esperienze->toPlainText());
        aziende.push_back(azienda->text());
        luoghi.push_back(luogo->text());
        for(int i = 0; i<6; ++i) date.push_back(dateEsp[i]->value());
    }
    if(esp.size()>current && esperienze->toPlainText().size()!=0)
    {
        esp[current] = esperienze->toPlainText();
        luoghi[current] = luogo->text();
        aziende[current] = azienda->text();
        for(int i = 0; i<6; ++i) date[current*6+i] = dateEsp[i]->value();
    }
    current--; // current è maggiore di zero
    esperienze->setText(esp[current]);
    luogo->setText(luoghi[current]);
    azienda->setText(aziende[current]);
    for(int i=0; i<6; ++i) dateEsp[i]->setValue(date[current*6+i]);
    if(current==0) prec->hide();
}

vector<QString> EspLavoroBox::getEsp() const{
    return esp;
}

vector<int> EspLavoroBox::getDate() const{
    return date;
}

vector<QString> EspLavoroBox::getLuoghi() const{
    return luoghi;
}

vector<QString> EspLavoroBox::getAziende() const{
    return aziende;
}

void EspLavoroBox::setEspBox(vector<QString> V_esperienze, vector<QString> V_aziende, vector<QString> V_luoghi, vector<int> V_date,bool m){
    if(m){
        for(unsigned int i = 0; i<V_esperienze.size(); i++)
        {
            esp.push_back(V_esperienze[i]);
            luoghi.push_back(V_luoghi[i]);
            aziende.push_back(V_aziende[i]);
            for(int j =0; j<6; ++j) date.push_back(V_date[6*i+j]);
        }
    }
    if(current<esp.size()){
        esperienze->setText(esp[current]);
        luogo->setText(luoghi[current]);
        azienda->setText(aziende[current]);
        for(int i =0; i<6; ++i) dateEsp[i]->setValue(date[i+current*6]);
    }
}

void EspLavoroBox::cancellaCurrent(){
    if(esp.size()>0 && esperienze->toPlainText().size()!=0){
        esp.erase(esp.begin()+current);
        luoghi.erase(luoghi.begin()+current);
        aziende.erase(aziende.begin()+current);
        for(int i =0; i<6; ++i) date.erase(date.begin());
        esperienze->clear();
        luogo->clear();
        azienda->clear();
        for(int i =0; i<6; ++i) dateEsp[i]->clear();
        if(current>0) current = current - 1;
        if(current==0) prec->hide();
        setEspBox(esp,luoghi,aziende,date,false);
    }
    else{
        QMessageBox* errore = new QMessageBox;
        errore->setText("Nessuna esperienza da cancellare");
        errore->show();
    }
}
