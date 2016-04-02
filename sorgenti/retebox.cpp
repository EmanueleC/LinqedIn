#include "retebox.h"
#include <iostream>
using namespace std;

ReteBox::ReteBox(Controller* c): controller(c), currentRow(0), currentColumn(0), rowCount(0) {
    QVBoxLayout * layout = new QVBoxLayout();
    griglia = new QGridLayout;
    infoText = new QTextEdit;
    creaGrigliaContatti();
    QGroupBox * contatti = new QGroupBox;
    contatti->setLayout(griglia);
    scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(contatti);
    layout->addWidget(scrollArea);
    layout->addWidget(infoText);
    setLayout(layout);
}

void ReteBox::creaGrigliaContatti(){
    for(int i = 0; i<controller->sizeRete(); ++i)
    {
        contatto.push_back(new QLabel(controller->getListaContatti()[i]));
        QPushButton* button = new QPushButton("Mostra Informazioni");
        button->setCheckable(true); // permette di tenere il pulsante abbassato
        infoButton.push_back(button);
        QPushButton* button_elimina = new QPushButton("Elimina Contatto");
        button_elimina->setCheckable(true);
        elimina.push_back(button_elimina);
        griglia->addWidget(contatto[currentRow], currentRow, currentColumn);
        griglia->addWidget(infoButton[currentRow], currentRow, currentColumn + 1);
        griglia->addWidget(elimina[currentRow], currentRow, currentColumn + 2);
        connect(infoButton[currentRow], SIGNAL(pressed()), this, SLOT(mostraInfo()));
        connect(elimina[currentRow], SIGNAL(pressed()), this, SLOT(rimuovi()));
        currentRow++;
        currentColumn = 0;
        rowCount++;
    }
}

void ReteBox::mostraInfo(){
    for(int i=0; i<rowCount; ++i){
        if(infoButton[i]->isDown()){
            infoText->setText(controller->getDatiRicerca(controller->cercaUsername(contatto[i]->text()),false));
            infoButton[i]->setDown(false); // rialza il pulsante
        }
    }
}

void ReteBox::rimuovi(){
    for(int i=0; i<rowCount; ++i){
        if(elimina[i]->isDown()){
            controller->rimuoviContatto(controller->cercaUsername(contatto[i]->text())); aggiorna();
        }
    }
    infoText->clear();
}

void ReteBox::aggiorna(){ // ricrea la griglia aggiornata
    QLayoutItem *child;
    while((child = griglia->takeAt(0)) != 0) {
            QWidget* widget = child->widget();
            if (widget)
            {
              delete child->widget();
              delete child;
            }
    }
    contatto.clear(); infoButton.clear(); elimina.clear(); infoText->clear();
    rowCount = 0; currentRow = 0; currentColumn = 0;
    creaGrigliaContatti();
}

