#ifndef COSTRUZIONEGRAFO_HPP
#define COSTRUZIONEGRAFO_HPP

#include <iostream>
#include <vector>
#include "LettoreDataset.hpp"

using namespace std;


vector<pair<int, int>> archi;
//vettore contenente tutti gli archi

vector<vector<int>> grafoadj(100);
//grafo rappresentato tramite liste di adiacenza
//intanto metto 100 come numero indicativo, 
//poi subentreeranno le hash table per i nodi grandi


void costruisciArchi() {
    //costruisce il vettore degli archi
    for(int i = 0; i < cammini.size(); i++) 
    {
        for(int j = 0; j < cammini[i].size() - 1; j++) 
        {
            int nodo1 = cammini[i][j];
            int nodo2 = cammini[i][j + 1];

            pair<int, int> arco;

            arco.first = nodo1;
            arco.second = nodo2;

            archi.push_back(arco);
            //aggiunge l'arco al vettore di tutti gli archi
        }
    }
}




void stampaArchi() {
    for(int i = 0; i < archi.size(); i++)
    {
        cout << "("<< archi[i].first<< ", "<< archi[i].second<< ")"<< endl;
    }
}




bool ricerca(const vector<int> &lista, int x) {
    //controlla se x è già presente nella lista
    for(int i = 0; i < lista.size(); i++)
    {
        if (lista[i] == x)
        {
            return true;
        }
    }

    return false;
}




void costruisciGrafo() {
    for(int i = 0; i < archi.size(); i++) 
    {
        int nodo1 = archi[i].first;
        int nodo2 = archi[i].second;

        
        if(!ricerca(grafoadj[nodo1], nodo2)) 
        {
            grafoadj[nodo1].push_back(nodo2);
        }
        //se non è già presente, aggiunge nodo2 ai vicini di nodo1.


        if (!ricerca(grafoadj[nodo2], nodo1))
        {
            grafoadj[nodo2].push_back(nodo1);
        }
        // se non è già presente, aggiunge nodo1 ai vicini di nodo2,
        //perché il grafo è non orientato.
    }
}




void stampaGrafo() {
    for (int i = 0; i < grafoadj.size(); i++)
    {
        if (grafoadj[i].size() > 0)
        { //se il nodo ha almeno un vicino, lo stampo.
            cout << "Vicini nodo " << i << ": ";

            for (int j = 0; j < grafoadj[i].size(); j++)
            {
                cout << grafoadj[i][j] << " ";
            }

            cout << endl;
        }
    }
}

#endif