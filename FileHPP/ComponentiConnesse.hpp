#ifndef COMPONENTICONNESSE_HPP
#define COMPONENTICONNESSE_HPP

#include <iostream>
#include <vector>

#include "CostruzioneGrafo.hpp"

using namespace std;

vector<bool> visitato;
// vector per sapere quando avviare DFS

vector<int> componentemaggiore;
//conterrà i nodi della componente connessa più grande

void nuovaDFS(int indice, vector<int> &componentecorrente)
{
    visitato[indice] = true;
    //timbra il nodo come già visitato, in modo da non considerarlo più

    componentecorrente.push_back(indice);
    //aggiungo il nodo alla componente corrente

    for (int i = 0; i < grafoadj[indice].size(); i++)
    {
        int vicino = grafoadj[indice][i];

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
    visitato.resize(grafoadj.size());
    for (int i = 0; i < visitato.size(); i++)
    {
        visitato[i] = false;
    }
    //do la giusta dimensione al vettore visitato e lo inizializzo tutto a false

    for (int i = 0; i < grafoadj.size(); i++)
    {
        if (visitato[i] == false)
        {
            vector<int> componentecorrente;

            nuovaDFS(i, componentecorrente);
            //avvio la DFS dall'elemento i, se è già stato visitato passerà a uno dei suoi vicini
            //la DFS finisce quando trovo tutta la componente connessa

            if (componentecorrente.size() > componentemaggiore.size())
            {
                componentemaggiore = componentecorrente;
            }
            //se la nuova componente è maggiore della precedente la salvo, altrimenti la scarto.
            //Alla fine mi resterà la componente connessa maggiore.
        }
    }
}



void stampaComponenteMaggiore()
{
    cout << "Componente connessa maggiore:" << endl;

    for (int i = 0; i < componentemaggiore.size(); i++)
    {
        cout << tabella.cercaNodoReale(componentemaggiore[i]) << " ";
    }

    cout << endl;
}

#endif