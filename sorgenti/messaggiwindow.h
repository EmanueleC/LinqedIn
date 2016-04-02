#ifndef MESSAGGIWINDOW_H
#define MESSAGGIWINDOW_H
#include <QtWidgets>
#include "controller.h"

class messaggiwindow: public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
    QVBoxLayout* layout;
    QHBoxLayout* hlayout;
    QGroupBox* box;
    QLabel* destinatario;
    QComboBox* contatti;
    QTextEdit* testo;
    QPushButton* invia;
public:
    messaggiwindow(Controller* );
public slots:
    void inviaMessaggio() const;
    void aggiorna();
};

#endif // MESSAGGIWINDOW_H
