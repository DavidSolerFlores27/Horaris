#include "Solucionador.h"

using namespace std;

Solucionador::Solucionador(){
    solus = 0;
}

void Solucionador::solucionar(const Solucio & s){

    Solucio sol = s;
    backtracking(sol);
    cout << endl << "TOTAL SOLUCIONS: "<<solus<<endl;
    cerr << endl << "TOTAL SOLUCIONS: "<<solus<<endl;

    if (solus > 1){
        cout << "Millor solució: "<<endl;
        millor.mostrar();
    }


}

void Solucionador::backtracking(Solucio & s){
    Candidats cand = s.inicialitzarCandidats();

    while (not cand.esFi()){
        if (s.acceptable(cand)){
            s.anotar(cand);
            if (not s.esCompleta()){
                backtracking(s);
            }else{
                solus++;
                
                   s.mostrar();
                    cout << "\n";
                    if (s.esMillor(millor)){
                        millor = s;
                        millor.calcularTemps();
                    }

            }

            s.desanotar(cand);
        }

        cand.seguent();
    }
}