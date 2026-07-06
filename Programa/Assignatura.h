/**
 * @file Assignatura.h
 * @brief Representa una assignatura, i les seves opcions
 * @author David Soler Flores (u6106247)
 * @date 07/02/2026
 */

#ifndef ASSIGNATURA_H
#define ASSIGNATURA_H
#include <iostream>
#include <list>
#include <vector>
#include "Classe.h"
#include "Constants.h"
using namespace std;

/**
 * @class Assignatura
 * @brief Representa una assignatura amb les seves classes de teoria, pràctiques i problemes
 * 
 * Permet afegir teories, i classes genèriques, les opcions de cada classe, i obtenir-les
 */
class Assignatura {

    private:
        /// @brief Nom de l'assignatura
        string nom;
        vector<vector<Classe>> teories;  // Matriu de diferents grups i les seves classes de teoria
        vector<Classe> practiques;  // Diferents grups de pràctiques
        vector<Classe> problemes;  // Diferents grups de problemes



    public:
        /**
         * @brief Constructor per defecte amb paràmetres opcionals
         * @param nom Nom de l'assignatura
         * @post Construiex una assignatura buida
         */
        Assignatura(const string & nom = "");

        /**
         * @brief Obté el nom de *this
         * @return El nom d'aquesta assignatura
         */
        string obtenirNom()const;

        /// @brief Afegeix les opcions de teoria
        void afegirTeoria(const vector<vector<Classe>> & hores);

        /**
         * @brief Afegeix les classes en el seu tipus corresponent
         * @param tipus Ha de ser "PRÀCTIQUES" o "PROBLEMES" 
         */
        void afegirClasse(const vector<Classe> & cl, const string & tipus);

        /**
         * @brief Obté les diferentes opcions per cada tipus
         * @param tipus Ha de ser "PRÀCTIQUES" o "PROBLEMES" 
         */
        int opcions(const string & tipus)const;

        /**
         * @brief Obté les teories d'un grup en concret
         * @pre teories not empty
         * @param grup Ha de ser >= 0 i < size() 
         */
        vector<Classe> obtenirTeories(int grup)const;

        /**
         * @brief Obté les classes d'un tipus de classe en concret.
         * @pre problemes o pràctiques (depenent de tipus) not empty()
         * @param grup NO HA DE SER EL GRUP. Ha de ser la posició. El cand.actual(); 
         */
        Classe obtenirClasse(int grup, const string & tipus)const;

        
        

        
};

#endif