/**
 * @file Solcio.h
 * @brief Objecte que representa una solució (completa o no) 
 * @author David Soler Flores (u6106247)
 * @date 07/02/2026
 */

#ifndef SOLUCIO_H
#define SOLUCIO_H
#include <iostream>
#include "Horari.h"
#include <vector>
#include "Candidats.h"
using namespace std;


/**
 * @class Solucio
 * @brief Representa una combinació de classes en un horari sense solapaments
 */
class Solucio {

    private:

        map<string, int> posicio_assignatures; // Per buscar amb temps logarítmic la posició d'una assignatura a partir del nom
        static const vector<string> clases_d_una_assignatura;

        Horari horari;   // Unicament per anotar, desanotar, i acceptable

        /// @brief Objecte d'una assignatura simplificat. Només un grup per cada classe 
        struct _Assignatura{
            string nom;
            vector<Classe> teoria;
            Classe practiques;
            Classe problemes;

            _Assignatura(){
                this->nom = "";
            }

            /**
             * @brief vector de set de restriccions
             * 
             * El vector és per diferenciar entre teoria, pràctiques o problemes
             * 
             *  El set indica les assignatures
             */
            vector<set<string>> restriccions;  
            
        };
        
        vector<_Assignatura> combinacio;  // Solució arribada

        vector<Assignatura> assignatures; // Informació completa de totes les assignatures

        int assignatura_actual;  // Nivell I per tractar totes les assignatures

        int clase_actual; // Nivell II: Donada una assignatura, ha d'assignar teoria, pràctiques i problemes.

        /**
         * @brief Modifica el nivell actual (avança o retrocedeix segons \p sumar )
         * @param sumar Indica si vol que avanci (true) o retrocedeixi (false)
         * 
         * Modifica el nivell protegint els limits per no accedir fora de rang
         */
        void modificarNivell(bool sumar);

        /**
         * @brief Donat el nom d'una assignatura, retorna la posició que es troba al vector (this->assignatures)
         * @pre \p assignatura ha d'existir al vector que s'ha passat al constructor. En c.c. llança excepció
         * @param assignatura Nom de l'assignatura que es busca
         * @note O(log(n)) sent n el nombre d'assignatures
         */
         int obtenirPosicio(const string & assignatura)const;

    public:
        /**
         * @brief Constructor per defecte
         * @post Construeix una solució buida
         */
        Solucio();

        /**
         * @brief Constructor amb paràmetres
         * @post Construeix una solució no completa
         * @param assignatures Vector amb totes les assignatures i amb la seva informació
         * @param restriccions Matriu on indica quines restriccions s'han de respectar
         * Matriu on el primer vector indica les assignatures - 
         * El segon guarda 3 tipus de restriccions (teoria, pràctiques, problemes) - 
         * El set, donat una assignatura i un tipus de classe, guarda totes les assignatures amb restriccions - 
         * @param descans Franja horària que indica els limits diaris de cada descans
         * @param dies Limits de franjes horàries disponibles per cada dia de la setmana (Dilluns = 0...Divendres = 5)
         */
        Solucio(const vector<Assignatura> & assignatures, const vector<vector<set<string>>> & restriccions, const FranjaHoraria & descans, const vector<FranjaHoraria> & dies );

        /**
         * @brief Donada una assignatura i un tipus de classe, retorna els candidats de grups
         * @return Objecte Candidats
         */
        Candidats inicialitzarCandidats()const;

        /**
         * @brief Indica si el candidat actual (cand.actual()) és vàlid a la solució actual
         * @param cand Not cand.esFi()
         * @return True si en el nivell actual (assignatura i grup) és vàlid aquell grup. Fals c.c.
         * @details Aquest mètode es divideix entre tres casos (2 d'ells possibles):
         * 
         *  - Si l'assignatura actual té restriccions, hem de mirar per totes les seves restriccions: 
         *          - Si ja han estat definides (s'han anotat en un nivell anterior)
         *          - Si els seus grups de la restricció que demana coincideixen amb el candidat actual.
         *              És condició necessària però no suficient. S'ha de seguir mirant els altres dos casos
         * 
         * - Es diferencia entre TEORIA i (PRACTIQUES O PROBLEMES):
         *  - Si la classe actual és TEORIA, hem de comprobar amb l'horari si qualsevol de les classes es solapen amb 
         *      alguna altra ja definida. Per això mirem horari, on anem guardant totes les classes de la solució actual
         * 
         * - Si la classe és PRACTIQUES o PROBLEMES només té una classe, aixi que amb una crida a horari fem prou.
         */
        bool acceptable(const Candidats & cand)const;

        /**
         * @brief Anota el candidat actual (cand.actual()). Defineix quin grup toca en una assignatura i un tipus de classe concret
         * @pre not cand.esFi() and this->acceptable( \p cand )
         * @post Anota el candidat actual i avança el nivell
         * @param cand Indica el candidat actual
         */
        void anotar(const Candidats & cand);
        
        /**
         * @brief Desanota el candidat actua i resta el nivell
         */
        void desanotar(const Candidats & cand);

        /**
         * @brief Indica si s'han combinat totes les assignatures i un grup.
         * @return True si s'ha arribat a una solució vàlida. Fals en c.c.
         */
        bool esCompleta()const;

        /// @brief Mostra la solució: Mostra les combinacions (en cada combinació mostra el grup de teoria, problemes i pràctiques si estàn definits)
        void mostrar()const;

};

#endif