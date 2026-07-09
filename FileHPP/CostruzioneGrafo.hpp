#ifndef COSTRUZIONEGRAFO_HPP
#define COSTRUZIONEGRAFO_HPP

#include <iostream>
#include <vector>

#include "LettoreDataset.hpp"
#include "IndicizzazioneHashTable.hpp"

using namespace std;

vector<pair<int, int>> archi;
// vettore contenente tutti gli archi

vector<vector<int>> grafoadj;
// grafo rappresentato tramite liste di adiacenza
// intanto metto 100 come numero indicativo,
// poi subentreeranno le hash table per i nodi grandi

HashTable tabella(5);

void costruisciArchi()
{
    // costruisce il vettore degli archi
    for (int i = 0; i < cammini.size(); i++)
    {
        for (int j = 0; j < cammini[i].size() - 1; j++)
        {
            int nodo1 = cammini[i][j];
            int nodo2 = cammini[i][j + 1];

            pair<int, int> arco;

            arco.first = nodo1;
            arco.second = nodo2;

            archi.push_back(arco);
            // aggiunge l'arco al vettore di tutti gli archi
        }
    }
}

void stampaArchi()
{
    for (int i = 0; i < archi.size(); i++)
    {
        cout << "(" << archi[i].first << ", " << archi[i].second << ")" << endl;
    }
}

bool ricerca(const vector<int> &lista, int x)
{
    // controlla se x è già presente nella lista
    for (int i = 0; i < lista.size(); i++)
    {
        if (lista[i] == x)
        {
            return true;
        }
    }

    return false;
}

//indicizzo prima i nodi, così grazie alla funzione numeroNodiDistinti, so quanto dovrà essere grande il vettore grafoadj
void indicizzaNodi()
{
    for (int i = 0; i < archi.size(); i++)
    {
        tabella.cercaIndice(archi[i].first);
        tabella.cercaIndice(archi[i].second);
    }
}


void costruisciGrafo()
{
    indicizzaNodi();
    grafoadj.resize(tabella.numeroNodiDistinti());

    for (int i = 0; i < archi.size(); i++)
    {
        int nodoReale1 = archi[i].first;
        int nodoReale2 = archi[i].second;

        //converto i nodi reali negli indici corrispondenti
        int indice1 = tabella.cercaIndice(nodoReale1);
        int indice2 = tabella.cercaIndice(nodoReale2);

        if (!ricerca(grafoadj[indice1], indice2))
        {
            grafoadj[indice1].push_back(indice2);
        }
        //se non è già presente, aggiunge l'indice del secondo nodo ai vicini dell'indice del primo.

        if (!ricerca(grafoadj[indice2], indice1))
        {
            grafoadj[indice2].push_back(indice1);
        }
        //se non è già presente, aggiunge l'indice del primo nodo ai vicini dell'indice del secondo,
        //perché il grafo è non orientato.
    }
}

void stampaGrafo()
{
    for (int i = 0; i < grafoadj.size(); i++)
    {
        cout << "Vicini nodo " << tabella.cercaNodoReale(i) << ": ";

        for (int j = 0; j < grafoadj[i].size(); j++)
        {
            cout << tabella.cercaNodoReale(grafoadj[i][j]) << " ";
        }

            cout << endl;      
    }
}

#endif