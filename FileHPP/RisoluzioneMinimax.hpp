#ifndef RISOLUZIONEMINIMAX_HPP
#define RISOLUZIONEMINIMAX_HPP

#include <iostream>
#include <vector>

#include "CostruzioneMST.hpp"

using namespace std;

vector<vector<pair<int,int>>> grafoadjMST(100);
//sarà il grafo del MST rappresentato tramite liste di adiacenza. 
//un vettore di grafoadjMST conterrà delle coppie in cui il primo elemento rappresenta il nodo, il secondo il peso

vector<bool> visitatoMST(100, false);


bool ricercaMST(const vector<pair<int,int>> &lista, int x)
{
    // controlla se x è già presente nella lista
    for (int i = 0; i < lista.size(); i++)
    {
        if (lista[i].first == x)
        {
            return true;
        }
    }

    return false;
}


void costruisciGrafoMST()
{
    for (int i = 0; i < archiMST.size(); i++)
    {
        int nodo1 = archiMST[i].nodo1;
        int nodo2 = archiMST[i].nodo2;
        int peso = archiMST[i].peso;

        if (!ricercaMST(grafoadjMST[nodo1], nodo2))
        {
            
            grafoadjMST[nodo1].push_back({nodo2,peso});
        }
        // se non è già presente, aggiunge nodo2 ai vicini di nodo1, con peso = peso.

        if (!ricercaMST(grafoadjMST[nodo2], nodo1))
        {
            grafoadjMST[nodo2].push_back({nodo1,peso});
        }
        // se non è già presente, aggiunge nodo1 ai vicini di nodo2,
        // perché il grafo è non orientato, sempre con peso = peso.
    }
}


void stampaGrafoMST()
{
    for (int i = 0; i < grafoadjMST.size(); i++)
    {
        if (grafoadjMST[i].size() > 0)
        { // se il nodo ha almeno un vicino, lo stampo.
            cout << "Vicini nodo " << i << ": ";

            for (int j = 0; j < grafoadjMST[i].size(); j++)
            {
                cout << grafoadjMST[i][j].first << " con peso "; 
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

int trovaMinimax(int a, int b)
{
    for (int i = 0; i < visitatoMST.size(); i++)
    {
        visitatoMST[i] = false;
    }
    // prima di iniziare una nuova DFS, azzero il vettore dei visitati

    return DFSminimax(a, b, 0);
    // avvio la DFS dal nodo iniziale.
    // All'inizio il cammino non contiene ancora archi, quindi pongo
    // maxpesoattuale = 0.
}

#endif