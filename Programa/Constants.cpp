#include "Constants.h"
using namespace std;

int convertirDiaNumero(const string & dia){
    bool trobat = false;
    int i = 0;

    while (i<dies.size() and not trobat){
        trobat = dies[i] == dia;
        if (not trobat){
            i++;
        }
    }

    return i;
}


string convertirDiaString(int dia){
    if (dia < 0 or dia >= dies.size()){
        return "-";
    }
    return dies[dia];
}

