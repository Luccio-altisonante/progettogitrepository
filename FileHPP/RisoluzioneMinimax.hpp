#ifndef RISOLUZIONEMINIMAX_HPP
#define RISOLUZIONEMINIMAX_HPP

#include <iostream>
#include <vector>

#include "CostruzioneMST.hpp"

using namespace std;

vector<vector<pair<int, int>>> grafoadjMST;
//grafo del MST rappresentato tramite liste di adiacenza, in ogni coppia il primo elemento rappresenta
//l'indice del nodo vicino, il secondo elemento rappresenta il peso dell'arco.

vector<bool> visitatoMST;
//visitatoMST[i] indica se il nodo di indice i è già stato visitato dalla DFS.



void costruisciGrafoMST()
{
    grafoadjMST.resize(grafoadj.size());
    visitatoMST.resize(grafoadjMST.size());

    for (int i = 0; i < archiMST.size(); i++)
    {
        int indice1 = archiMST[i].indice1;
        int indice2 = archiMST[i].indice2;
        int peso = archiMST[i].peso;

        grafoadjMST[indice1].push_back({indice2,peso});
        //aggiunge indice2 ai vicini di indice1, con peso = peso.

        grafoadjMST[indice2].push_back({indice1,peso});
        //aggiunge nodo1 ai vicini di nodo2, perché il grafo è non orientato, sempre con peso = peso.
        //Non è necessario controllare eventuali duplicati perché archiMST contiene già gli archi 
        //del Minimum Spanning Tree, quindi ogni arco compare una sola volta.
    }
}


void stampaGrafoMST()
{
    for (int i = 0; i < grafoadjMST.size(); i++)
    {
        if (grafoadjMST[i].size() > 0)
        { // se il nodo ha almeno un vicino, lo stampo.
            cout << "Vicini nodo " << tabella.cercaNodoReale(i) << ": ";

            for (int j = 0; j < grafoadjMST[i].size(); j++)
            {
                cout << tabella.cercaNodoReale(grafoadjMST[i][j].first) << " con peso ";
                cout << grafoadjMST[i][j].second << "; ";
            }

            cout << endl;
        }
    }
}


int DFSminimax(int nodoattuale, int nodofinale, int maxpesoattuale)
{
    visitatoMST[nodoattuale] = true;
    //segno il nodo attuale come già visitato

    if (nodoattuale == nodofinale)
    {
        return maxpesoattuale;
        // se ho raggiunto il nodo finale, vuol dire che il cammino era giusto,
        // quindi restituisco il massimo peso incontrato lungo quel cammino.
    }
    else
    {

        for (int i = 0; i < grafoadjMST[nodoattuale].size(); i++)
        {
            int vicino = grafoadjMST[nodoattuale][i].first;
            int pesoVicino = grafoadjMST[nodoattuale][i].second;

            if (visitatoMST[vicino] == false)
            {
                int nuovoMassimo;

                if (pesoVicino > maxpesoattuale)
                {
                    nuovoMassimo = pesoVicino;
                }
                else
                {
                    nuovoMassimo = maxpesoattuale;
                }
                //se incontro un nodo il cui arco con nodoattuale ha peso maggiore
                //aggiorno il valore del nuovoMassimo lungo questo cammino con il peso

                int risultato = DFSminimax(vicino, nodofinale, nuovoMassimo);
                //provo ricorsivamente a raggiungere il nodo finale partendo da questo vicino. 
                //La chiamata restituisce il massimo peso del cammino, se da questo vicino si riesce 
                //ad arrivare al nodo finale, oppure -1 se invece questo ramo porta a un vicolo cieco 
                //che non contiene il nodo finale.

                if (risultato != -1)
                {
                    return risultato;
                    //se il risultato è diverso da -1, allora il cammino giusto verso nodofinale è proprio questo,
                    //quindi posso restituire lo stesso valore del peso massimo alla chiamata precedente.
                }
            }
        }
        return -1;
        //se esco dal for, significa che ho provato tutti i vicini raggiungibili del nodo attuale 
        //e nessuno di essi porta al nodo finale. Quindi il cammino cercato non passa da questo ramo, 
        //e restituisco -1 per segnalare alla chiamata precedente che questo percorso è un vicolo cieco.
    }
}

int trovaMinimax(int nodoReale1, int nodoReale2)
{
    if (!tabella.ricerca(nodoReale1) || !tabella.ricerca(nodoReale2))
    {
        return -2;
    }
    //se un nodo non fa parte del dataset restituisco -2. Scelgo -2 e non -1 per distinguere la tipologia
    //di errore durante i test dal main

    int indice1 = tabella.cercaIndice(nodoReale1);
    int indice2 = tabella.cercaIndice(nodoReale2);
    //arrivano in input i nodi reali ma si lavora sugli indici corrispondenti

    for (int i = 0; i < visitatoMST.size(); i++)
    {
        visitatoMST[i] = false;
    }
    //Prima di una nuova DFS resetto sempre tutto il vettore ponendolo false, perché
    //ogni chiamata è indipendente dalla precedente.

    return DFSminimax(indice1, indice2, 0);
    //avvio la DFS dal nodo iniziale.
    //All'inizio il cammino non contiene ancora archi, quindi pongo maxpesoattuale = 0.
}

#endif