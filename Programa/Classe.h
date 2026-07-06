/**
 * @file Classe.h
 * @brief Representa una assignatura, i les seves opcions
 * @author David Soler Flores (u6106247)
 * @date 07/02/2026
 */
#ifndef CLASSE_H
#define CLASSE_H
#include <iostream>
#include "FranjaHoraria.h"
#include "Constants.h"
using namespace std;
/**
 * @class Classe
 * Guarda les dades d'una classe en concret, d'un tipos, d'una assignatura, en un dia, els seus horaris i la setmana que pertany
 * Disposa de getters per obtenir l'informació necessària. 
 */
class Classe {

    private:
        /// @brief Indica quin dia de la setmana és la classe (0-4)
            int dia;

        /// @brief Indica la frànja horària de *this
            FranjaHoraria franja;

        /// @brief Indica si és obligatori assistir
            bool _obligatoria;

        /// @brief Indica el nom de l'assignatura que pertany
            string assignatura;

        /// @brief Indica si és de teoria, pràctiques o problemes
            string tipus;

        /// @brief Indica si és setmana A (A), b (B) o ambdues (A/B)
            string setmana;

        /// @brief Indica el número de grup que pertany
            int grup;


        /**
         * @brief Convertidor necessari per convertir "AB" a "A/B" si és necessari
         * @pre \p set ha de ser "A" or "B" or "AB" 
         * @post Retorna \p set . Si és "AB" retorna "A/B"
         * @param set Indica a quina setmana pertany
         * @return \p set com demana la classe
         */
        static string convertirSetmana(const string & set);



    public:

        /**
         * @brief Indica si ha solapament entre dues classes
         * @pre \p a i \p b han de tenir definides les hores d'inici i final
         * @post Retorna si l'hora de començament d'alguna classe és abans que l'hora de fi
         * @param a Primer classe
         * @param b Segona classe
         * @return True si hi ha solapament entre \p a i \p b . Fals en c.c.
         */
        static bool hiHaSolapament(const Classe & a, const Classe & b);

        /**
         * @brief Constructor per defecte amb paràmetres opcionals
         */
        Classe(const string & nom_assignatura = "", const string & dia = "",  const Hora & in = Hora(), const Hora & fi = Hora(), const string & tipus = "", int grup = 0,  bool obligatoria = true, const string & setmana = "AB");

        /**
         * @brief Indica si la classe és de la setmana A)
         * @return True si *this es fa a la setmana A, fals en c.c.
         */
        bool esSetmanaA()const;

        /**
         * @brief Indica si la classe és de la setmana B)
         * @return True si *this es fa a la setmana B, fals en c.c.
         */
        bool esSetmanaB()const;

        /**
         * @brief Obté el dia en que es fa la classe
         * @return Index del dia de la setmana de *this
         */
        int obtenirDia()const;

        /**
         * @brief Obté el nom de l'assignatura
         * @return this->assignatura
         */
        string obtenirNom()const;

        FranjaHoraria franjaHoraria()const;

        /**
         * @brief Indica si la classe és obligatòria (No es pot solapar)
         * @return False si *this és obligatòria. true en c.c.
         */
        bool obligatoria()const;

        /**
         * @brief Obté el grup que pertany *this
         * @return El grup que correspon *this
         */
        int obtenirGrup()const;

        /**
         * @brief Indica si *this està definit (No amb el constructor per defecte)
         * @return Si *this representa una classe vàlida
         */
        bool classeDefinida()const;
        
        /**
         * @brief Sobrecàrrega de l'operador << 
         * @post Mostra els detalls de *this
         */
        friend  ostream & operator<<( ostream & os, const Classe & c );

        /**
         * @brief Sobrecàrrega de l'operador < 
         * @pre c.classeDefinida() and this->classeDefinida()
         * @return True si *this és estrictament més petit que \p c . Fals c.c
         */
        bool operator<(const Classe & c)const;

        /**
         * @brief Sobrecàrrega de l'operador == 
         * @pre c.classeDefinida() and this->classeDefinida()
         * @return True si *this és exàctament igual que \p c . Fals c.c
         */
        bool operator==(const Classe & c)const;

        /**
         * @brief Sobrecàrrega de l'operador != 
         * @pre c.classeDefinida() and this->classeDefinida()
         * @return not (*this == c)
         */
        bool operator!=(const Classe & c)const;
        
        

};

#endif