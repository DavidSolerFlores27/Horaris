#include "Candidats.h"
using namespace std;

Candidats::Candidats(int maxim, int actual){
    this->_actual = actual;
    this->_maxim = maxim;
}

bool Candidats::esFi()const{
    return _actual >= _maxim;
}

int Candidats::actual()const{
    if (esFi()){
        cerr << "No hi han més candidats"<<endl;
        throw ("No hi han més candidats");
    }

    return _actual;
}

void Candidats::seguent(){
    if (esFi()){
        cerr << "No hi han més candidats"<<endl;
        throw ("No hi han més candidats");
    }

    _actual++;
}
