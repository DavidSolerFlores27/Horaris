/**
 * @file main.cpp
 * @brief Programa principal
 * @author David Soler Flores (u6106247)
 * @date 07/02/2026
 */


#include <iostream>
#include <fstream>
#include "Horari.h"
#include "Solucionador.h"
using namespace std;



/// @brief Constant per assignatura no obligatòria
const int NO_OBLIGATORIA = 0;
/// @brief Constant per assignatura obligatòria
const int OBLIGATORIA = 1;




/**
 * @brief Llegeix una hora per teclat
 */
Hora llegirHora(){
    int h, m;
    cin >> h >> m;
    return Hora(h,m);
}


/**
 * @brief Funció per llegir una classe sencera a partir del fitxer
 * @pre  \p nom not buit, \p tipus ha de ser: (TEORIA, PRACTIQUES, PROBLEMES)
 * @post Retorna la classe llegida pel \p fin
 * @param nom Nom de l'assignatura de la classe
 * @param tipus Tipus de classe (TEORIA, PRACTIQUES, PROBLEMES)
 * @param obl Booleà que indica si és obligatòria o no
 * @return Classe llegida
 * 
 */
Classe llegir_classe(const string & nom, const string & tipus, bool obl){

    int grup;
    string dia;
    cin >> grup >> dia;
    Hora inici = llegirHora();
    Hora final = llegirHora();

    if (tipus == TEORIA){
        return Classe(nom, dia, inici, final, tipus, grup, obl);
    } 

    string setmanes;

    cin >> setmanes;



    return Classe (nom,dia, inici, final, tipus, grup, obl,setmanes);
}


/**
 * @brief Llegeix les restriccions i les omple a \p res a la posició \p index
 * @pre  \p index < res.size() i \p index >= 0, \p res not buit
 * @post Omple res[i] amb les restriccions
 * @param index Indica si llegueix teoria, pràctiques o problemes (0,1,2), respectivament
 * @param res vector de sets on el vector indica quina tipus de classe llegeix i el set guarda les restriccions.
 */
void llegirRestriccions(int index, vector<set<string>> & res){
    int n;
    cin >> n;


    for (int i = 0; i<n; i++){
        string assignatura;
        getline(cin >> ws, assignatura);
        res[index].insert(assignatura);
    }
}

/**
 * @brief Llegeix les classes i restriccions d'una assignatura i un tipus de classe
 * @pre \p nom_assignatura not buit, \p tipus definit,  \p index < res.size() i \p index >= 0, \p res not buit
 * @post Llegeix totes les classes i les seves restriccions i les omple a \p vec i a \p res respectivament
 * @param vec vector on es guarden les classes
 * @param res vector de sets  on es guarden les restriccions
 */
void llegirClasses(const string & nom_assignatura, const string & tipus, int j,  vector<Classe> &  vec, vector<set<string>> & res){
    int grups;
    int obligatoria;

    cin >> grups;

    vec.resize(grups);

    if (grups != 0){
        cin >> obligatoria;

        for (int i = 0; i<grups; i++){
            vec[i] = llegir_classe(nom_assignatura, tipus, obligatoria == OBLIGATORIA);
        }

        llegirRestriccions(j, res);
    }


     
}


/**
 * @brief Llegeix una assignatura (nom, classes (teoria, pràctiques, problemes)) i les seves restriccions i la retorna
 */
Assignatura llegir_assignatura(vector<set<string>> & res){
    string nom;
    getline(cin >> ws, nom);

   
    int obligatoria;
    int grups, hores_teoria;
    cin >> grups;
    if (grups != 0){
        cin >> hores_teoria >> obligatoria;
    }


     Assignatura a(nom);

    vector<vector<Classe>> teories(grups);


    for(int i = 0; i<grups; i++){
        teories[i].resize(hores_teoria);
        for (int j = 0; j<hores_teoria; j++){
            teories[i][j] = llegir_classe(nom, TEORIA, obligatoria == OBLIGATORIA);
        }
    }

    if (grups != 0){
        llegirRestriccions(0, res);
    }





    vector<Classe> practiques;
    vector<Classe> problemes;

    llegirClasses( nom, PRACTIQUES, 1, practiques, res);
    llegirClasses(nom, PROBLEMES, 2, problemes, res);



    a.afegirTeoria(teories);
    a.afegirClasse(practiques, PRACTIQUES);
    a.afegirClasse(problemes, PROBLEMES);



    return a;
}


/**
 * @brief Llegeix les assignatures i les seves restriccions. 
 */
void llegir_assignatures(vector<Assignatura> & assignatures, vector<vector<set<string>>> & restriccions){

        int n_assig;
        cin >>  n_assig;

        assignatures.resize(n_assig);
        restriccions.resize(n_assig);
        for (int i = 0; i<n_assig; i++){
            restriccions[i].resize(3);
        }


        for (int i = 0; i<assignatures.size(); i++){
            assignatures[i] =  llegir_assignatura(restriccions[i]);

        }

}

/**
 * @brief Llegiex una franja horària i la retorna
 */
FranjaHoraria llegirFranja(bool llegir_duracio = false){
    Hora a = llegirHora();
    Hora b = llegirHora();
    
   
    if (llegir_duracio){
         int dur_min;
         cin >> dur_min;
         return FranjaHoraria(a, b, dur_min);
    }
   

    return FranjaHoraria(a, b);
}


/**
 * @brief Llegiex un descans i ho retorna
 */
FranjaHoraria llegirDescans(){
    int n;
    cin >> n;
    FranjaHoraria f;

    if (n != 0){
        f = llegirFranja(true);
    }
    return f;
}

/**
 * @brief Llegiex els limits per pantalla i els omple a \p vec
 */
void llegirLimit(vector<FranjaHoraria> & vec){
    int n_dies;
    cin >> n_dies;
    vector<bool> dies_seleccionats(dies.size(), false);

    for (int i = 0; i<n_dies; i++){
        string dia;
        cin >> dia;
        dies_seleccionats[convertirDiaNumero(dia)] = true;
    }

    FranjaHoraria restriccio = llegirFranja();

    for (int i = 0; i<dies.size(); i++){
        if (dies_seleccionats[i]){
            vec[i] = restriccio;
        }
    }

}

/**
 * @brief Llegiex els limits diaris d'hores i ho retorna. Per defecte és de 00:00 a 23:59
 */
vector<FranjaHoraria> llegirLimitsDiaris(){

    vector<FranjaHoraria> res(dies.size(), FranjaHoraria(Hora(0, 0), Hora(23, 59)));
    int n;
    cin >> n;
    for (int i = 0; i<n; i++){
        llegirLimit(res);
    }

    return res;
}


int main() {
    vector<Assignatura> assignatures;
    /**
     * Matriu de sets on el primer vector indica les assignatures
     * El segon guarda 3 tipus de restriccions (teoria, pràctiques, problemes)
     * El set, donat una assignatura i un tipus de classe, guarda totes les assignatures amb restriccions
     */
    vector<vector<set<string>>> restriccions;
    llegir_assignatures(assignatures, restriccions);

    vector<FranjaHoraria> limits_dies = llegirLimitsDiaris();
    FranjaHoraria descans = llegirDescans();

    Solucio s(assignatures, restriccions, descans, limits_dies);
    Solucionador sol;
    sol.solucionar(s);

    return 0;
}








