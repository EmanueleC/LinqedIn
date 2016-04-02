#include "rettangolo.h"

Rettangolo::Rettangolo(bool m, QWidget * parent): mode(m), QWidget(parent) {}


void Rettangolo::paintEvent(QPaintEvent * e){
       QRect rect = e->rect();
       rect.setHeight(70);
       QPainter painter(this);
       painter.setRenderHint(QPainter::Antialiasing);
       painter.setPen(Qt::black);
       QFont serifFont = QFont("Times", 20, QFont::Bold);
       painter.setFont(serifFont);
       if(mode){
           painter.setBrush(QColor(0, 33, 66, 110));
           painter.drawText(rect, Qt::AlignCenter, "LinQedin");
       }
       else{
           painter.setBrush(QColor(99, 00, 00, 110));
           painter.drawText(rect, Qt::AlignCenter, "LinQedin - Modalità Admin");
       }
       painter.drawRect(rect);
}
