#ifndef GESTIONEFREQUENZE_HPP
#define GESTIONEFREQUENZE_HPP

#include <iostream>
#include <vector>

#include "CostruzioneGrafo.hpp"

using namespace std;

struct ArcoPesato
{
    int nodo1;
    int nodo2;
    int peso;
};


vector<ArcoPesato> archipesati;
//vector contenente tutti gli archi pesati


int cercaArcoPesato(int nodo1, int nodo2)
{ //cerco se tra gli archi pesati è già presente quello di estremi nodo1 e nodo2
    for(auto i=0; i<archipesati.size(); i++) 
    {
        if ((archipesati[i].nodo1 == nodo1 && archipesati[i].nodo2 == nodo2) ||
            (archipesati[i].nodo1 == nodo2 && archipesati[i].nodo2 == nodo1)) 
            //cerco se (nodo1,nodo2) o (nodo2,nodo1) sono già presenti in ArchiPesati, 
            //in tal caso returno la loro posizione, per poterne poi modificare il peso
            { 
                return i;
            }
    }
    return -1;
}




void costruisciarchipesati() 
{
    for (auto i = 0; i < archi.size(); i++)
    {
        int nodo1 = archi[i].first;
        int nodo2 = archi[i].second;

        int posizione = cercaArcoPesato(nodo1, nodo2);

        if (posizione != -1)
        {
            archipesati[posizione].peso++;
        }

        else
        {
            ArcoPesato nuovoarco;

            nuovoarco.nodo1 = nodo1;
            nuovoarco.nodo2 = nodo2;
            nuovoarco.peso = 1;

            archipesati.push_back(nuovoarco);
        }
    }  
}

void stampaarchipesati()
{
    for (int i = 0; i < archipesati.size(); i++)
    {
        cout << "(" << archipesati[i].nodo1 << ", " << archipesati[i].nodo2 << ") ";
        cout << "peso = " << archipesati[i].peso << endl;
    }
}

#endif