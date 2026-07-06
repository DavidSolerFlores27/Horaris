/**
 * @file FranjaHoraria.h
 * @brief Representa una Franja Horària
 * @author David Soler Flores (u6106247)
 * @date 06/07/2026
 */


#ifndef FRANJA_HORARIA_H
#define FRANJA_HORARIA_H
#include <iostream>
#include "Hora.h"
using namespace std;


/**
 * @class FranjaHoraria
 * @brief Representa una franja horària entre dues hores
 * 
 */
class FranjaHoraria {

    private:
        /// @brief Limit inicial
        Hora inicial_limit;
        /// @brief  Limit final
        Hora final_limit;

        /// @brief Hora inicial que s'ha modificat
        Hora _inicial;
        /// @brief Hora final que s'ha modificat
        Hora _final;

        ///@brief Duració minima entre _final i _inicial 
        int duracio_minima;

    public:

        /**
         * @brief Constructor amb paràmetres i per defecte
         * @param inicial Hora inicial minima que es vol la franja
         * @param final Hora final màxima que es vol la franja
         * @param duracio_minima Duració minima que ha de tenir *this 
         */
        FranjaHoraria(const Hora & inicial = Hora(), const Hora & final = Hora(), int duracio_minima = 0);

        /// @brief Indica si hi ha solapaments entre \p a i \p b
        static bool hiHaSolapament(const FranjaHoraria & a, const FranjaHoraria & b);

        /// @brief Duració de *this en minuts
        int duracio()const;

        /// @brief Temps solapat en minuts entre \p f i *this. Si no hi ha solapament, és 0 
        int tempsSolapat(const FranjaHoraria & f)const;

        /// @brief Hora inicial de *this
        Hora inicial()const;

        /// @brief Hora final de *this 
        Hora final()const;

        /**
         * @brief Indica si es poden modificar els extrems actuals, ja sigui per escurçar-los o ampliar-los
         */
        bool esPotSumar(int minutsInicial, int minutsFinal)const;

        /**
         * @brief Suma els minuts indicats al intervals. 
         * @pre Es poden sumar
         */
        void sumar(int minutsInicial, int minutsFinal);

        /// @brief Sobre-escriptura de l'operador de <<
        /// Mostra per pantalla l'hora inicial, la final i la durada 
        friend  ostream & operator<<( ostream & os, const FranjaHoraria & f );

        /// Sobreescriptura d'operadors

         bool operator<(const FranjaHoraria & f)const;
          bool operator==(const FranjaHoraria & f)const;
          bool operator!=(const FranjaHoraria & f)const;

};


#endif