#include "Classe.h"
using namespace std;

Classe::Classe(const string & nom_assignatura, const string & dia,  const Hora & in, const Hora & fi, const string & tipus, int grup,  bool obligatoria, const string & setmana  ){
    this->assignatura = nom_assignatura;
    this->dia = convertirDiaNumero(dia);
    this->franja = FranjaHoraria(in, fi);
    this->tipus = tipus;
    this->grup = grup;
    this->_obligatoria = obligatoria;
    this->setmana = convertirSetmana(setmana);

}



bool Classe::esSetmanaA()const{
    return setmana == "A/B" or setmana == "A";
}

bool Classe::esSetmanaB()const{
    return setmana == "A/B" or setmana == "B";
}

int Classe::obtenirDia()const{
    return dia;
}

int Classe::obtenirGrup()const{
    return grup;
}

FranjaHoraria Classe::franjaHoraria()const{
    return franja;
}


bool Classe::obligatoria()const{
    return this->_obligatoria;
}


bool Classe::hiHaSolapament(const Classe & a, const Classe & b){
    return FranjaHoraria::hiHaSolapament(a.franjaHoraria(), b.franjaHoraria());
}


bool Classe::operator<(const Classe & c) const {
    if (dia != c.dia){
        return dia < c.dia;
    } 
    if (franja != c.franja){
        return franja < c.franja;
    }
    if (tipus != c.tipus){
        return tipus < c.tipus;
    }
    if (grup != c.grup){
        return grup < c.grup;
    }
    if (setmana != c.setmana){
        return setmana < c.setmana;
    }
    return assignatura < c.assignatura;
}


bool Classe::classeDefinida()const{
    return dia >= 0 and dia < 5;
}

ostream & operator<<(ostream & os, const Classe & c){

    if (c.classeDefinida()){
        os << c.tipus << "-" << c.grup << "(Set "<<c.setmana<<") "<<endl;
        os<< "          "<<convertirDiaString(c.dia)<< " (" << c.franja<<")";
    }



    return os;
}

bool Classe::operator==(const Classe & c)const{
    return this->dia == c.dia and 
            this->franja == c.franja and
            _obligatoria == c._obligatoria and 
            this->assignatura == c.assignatura and
             this->tipus == c.tipus and 
             this->setmana == c.setmana and
             this->grup == c.grup;
}

bool Classe::operator!=(const Classe & c)const{
    return not (*this == c);
}


string Classe::convertirSetmana(const string & set){
    if (set.size() == 2){
        return "A/B";
    }

    return set;
}

string Classe::obtenirNom()const{
    return assignatura;
}

