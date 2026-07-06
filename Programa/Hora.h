/**
 * @file Hora.h
 * @brief Representa una hora en 24 h
 * @author David Soler Flores (u6106247)
 * @date 07/02/2026
 */
#ifndef HORA_H
#define HORA_H
#include <iostream>

using namespace std;
/**
 * @class Hora
 * @brief Representa una hora en 24 h
 * 
 * Permet construïr l'hora, saber si és vàlida, i els operadors
 */
class Hora {

    private:
        int hora, min;

    public:
        /**
         * @brief Constructor per defecte amb paràmetres opcionals
         */
        Hora(int h = 0, int m = 0);

        /**
         * @brief Indica si una hora és vàlida
         * @return True si 0 <= h <= 23 i 0 <= min <= 59
         */
        static bool esValida(int h, int min);

        /**
         * @brief Duració de *this
         * @return Duració en minuts de *this
         */
        int minuts()const;

        /**
         * @brief Indica si es pot sumar \p min a *this
         */
        bool esPotSumar(int min)const;

        /**
         * @brief Suma \p min a *this
         * @pre es pot sumar \p min a *this
         */
        void sumar(int min);

        /**
         * @brief Calcula la diferència en minuts entre dues hores. 
         */
        int resta(const Hora & h)const;

        /// @brief Indica si *this < h
        bool operator<(const Hora & h)const;
        /// @brief Indica si *this == h
        bool operator==(const Hora & h)const;
        /// @brief Indica si *this <= h
        bool operator<=(const Hora & h)const;

        bool operator!=(const Hora & h)const;

        Hora operator-(const Hora & h)const;

        bool operator>(const Hora & h)const;
    
        bool operator>=(const Hora & h)const;

        /// @brief Sobrecàrrega de l'operador <<.
        /// Mostra per pantalla l'hora (HH:MM)
        friend ostream& operator<<(ostream & os, const Hora & h);

};

#endif