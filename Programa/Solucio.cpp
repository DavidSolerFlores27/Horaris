#include "Solucio.h"
using namespace std;


const vector<string> Solucio::clases_d_una_assignatura = {TEORIA, PRACTIQUES, PROBLEMES};

Solucio::Solucio(){
    combinacio.resize(0);
    assignatures.resize(0);

    assignatura_actual = 0;
    this->clase_actual = 0;
    this-> temps = 0;
}

Solucio::Solucio(const vector<Assignatura> & assignatures, const vector<vector<set<string>>> & restriccions, const FranjaHoraria & desc, const vector<FranjaHoraria> & dies ){
    this->assignatures = assignatures;

    combinacio.resize(assignatures.size());
    for (int i = 0; i<combinacio.size(); i++){

        combinacio[i].nom = assignatures[i].obtenirNom(); 
        combinacio[i].restriccions = restriccions[i];

        posicio_assignatures.insert({assignatures[i].obtenirNom(), i});

    }
    assignatura_actual = 0;
    clase_actual = 0;
    horari.afegirRestriccionsDiaries(dies);
    horari.afegirDescans(desc);
}

Candidats Solucio::inicialitzarCandidats()const{
    if (assignatures.empty()){
        return Candidats();
    }
    return Candidats(assignatures[assignatura_actual].opcions(clases_d_una_assignatura[clase_actual]));

}


int Solucio::obtenirPosicio(const string & assignatura)const{
    map<string, int> :: const_iterator it = posicio_assignatures.find(assignatura);

    if (it == posicio_assignatures.end()){
        cerr << "No existeix l'assignatura: "<<assignatura;
        throw ("No s'ha trobat l'assignatura");
    }

    return it->second;
}

bool Solucio::acceptable(const Candidats & cand)const{

    if (not combinacio[assignatura_actual].restriccions[clase_actual].empty()){ // Si té restriccions de grup
        set<string>::const_iterator it = combinacio[assignatura_actual].restriccions[clase_actual].begin();
        set<string>::const_iterator fi = combinacio[assignatura_actual].restriccions[clase_actual].end();
        bool disponible = true;
        int max = combinacio[assignatura_actual].restriccions[clase_actual].size();  // Fins a quin grup hem de mirar

        while (it != fi and disponible){
            
            int pos_restriccio = obtenirPosicio(*it);
            if (pos_restriccio < assignatura_actual){  // Si la restricció és d'un nivell anterior (Si ja l'hem anotat)

                int grup_res;
                int grup_actual;

                if (clases_d_una_assignatura[clase_actual] == TEORIA){
                     grup_res = combinacio[pos_restriccio].teoria[0].obtenirGrup();  // El grup de teoria és sempre el mateix. Amb un ens serveix
                     grup_actual = assignatures[assignatura_actual].obtenirTeories(cand.actual())[0].obtenirGrup();
                }else{

                    grup_actual = assignatures[assignatura_actual].obtenirClasse(cand.actual(), clases_d_una_assignatura[clase_actual]).obtenirGrup();
                    
                    if (clases_d_una_assignatura[clase_actual] == PRACTIQUES){
                            grup_res = combinacio[pos_restriccio].practiques.obtenirGrup();
                    }else{
                            grup_res = combinacio[pos_restriccio].problemes.obtenirGrup();

                    }
                }
                disponible = grup_res == grup_actual;

            }
            it++;
        }
        if (not disponible){
            return false;
        }

    }
    

    // Cas especial: Si és de teoria, hem de mirar totes les hores.
    if (clases_d_una_assignatura[clase_actual] == TEORIA){
        vector<Classe> teories = assignatures[assignatura_actual].obtenirTeories(cand.actual());
        int i = 0;
        bool disponible = true;
        while (i<teories.size() and disponible){
            disponible = horari.disponible(teories[i], combinacio[assignatura_actual].restriccions[clase_actual]);
            i++;
        }
        
        return disponible;
        
    }

    

    // Mirem si la clase de pràctiques o problemes no coincideix amb qualsevol altra, ignorant les restriccions
   return horari.disponible(assignatures[assignatura_actual].obtenirClasse(cand.actual(), clases_d_una_assignatura[clase_actual]), combinacio[assignatura_actual].restriccions[clase_actual]);
    
}

