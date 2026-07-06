#include "Hora.h"
#include <iomanip>
using namespace std;

Hora::Hora(int h, int m){

    if (not esValida(h, m)){
        cerr << "Hora no vàlida: "<<h <<":"<< m;
        throw ("Hora no vàlida");
    }
    this->hora = h;
    this->min = m;
}

bool Hora::esValida(int h, int m){
    return h < 24 and h >= 0 and m <= 59 and m >= 0;
}


int Hora::minuts()const{
    return hora*60 + min;
}


bool Hora::operator<(const Hora & h)const{
    return this->hora < h.hora or (hora == h.hora and min < h.min);
}

bool Hora::operator==(const Hora & h)const{
    return this->hora == h.hora and min == h.min;
}

bool Hora::operator<=(const Hora & h)const{
    return *this < h or *this == h;
}

bool Hora::operator!=(const Hora & h)const{
    return not (*this == h);
}


Hora Hora::operator-(const Hora & h)const{
    if (*this < h){
        cerr << "Ordre incorrecta de resta d'hores";
        throw ("Ordre incorrecta de resta d'hores");
    }

    int min = minuts() - h.minuts();

    return Hora(min/60, min%60);

}

bool Hora::operator>(const Hora & h)const{
    return not(*this <= h);
}

bool Hora::operator>=(const Hora & h)const{
    return *this > h or *this == h;
}

bool Hora::esPotSumar(int m)const{
    int _minuts = minuts() + m;
    return esValida(_minuts/60, _minuts%60);
}


void Hora::sumar(int m){
    if (not esPotSumar(m)){
        cerr<< "No es pot sumar "<<m<<" minuts a: ";
        cerr<<*this;
        throw ("No es pot sumar");
    }
    
    int _minuts = minuts()+m;
    this->hora = _minuts/60;
    this->min = _minuts%60;

}


int Hora::resta(const Hora & h)const{
    return minuts() - h.minuts();
}

ostream& operator<<(ostream & os, const Hora & h){
    os << setw(2) << setfill('0') << h.hora <<":"<< setw(2) << setfill('0') << h.min;
    return os;
}