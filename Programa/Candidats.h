/**
 * @file Candidats.h
 * @brief Representa la gestió de candidats del backtracking
 * @author David Soler Flores (u6106247)
 * @date 07/02/2026
 */

#ifndef CANDIDATS_H
#define CANDIDATS_H
#include <iostream>

using namespace std;


/**
 * @class Candidats
 * @brief Itera i gestiona els possibles grups d'una assignatura
 */
class Candidats {

    private:

        /// @brief Candidat (grup) actual
        int _actual; 
        /// @brief Valor que suposa el limit de _actual. 
        int _maxim;
        

    public:
        /**
         * @brief Constructor per defecte amb paràmetres opcionals
         */
        Candidats(int maxim = 0, int actual = 0);
        
        /**
         * @brief Indica si no queden candidats
         * @return True si no queden candidats, false c.c.
         */
        bool esFi()const;

        /**
         * @brief Retorna el candidat actual
         * @pre not esFi()
         * @return Candidat actual
         */
        int actual()const;

        /**
         * @brief Avança al següent candidat
         * @pre not esFi()
         * @post Avança el candidat
         */
        void seguent();
};

#endif