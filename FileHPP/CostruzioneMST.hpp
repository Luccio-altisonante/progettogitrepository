#ifndef COSTRUZIONEMST_HPP
#define COSTRUZIONEMST_HPP

#include <iostream>
#include <vector>

#include "ComponentiConnesse.hpp"
#include "GestioneFrequenze.hpp"

using namespace std;

vector<ArcoPesato> archiCCM;
//conterrà tutti gli archi appartenenti alla componente connessa maggiore


//questa funzione mi dice se un nodo appartiene alla componente connessa maggiore o meno
//(in questo modulo il nodo sarà un nodo di un arco pesato)
bool appartieneComponenteMaggiore(int nodo)
{
    for (int i = 0; i < componentemaggiore.size(); i++)
    {
        if (componentemaggiore[i] == nodo)
        {
            return true;
        }
    }

    return false;
}



void selezionaArchiCCM()
{
    for (int i = 0; i < archipesati.size(); i++)
    {
        if (appartieneComponenteMaggiore(archipesati[i].nodo1))
        {
            archiCCM.push_back(archipesati[i]);
            //se il primo nodo di un arco appartiene alla componente connessa maggiore,
            //aggiungo l'arco al vettore di tutti gli archi della CCM, archiCCM.
            //(per definizione di componente connessa basta sapere se il primo nodo ci stia o meno,
            // e ugualmente si comporterà il secondo)  
        }
    }
}

void stampaArchiCCM()
{
    cout << endl;
    cout << "Archi appartenenti alla componente connessa maggiore:" << endl;
    cout << endl;

    for (int i = 0; i < archiCCM.size(); i++)
    {
        cout << "(" << archiCCM[i].nodo1 << "," << archiCCM[i].nodo2; cout << ")";
        cout << " con peso = " << archiCCM[i].peso << endl;
    }
}

#endif