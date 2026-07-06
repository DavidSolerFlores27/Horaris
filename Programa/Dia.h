/**
 * @file Dia.h
 * @brief Objecte que representa un dia entre dilluns i divendres
 * @author David Soler Flores (u6106247)
 * @date 07/02/2026
 */


#ifndef DIA_H
#define DIA_H
#include <iostream>
#include <vector>
#include "Classe.h"
#include <map>
#include <set>
#include <list>
#include "Assignatura.h"
using namespace std;



/**
 * @class Dia
 * @brief Representa un dia lectiu i conté classes sense solapaments
 * 
 * Té els mètodes adients per tal de saber si una classe es pot afegir, per afegir i eliminar de *this
 * 
 */
class Dia {

    private:
        set<Classe> horari;  // Horari de classes ordenades i úniques
        FranjaHoraria desc; // Franja horària per determinar el descans
        list<pair<Classe, FranjaHoraria>> hist_desc;  // Historial de descansos anteriors. Al desanotar, he de saber quin descans anava abans
        FranjaHoraria limit;     // Limit d'hores a l'uni


        /**
         * @brief Indica si el nom de \p c pertany a les restriccions \p res
         * @return True si \p c existeix a \p res
         */
        static bool pertany(const Classe & c, const set<string> & res);

        /**
         * @brief Indica si \p classe pot evitar solapaments amb el descans
         */
        bool compleixDescans(const FranjaHoraria & classe)const;

        /**
         * @brief Modifica desc per ajustar-ho a \p f perquè no hi hagin solapaments
         */
        void ajustarDescans(const FranjaHoraria & f);

        /**
         * @brief Calcula el temps que s'ha de sumar a ambdós limits dels descans per tal que no hi hagin solapaments
         * @pre Ha d'estar solapat i ha de ser possible moure el descans (cas 5)
         */
        pair<int, int> tempsNecessaris(const FranjaHoraria & f)const;


        /**
         * @brief Indica si la franja horària del descans és completament a dins de \p f (Cas 5)
         */
        bool impossibleMoureDescans(const FranjaHoraria & f)const;

        /**
         * @brief Indica si \p classe es troba fora dels limits de la franja horària de limit
         */
        bool foraLimit(const FranjaHoraria & classe)const;

    public:
        /// @brief Constructor per defecte
        Dia();

        /// @brief Defineix el limit horari de *this
        /// @param f Franja horària, màxima i minima que el usuari vol anar *this
        void definirLimit(const FranjaHoraria & f);

        /**
         * @brief Defineix els descans
         */
        void definirDescans(const FranjaHoraria & f);

        /**
         * @brief Indica si es pot afegir \p cl a *this
         * @pre \p cl .classeDefinida()
         * @post Indica si no hi ha cap solapament que en les classes de *this amb \p cl
         * @param cl Classe que es vol afegir
         * @param res Set de restriccions de \p cl
         * @return True si \p cl es pot afegir a *this (No hi ha solapament). Fals en c.c.
         * @note O(n * log(m)) sent n el nombre d'assignatures que conté *this i m res.size()
         */
        bool esPotAfegir(const Classe & cl, const set<string> & res)const;

        /**
         * @brief Afegeix \p cl a *this
         * @pre \p c .classeDefinida and this->esPotAfegir( \p c )
         * @post \p c afegida
         * @param cl Classe que s'afegeix
         * @note O(log(n)) sent n el nombre d'assignatures que conté *this
         */
        void afegir(const Classe & c);

        /**
         * @brief Esborra \p c de *this
         * @pre \p c ha d'existir a *this (Excepció en cas contrari)
         * @post \p c esborrada
         * @note O(log(n)) sent n el nombre d'assignatures que conté *this
         */
        void esborrar(const Classe & c);

        /// @brief Mostra per pantalla el descans. Hora inicial, final i duració
        void mostrarDescans()const;

        
};

#endif