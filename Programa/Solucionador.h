/**
 * @file Solucionador.h
 * @brief Objecte que permet solucionar el problema plantejat amb backtracking
 * @author David Soler Flores (u6106247)
 * @date 07/02/2026
 */

#ifndef SOLUCIONADOR_H
#define SOLUCIONADOR_H
#include <iostream>
#include "Horari.h"
#include "Solucio.h"
using namespace std;

/**
 * @class Solucionador
 * @brief Permet solucionar el problema d'assignacions d'horaris sense solapaments.
 * Mostra totes les possibles solucions (Si n'hi ha) i després indica quantes n'ha trobat
 */
class Solucionador {

    private:
        /**
         * @brief Algorisme backtracking_totes. Tant punt en troba, les mostra. No les guarda
         * @param s Solució passada per referència per poder modificar-la
         */
        void backtracking(Solucio & s);
            int solus; // Numero de solucions trobades

    public:
        /**
         * @brief Constructor per defecte
         * 
         * Inicialitza el nombre de solucions a 0
         */
        Solucionador();

        /**
         * @brief Soluciona la combinació de diferents assignatures en horari sense solapaments
         * @param assignatures Vector d'assignatures
         * @param restriccions Matriu de sets on indica quines restriccions s'han de respectar
         * Matriu on el primer vector indica les assignatures - 
         * El segon guarda 3 tipus de restriccions (teoria, pràctiques, problemes) - 
         * El set, donat una assignatura i un tipus de classe, guarda totes les assignatures amb restriccions - 
         */
        void solucionar(const Solucio & s);
};

#endif