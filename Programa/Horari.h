/**
 * @file Horari.h
 * @brief Objecte que representa un horari de dues setmanes amb classes
 * @author David Soler Flores (u6106247)
 * @date 07/02/2026
 */

#ifndef HORARI_H
#define HORARI_H
#include <iostream>
#include <vector>
#include "Dia.h"
using namespace std;



/**
 * @class Horari
 * @brief Representa l'horari en dues setmanes (A i B) i disposa els mètodes per saber si una classe es pot afegir, afegir-la i esborrar-la
 */
class Horari {

    private:

        /// @brief Representació: Dos vectors de Dies. 

        vector<Dia> setA;
        vector<Dia> setB;


    public:
    
        /**
         * @brief Constructor per defecte
         * @post Reasigna la mida dels dos vectors perquè simbolitzin una setmana lectiva (5 posicions)
         */
        Horari();

        /**
         * @brief Inicialitza la franja horària de descans a tots els dies de ambdues setmanes
         */
        void afegirDescans(const FranjaHoraria & desc);

        /**
         * @brief Afegeix les restriccions als dies corresponents de *this
         */
        void afegirRestriccionsDiaries(const vector<FranjaHoraria> & desc);

        /**
         * @brief Indica si una classe es pot afegir a *this
         * @pre \p cl .classeDefinida()
         * @param cl Classe que es vol afegir.
         * @param res Set de restriccions de \p cl
         * @return True si es pot afegir a les setmanes corresponents a \p cl
         */
        bool disponible(const  Classe & cl, const set<string> & res)const;

        /**
         * @brief Insereix \p cl a la setmana i dia corresponent
         * @pre \p cl .classeDefinida() and this->disponible( \p cl )
         * @param cl Classe que s'afegiex
         */
        void inserirClasse(const Classe & cl);

        /**
         * @brief Esborra \p cl a la setmana i dia corresponent
         * @pre \p cl s'ha hagut d'afegir anteriorment
         * @param cl Classe que s'esborra
         */
        void esborrarClasse(const Classe & cl);

        /**
         * @brief Mostra la franja horària dels descansos de tots els dies.
         */
        void mostrarDescansos()const;


};

#endif