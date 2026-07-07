#include "Horari.h"
using namespace std;

Horari::Horari(){
    this->setA.resize(dies.size());
    this->setB.resize(dies.size());
}

void Horari::afegirDescans(const FranjaHoraria & desc){
    for (int i = 0; i<dies.size(); i++){
        setA[i].definirDescans(desc);
        setB[i].definirDescans(desc);
    }
}

void Horari::afegirRestriccionsDiaries(const vector<FranjaHoraria> & dies){
    for (int i = 0; i<dies.size(); i++){
        setA[i].definirLimit(dies[i]);
        setB[i].definirLimit(dies[i]);
    }
}


bool Horari::disponible(const Classe &cl, const set<string> & res)const{
    bool afegir = true;
    if (cl.esSetmanaA()){
        afegir = setA[cl.obtenirDia()].esPotAfegir(cl, res);
    }

    if (cl.esSetmanaB()){
        afegir = afegir and setB[cl.obtenirDia()].esPotAfegir(cl, res);
    }


    return afegir;
}


void Horari::inserirClasse(const Classe & cl){
    if (cl.esSetmanaA()){
        setA[cl.obtenirDia()].afegir(cl);
    }

    if (cl.esSetmanaB()){
        setB[cl.obtenirDia()].afegir(cl);
    }
}


void Horari::esborrarClasse(const Classe & cl){
    if (cl.esSetmanaA()){
        setA[cl.obtenirDia()].esborrar(cl);
    }
    if (cl.esSetmanaB()){
        setB[cl.obtenirDia()].esborrar(cl);
    }
}


void Horari::mostrarDescansos()const{
    cout << "   -> Setmana A:"<<endl;
    for (int i = 0; i<5; i++){
        cout << "       ->"<<convertirDiaString(i)<<" ";
         setA[i].mostrarDescans();
        cout << endl;
    }

    cout << "   -> Setmana B:"<<endl;
    for (int i = 0; i<5; i++){
        cout << "       ->"<<convertirDiaString(i)<<" ";
        setB[i].mostrarDescans();
        cout <<endl;
    }

}


int Horari::minutsMig()const{
    int total = 0;
    for (int i = 0; i<dies.size(); i++){
        total += setA[i].minutsMig() + setB[i].minutsMig();
    }

    return total;
}