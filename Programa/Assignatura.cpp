#include "Assignatura.h"
using namespace std;

Assignatura::Assignatura(const string & nom){
    this->nom = nom;
}


void Assignatura::afegirTeoria(const vector<vector<Classe>> & cl){
    this->teories = cl;
}



void Assignatura::afegirClasse(const vector<Classe> & cl, const string & tipus){
    if (tipus == PRACTIQUES){
        this->practiques = cl;
    }else{
        this->problemes = cl;
    }
}

string Assignatura::obtenirNom()const{
    return nom;
}

int Assignatura::opcions(const string & tipus)const{

    if (tipus == TEORIA){
        return teories.size();
    
    }

    if (tipus == PRACTIQUES){
        return practiques.size();
    }
    
    return problemes.size();
}


vector<Classe> Assignatura::obtenirTeories(int grup)const{
    return teories[grup];
}


Classe Assignatura::obtenirClasse(int grup, const string & tipus)const{

    if (tipus == PRACTIQUES){
        return practiques[grup];
    }

    return problemes[grup];
}

