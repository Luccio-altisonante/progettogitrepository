#ifndef COMPONENTICONNESSE_HPP
#define COMPONENTICONNESSE_HPP

#include <iostream>
#include <vector>

#include "CostruzioneGrafo.hpp"

using namespace std;

vector<bool> visitato(100, false);
//vector per sapere quando avviare DFS


vector<vector<int>> componenti;
//ogni elemento di componenti è una componente connessa

vector<int> componentemaggiore;
//conterrà i nodi della componente connessa più grande

void nuovaDFS(int nodo, vector<int> &componentecorrente)
{
    visitato[nodo] = true;
    //timbra il nodo come già visitato, in modo da non considerarlo più

    componentecorrente.push_back(nodo);
    //aggiungo il nodo alla componente corrente

    for (int i = 0; i < grafoadj[nodo].size(); i++)
    {
        int vicino = grafoadj[nodo][i];

        if (visitato[vicino] == false)
        {
            nuovaDFS(vicino, componentecorrente);
        }
        //per ogni vicino del nodo guardo se è già stato visitato, se si non faccio niente e vado avanti,
        //altrimenti ripeto il procedimento di inserimento e verifica vicini con questo nodo vicino

    }
}



void costruisciComponenti()
{
    for (int i = 0; i < grafoadj.size(); i++)
    {
        if (grafoadj[i].size() > 0 && visitato[i] == false)
        {
            //per ora la prima condizione è messa solo perché ho definito arbitrariamente un vettore
            //lungo 100, quindi ci potrebbero essere delle posizioni di questo vettore vuote, cioè
            //che non rappresentano nessun elemento del grafo, che hanno 0 vicini, e non voglio considerarle
            vector<int> componentecorrente;

            nuovaDFS(i, componentecorrente);
            //avvio la DFS dall'elemento i, se è già stato visitato passerà a uno dei suoi vicini
            //la DFS finisce quando trovo tutta la componente connessa

            componenti.push_back(componentecorrente);
            //aggiungo la componente al vettore di tutte le componenti
        }
    }
}

void stampaComponenti()
{
    for (int i = 0; i < componenti.size(); i++)
    {
        cout << "Componente " << i + 1 << ": ";

        for (int j = 0; j < componenti[i].size(); j++)
        {
            cout << componenti[i][j] << " ";
        }

        cout << endl;
    }
}





void trovaComponenteMaggiore()
{

    int indice = 0;

    for (int i = 1; i < componenti.size(); i++)
    {
        if (componenti[i].size() > componenti[indice].size())
        {
            indice = i;
        }
    }

    componentemaggiore = componenti[indice];
}

void stampaComponenteMaggiore()
{
    cout << "Componente connessa maggiore:" << endl;

    for (int i = 0; i < componentemaggiore.size(); i++)
    {
        cout << componentemaggiore[i] << " ";
    }

    cout << endl;
}

#endif