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



void nuovaDFS(int nodo, vector<int> &componentecorrente)
{
    visitato[nodo] = true;

    componentecorrente.push_back(nodo);

    for (int i = 0; i < grafoadj[nodo].size(); i++)
    {
        int vicino = grafoadj[nodo][i];

        if (visitato[vicino] == false)
        {
            nuovaDFS(vicino, componentecorrente);
        }
    }
}

void costruisciComponenti()
{
    for (int i = 0; i < grafoadj.size(); i++)
    {
        if (grafoadj[i].size() > 0 && visitato[i] == false)
        {
            vector<int> componentecorrente;

            nuovaDFS(i, componentecorrente);

            componenti.push_back(componentecorrente);
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

#endif