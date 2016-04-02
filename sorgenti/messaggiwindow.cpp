#include "messaggiwindow.h"

messaggiwindow::messaggiwindow(Controller * c): controller(c)
{
    box = new QGroupBox;
    hlayout = new QHBoxLayout;
    destinatario = new QLabel("Seleziona destinatario: ");
    contatti = new QComboBox();
    for(unsigned int i = 0; i<controller->getListaContatti().size(); ++i)
        contatti->addItem(controller->getListaContatti()[i]);
    hlayout->addWidget(destinatario);
    hlayout->addWidget(contatti);
    box->setLayout(hlayout);
    layout = new QVBoxLayout;
    layout->addWidget(box);
    testo = new QTextEdit("Digita qui il testo del messaggio");
    testo->setFrameStyle(QFrame::Box);
    testo->setOverwriteMode(true);
    layout->addWidget(testo);
    invia = new QPushButton("Invia");
    connect(invia, SIGNAL(clicked()), this, SLOT(inviaMessaggio()));
    layout->addWidget(invia);
    setLayout(layout);
    setWindowTitle("Messaggi LinQedIn");
}

void messaggiwindow::inviaMessaggio() const{
    int check = controller->inviaMessaggio(contatti->currentText(),testo->toPlainText());
    switch(check){
        case -1: {
            QMessageBox* message = new QMessageBox;
            message->setText("Attenzione, hai raggiunto la quota massima di messaggi");
            message->show();
            }
            break;
        case 0: {
            QMessageBox* message = new QMessageBox;
            message->setText("Attenzione, l'utente selezionato non è presente nel database LinqedIn");
            message->show();
            }
            break;
        case 1: {
            QMessageBox* message = new QMessageBox;
            message->setText("Il suo messaggio è stato inviato");
            message->show();
            testo->clear();
            }
            break;
    }
}

void messaggiwindow::aggiorna(){
    contatti->clear();
    for(unsigned int i = 0; i<controller->getListaContatti().size(); ++i)
        contatti->addItem(controller->getListaContatti()[i]);
}
