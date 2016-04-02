#include "smartutente.h"
#include "utente.h"

SmartUtente::SmartUtente(Utente * u): up(u) {
    if(up){ up->riferimenti++; }
}

SmartUtente::SmartUtente(const SmartUtente & us): up(us.up) {
    if(up){ up->riferimenti++; }
}

SmartUtente::~SmartUtente(){
    if(up){
        up->riferimenti--; // distruzione logica
        if(up->riferimenti == 0){ delete up; }  // distruzione effettiva
    }
}

SmartUtente& SmartUtente::operator =(const SmartUtente & us){
    if(this!=&us){
        Utente* aux = up;
        up = us.up;
        if(up){ up->riferimenti++; }
        if(aux){
            aux->riferimenti--;
            if(aux->riferimenti == 0){ delete aux; }
        }
    }
    return *this;
}

Utente& SmartUtente::operator *() const{
    return *up;
}

Utente* SmartUtente::operator ->() const{
    return up;
}

bool SmartUtente::operator ==(const SmartUtente & us) const{
    return up == us.up;
}

bool SmartUtente::operator !=(const SmartUtente & us) const{
    return up != us.up;
}


