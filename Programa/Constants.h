/**
 * @file Constants.h
 * @brief Representa les constant i funcions s a tot el programa
 * @author David Soler Flores (u6106247)
 * @date 07/02/2026
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
#include <vector>
#include <map>
using namespace std;


/**
 * Constants per facilitar el disseny del programa. 
 * Es declaren a una classe externa per tal que tots els objectes puguin accedir
 */


const string PROBLEMES = "problemes";
const string PRACTIQUES = "pràctiques";
const string TEORIA = "teoria";

const vector<string> dies = {"Dilluns", "Dimarts", "Dimecres", "Dijous", "Divendres"};

/// Mètodes accessibles per tots els objectes

/**
 * @brief Indica quin dia representa \p dia a la setmana en base 0
 * @param dia Nom del dia en format de text amb la primera lletra en majúscules
 * @pre Ha de ser un dia real
 * @post Indica quin dia de la setmana és \p dia 
 * @return L'index en base 0 de \p dia 
 * @note Encara que sigui lineal, és constant. Sempre és 5 -> 0(1)
 */
int convertirDiaNumero(const string & dia);

/**
 * @brief Indica quin dia lectiu de la setmana es troba a la posició \p dia en base 0
 * @param dia Ha d'estar entre 0 i 4
 * @return El dia corresponent a \p dia  Si no existeix, retorna "-" 
 */
string convertirDiaString(int dia);




#endif