#ifndef COSTRUZIONEGRAFO_HPP
#define COSTRUZIONEGRAFO_HPP

#include <iostream>
#include <vector>

#include "LettoreDataset.hpp"
#include "IndicizzazioneHashTable.hpp"

using namespace std;

vector<pair<int, int>> archi;
//vettore contenente tutti gli archi

vector<vector<int>> grafoadj;
//grafo rappresentato tramite liste di adiacenza
//intanto metto 100 come numero indicativo,
//poi subentreeranno le hash table per i nodi grandi

HashTable tabella(50021);
//inizializzo la tabella ad una dimensione grande e prima, se servirà più spazio
//verranno eseguiti dei rehash

void costruisciArchi()
{
    // costruisce il vettore degli archi
    for (int i = 0; i < cammini.size(); i++)
    {
        for (int j = 0; j < cammini[i].size() - 1; j++)
        {
            int nodoReale1 = cammini[i][j];
            int nodoReale2 = cammini[i][j + 1];

            int indice1 = tabella.cercaIndice(nodoReale1);
            int indice2 = tabella.cercaIndice(nodoReale2);
            //converto i nodi reali negli indici corrispondenti

            pair<int, int> arco;

            arco.first = indice1;
            arco.second = indice2;

            archi.push_back(arco);
            // aggiunge l'arco al vettore di tutti gli archi
        }
    }
}

void stampaArchi()
{
    for (int i = 0; i < archi.size(); i++)
    {
        int nodoReale1 = tabella.cercaNodoReale(archi[i].first);
        int nodoReale2 = tabella.cercaNodoReale(archi[i].second);
        cout << "(" << nodoReale1 << ", " << nodoReale2 << ")" << endl;
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


void eliminaDuplicati(vector<int>& v)
{
    //anche se passerò in input un vettore contenente gli indici corrispondenti ai nodi reali,
    //li tratterò qui come se fossero nodi, solo per sfruttare la classe HashTable che ho già definito.
    //gli indici degli elementi di visitati non avranno alcuna funzione.
    int n = v.size();
    HashTable visitati(n);

    vector<int> senzaDuplicati;

    for (int i = 0; i < n; i++)
    {
        if (!visitati.ricerca(v[i]))
        {
            //se non è già presente inserisco l'elemento nella hash table e nel vettore senzaDuplicati 
            visitati.cercaIndice(v[i]);
            senzaDuplicati.push_back(v[i]);
        }
    }
    v = senzaDuplicati;
}

void costruisciGrafo()
{
    grafoadj.resize(tabella.numeroNodiDistinti());

    for (int i = 0; i < archi.size(); i++)
    {
        int indice1 = archi[i].first;
        int indice2 = archi[i].second;

        grafoadj[indice1].push_back(indice2);
        //aggiunge l'indice del secondo nodo ai vicini dell'indice del primo.

        grafoadj[indice2].push_back(indice1);
        //aggiunge l'indice del primo nodo ai vicini dell'indice del secondo,
        //perché il grafo è non orientato.
    }

    for (int i = 0; i < grafoadj.size(); i++)
    {
        eliminaDuplicati(grafoadj[i]);
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