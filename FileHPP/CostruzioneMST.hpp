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


//MergeSort visto a lezione, con l'unica modifica che prende un vector<Arcopesato> invece di un vector<int>
void Fusione(vector<ArcoPesato> &a, int sx, int cx, int dx)
{
    int i = sx;
    int j = cx + 1;
    int k = 0;
    vector<ArcoPesato> b(dx - sx + 1);

    while ((i <= cx) && (j <= dx))
    {
        if (a[i].peso <= a[j].peso)
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }

        k++;
    }


    for ( ; i <= cx; i++, k++)
    {
        b[k] = a[i];
    }
    for ( ; j <= dx; j++, k++) 
    {
        b[k] = a[j];
    }



    for (i = sx; i <= dx; i++) 
    {
        a[i] = b[i - sx];
    }

}


void MergeSort(vector<ArcoPesato> &a, int sinistra, int destra) 
{
    if (sinistra < destra)
    {
        int centro = (sinistra + destra) / 2;
        MergeSort(a, sinistra, centro);
        MergeSort(a, centro + 1, destra);
        Fusione(a, sinistra, centro, destra);
    }
}


void ordinaArchiCCM()
{
        MergeSort(archiCCM, 0, archiCCM.size() - 1);
}

void stampaArchiCCMordinati()
{
    cout << endl;
    cout << "Archi della componente connessa maggiore ordinati:" << endl;
    cout << endl;

    for (int i = 0; i < archiCCM.size(); i++)
    {
        cout << "(" << archiCCM[i].nodo1 << "," << archiCCM[i].nodo2 << ")";
        cout << " con peso = " << archiCCM[i].peso << endl;
    }
}

#endif