bool Solucio::esCompleta()const{
    return assignatura_actual == assignatures.size() and clase_actual == 0;
}


void Solucio::anotar(const Candidats & cand){
    string clase_act = clases_d_una_assignatura[clase_actual];
    if (clase_act == TEORIA){
        vector<Classe> teories = assignatures[assignatura_actual].obtenirTeories(cand.actual());
        combinacio[assignatura_actual].teoria = teories;

        for (int i = 0; i<teories.size(); i++){
            horari.inserirClasse(teories[i]);
        }
    }else{
        Classe cl = assignatures[assignatura_actual].obtenirClasse(cand.actual(), clase_act);
            
        horari.inserirClasse(cl);
        if (clase_act == PRACTIQUES){
            combinacio[assignatura_actual].practiques = cl;
        }else{
            combinacio[assignatura_actual].problemes = cl;
        }
    

    }

    modificarNivell(true);
    while (assignatura_actual < assignatures.size() and assignatures[assignatura_actual].opcions(clases_d_una_assignatura[clase_actual]) == 0){
        modificarNivell(true);
    }  
    
}

void Solucio::modificarNivell(bool sumar){
    if (sumar){
        clase_actual++;
        if (clase_actual == clases_d_una_assignatura.size()){
            clase_actual = 0;
            assignatura_actual++;
        }

    }else{

        clase_actual--;
        if (clase_actual < 0){
            clase_actual = clases_d_una_assignatura.size()-1;
            assignatura_actual--;
        }
    }

}

void Solucio::desanotar(const Candidats & cand){
    modificarNivell(false);

    while (assignatura_actual >= 0 and assignatura_actual < assignatures.size() and assignatures[assignatura_actual].opcions(clases_d_una_assignatura[clase_actual]) == 0){
        modificarNivell(false);
    }

    string clase_act = clases_d_una_assignatura[clase_actual];

    if (clase_act == TEORIA){
        vector<Classe> teories = assignatures[assignatura_actual].obtenirTeories(cand.actual());

        for (int i = 0; i<teories.size(); i++){
            horari.esborrarClasse(teories[i]);
        }
    }else{
        Classe cl = assignatures[assignatura_actual].obtenirClasse(cand.actual(), clase_act);
        horari.esborrarClasse(cl);
    }
}


void Solucio::mostrar()const{
    cout << string(50, '=')<<endl;
    cout << "Grups: "<<endl << endl;
    for (int i = 0; i<combinacio.size(); i++){

        cout << combinacio[i].nom << ":" <<  endl;
        cout << "   -> Teoria:"<<endl;
        for (int j = 0; j<combinacio[i].teoria.size(); j++){
            cout << "           "<< combinacio[i].teoria[j]<<endl;
        }

        if (combinacio[i].practiques.classeDefinida()){
            cout << "   -> Pràctiques: "<<endl;
            cout << "           "<<combinacio[i].practiques<<endl;
        }

        if (combinacio[i].problemes.classeDefinida()){
                cout << "   -> Problemes: "<<endl;
                cout << "           "<<combinacio[i].problemes<<endl;
        }
        cout << endl;
        
    }
    cout << string(50, '.')<<endl;

    cout << "Descans: "<<endl;
    horari.mostrarDescansos();
     cout << string(50, '.')<<endl;
    cout << string(50, '=')<<endl;
}

void Solucio::calcularTemps(){
    this->temps = horari.minutsMig();
}


bool Solucio::esMillor(const Solucio & s)const{
    if (s.assignatures.empty()){
        return true;
    }

    return horari.minutsMig() < s.temps;

}