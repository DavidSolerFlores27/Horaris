#include "FranjaHoraria.h"
using namespace std;

FranjaHoraria::FranjaHoraria(const Hora & inici, const Hora & final, int duracio_minima){
    this->_inicial = min(inici, final);
    this->_final = max(inici, final);

    this->inicial_limit = _inicial;
    this->final_limit = _final;

    if (duracio_minima == 0){
        this->duracio_minima = _final.minuts() - _inicial.minuts();
    
    }else if (duracio_minima > ((final - inici).minuts())){
        cerr << "Duració incorrecta: "<<duracio_minima<<endl;
        throw ("Duració incorrecta");
    
    }else{
        this->duracio_minima = duracio_minima;
    }
}

bool FranjaHoraria::hiHaSolapament(const FranjaHoraria & a, const FranjaHoraria & b){
    return not (a._final <= b._inicial or b._final <= a._inicial);
}

int FranjaHoraria::duracio()const{
    return _final.minuts() - _inicial.minuts();
}



void FranjaHoraria::sumar(int minIn, int minFi){
    if (not esPotSumar(minIn, minFi)){
        cerr << "No es pot sumar ";
        throw ("No es pot sumar");
    }

    _inicial.sumar(minIn);
    _final.sumar(minFi);
}

Hora FranjaHoraria::inicial()const{
    return _inicial;
}

Hora FranjaHoraria::final()const{
    return _final;
}



bool FranjaHoraria::esPotSumar(int minIn, int minFi)const{
    if (not inicial().esPotSumar(minIn) or not final().esPotSumar(minFi)){
        return false;
    }

    Hora copia_in = inicial();
    Hora copia_fi = final();

    copia_in.sumar(minIn);
    copia_fi.sumar(minFi);
    return ((copia_fi.minuts() - copia_in.minuts()) >= duracio_minima) and copia_fi <= final_limit and copia_in >= inicial_limit;

}


int FranjaHoraria::tempsSolapat(const FranjaHoraria & f)const{

    Hora inici_sol = max(inicial(), f.inicial());
    Hora final_sol = min(final(), f.final());

    return max(0, final_sol.resta(inici_sol));
}



bool FranjaHoraria::operator<(const FranjaHoraria & f)const{
    if (this->_inicial != f._inicial){
        return _inicial < f._inicial;
    }

    return this->_final < f._final;
}

bool FranjaHoraria::operator==(const FranjaHoraria & f)const{
    return this->_inicial == f._inicial and this->_final == f._final;
}

bool FranjaHoraria::operator!=(const FranjaHoraria & f)const{
    return not (*this == f);
}


ostream& operator<<(ostream & os, const FranjaHoraria &h){
    os << h.inicial() << " - "<<h.final()<< " ("<<h.duracio()<<" min)";
    return os;
}