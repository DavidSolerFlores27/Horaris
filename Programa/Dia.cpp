#include "Dia.h"
using namespace std;



Dia::Dia(){
    horari.clear();
}

void Dia::definirLimit(const FranjaHoraria & f){
    this->limit = f;
}


void Dia::definirDescans(const FranjaHoraria & f){
    this->desc = f;
}


void Dia::afegir(const Classe & cl){
    horari.insert(cl);
    FranjaHoraria f = cl.franjaHoraria();
    if ( cl.obligatoria() and FranjaHoraria::hiHaSolapament(f, desc)){
        hist_desc.push_back({cl, desc});
        ajustarDescans(f);
    }
    
}


void Dia::ajustarDescans(const FranjaHoraria & f){
    pair<int, int> temps = tempsNecessaris(f);
    desc.sumar(temps.first, temps.second);

}

void Dia::esborrar(const Classe & cl){
    set<Classe> :: iterator it = horari.find(cl);

    if (it == horari.end()){
        cerr << "No s'ha trobat la classe: "<<cl.obtenirNom()<<endl;
        throw("No s'ha trobat la classe");
    }else{
        horari.erase(it);
        if (not hist_desc.empty() and hist_desc.back().first == cl){
            desc = hist_desc.back().second;
            hist_desc.pop_back();
        }
    }
}


bool Dia::pertany(const Classe & cl, const set<string> & res){

    set<string>::const_iterator it = res.find(cl.obtenirNom());

    return it != res.end();
}


bool Dia::impossibleMoureDescans(const FranjaHoraria & f)const{
    return desc.inicial() >= f.inicial() and desc.final() <= f.final();
}

pair<int, int> Dia::tempsNecessaris(const FranjaHoraria & f)const{
    if (not FranjaHoraria::hiHaSolapament(desc, f)){
        cerr << "No hi ha solapament";
        throw ("No hi ha solapament");
    }

    Hora inici_f = f.inicial();
    Hora final_f = f.final();

    Hora inici_des = desc.inicial();
    Hora final_des = desc.final();

    if (impossibleMoureDescans(f)){
        // cas 5)
        cerr << "No es pot modificar de cap manera el descans";
        throw ("No es pot modificar el descans");
    }

    int temps_sup, temps_inf;

     if (inici_f > inici_des and final_f < final_des){
        // cas 6)

        
        int temps_sup_c = inici_f.resta(inici_des) + f.duracio();
        int temps_inf_c = final_des.resta(final_f) + f.duracio();
        

        if (desc.esPotSumar(temps_sup_c, 0)){
            temps_sup = temps_sup_c;
            temps_inf = 0;
        }else if (desc.esPotSumar(0, -temps_inf_c)){
            temps_sup = 0;
            temps_inf = -temps_inf_c;
        }else{
            cerr << "No es pot sumar"<<endl;
            throw ("No es pot sumar");
        }
     }else{

            int temps = desc.tempsSolapat(f);
            if (f < desc){
                // cas 3)
                temps_sup = temps;
                temps_inf = 0;
            }else{
                // cas 4)
                temps_sup = 0;
                temps_inf = -temps;
            }

     }
     return {temps_sup, temps_inf};
        

}


bool Dia::compleixDescans(const FranjaHoraria & f)const{

    if (not FranjaHoraria::hiHaSolapament(desc, f)){
        // cas 1) i 2)
        return true;
    }


    if (impossibleMoureDescans(f)){
        // cas 5)
        return false;
    }

    pair<int, int> temps = tempsNecessaris(f);
    return desc.esPotSumar(temps.first, temps.second);
}



bool Dia::foraLimit(const FranjaHoraria & f)const{
    return f.inicial() < limit.inicial() or f.final() > limit.final();
}

bool Dia::esPotAfegir(const Classe & cl, const set<string> & res)const{

    bool solapat = false;
    set<Classe> :: const_iterator it = horari.begin();

    FranjaHoraria f = cl.franjaHoraria();

    if (cl.obligatoria() and  (foraLimit(f) or not compleixDescans(f))){ 
        return false;
    }
    

    if (it != horari.end()){

        while (it != horari.end() and not solapat ){ // Mentres no arribi al final, mentres no trobi, i no sigui major. 

            solapat =  it->obligatoria() and cl.obligatoria() and Classe::hiHaSolapament(*it, cl) and not pertany(*it, res);
            it++;
        }
    }
    return not solapat;
}


void Dia::mostrarDescans()const{
    cout << desc;
}


