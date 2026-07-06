#include "Solucionador.h"

using namespace std;

Solucionador::Solucionador(){
    solus = 0;
}

void Solucionador::solucionar(const Solucio & s){

    Solucio sol = s;
    backtracking(sol);
    cout << endl << "TOTAL SOLUCIONS: "<<solus;

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

            }

            s.desanotar(cand);
        }

        cand.seguent();
    }
}