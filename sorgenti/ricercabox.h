#ifndef RICERCABOX_H
#define RICERCABOX_H
#include "controller.h"
#include <QWidget>
#include <QtWidgets>


class UserWindow;

class ricercabox: public QWidget
{
    Q_OBJECT
private:
    Controller * controller;
    QGridLayout * ricercaLayout;
    QLineEdit * nomeCercato, * cognomeCercato, * usernameCercato, * provinciaCercata, * aziendaCercata, *titoloStudio, *areaStudio;
    QTextEdit * infoText;
    UserWindow * user;
    bool completa; // true se usata dall'admin, false se usata dal client
    QPushButton* nascondi;
public:
    ricercabox(Controller* , UserWindow* = 0, bool = false);
    QString getText() const;
    QString getUsername() const;
public slots:
    void ricercaNome() const;
    void ricercaCognome() const;
    void ricercaProvincia() const;
    void ricercaUsername() const;
    void ricercaAzienda() const;
    void ricercaTitolo() const;
    void ricercaArea() const;
    void ricercaCombinata() const;
    void nascondiTesto() const;
};

#endif // RICERCABOX_H
