#ifndef COSTRUZIONEMST_HPP
#define COSTRUZIONEMST_HPP

#include <iostream>
#include <vector>

#include "ControlloDSU.hpp"
#include "ComponentiConnesse.hpp"
#include "GestioneFrequenze.hpp"

using namespace std;

vector<ArcoPesatoIndicizzato> archiCCM;
//conterrà tutti gli archi appartenenti alla componente connessa maggiore

vector<ArcoPesatoIndicizzato> archiMST;
//conterrà tutti gli archi di archiCCM che faranno parte del MST

vector<bool> appartieneCCM;
//appartieneCCM[i] vale true se il nodo di indice i appartiene alla componente connessa maggiore, false altrimenti.


void costruisciVettoreCCM()
{
    appartieneCCM.resize(grafoadj.size());
    for (int i = 0; i < grafoadj.size(); i++)
    {
        appartieneCCM[i] = false;
    }

    for (int i = 0; i < componentemaggiore.size(); i++)
    {
        appartieneCCM[componentemaggiore[i]] = true;
    }
    //componentemaggiore contiene la lista degli indici dei nodi appartenenti alla componente connessa maggiore.
    //Nel vettore appartieneCCM, la posizione i del vettore corrisponde al nodo di indice i.
    //Per questo, leggendo gli indici contenuti in componentemaggiore, è sufficiente porre a true la posizione 
    //corrispondente di appartieneCCM,
}



void selezionaArchiCCM()
{
    costruisciVettoreCCM();

    for (int i = 0; i < archipesati.size(); i++)
    {
        if (appartieneCCM[archipesati[i].indice1])
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
    for (int i = 0; i < archiCCM.size(); i++)
    {
        cout << "(" << tabella.cercaNodoReale(archiCCM[i].indice1) << ",";
        cout << tabella.cercaNodoReale(archiCCM[i].indice2) << ")";
        cout << " con peso = " << archiCCM[i].peso << endl;
    }
}


//MergeSort visto a lezione, con l'unica modifica che prende un vector<Arcopesato> invece di un vector<int>
void Fusione(vector<ArcoPesatoIndicizzato> &a, int sx, int cx, int dx)
{
    int i = sx;
    int j = cx + 1;
    int k = 0;
    vector<ArcoPesatoIndicizzato> b(dx - sx + 1);

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


void MergeSort(vector<ArcoPesatoIndicizzato> &a, int sinistra, int destra) 
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
        cout << "(" << tabella.cercaNodoReale(archiCCM[i].indice1) << ",";
        cout << tabella.cercaNodoReale(archiCCM[i].indice2) << ")";
        cout << " con peso = " << archiCCM[i].peso << endl;
    }
}



void costruisciMST() 
{
    inizializzaDSU();

    for (int i = 0; i < archiCCM.size(); i++)
    {
        int indice1 = archiCCM[i].indice1;
        int indice2 = archiCCM[i].indice2;

        int rappresentante1 = trovaRappresentante(indice1);
        int rappresentante2 = trovaRappresentante(indice2);

        if (rappresentante1 != rappresentante2)
        {
            archiMST.push_back(archiCCM[i]);

            unisci(indice1, indice2);
        }
    }
}


void stampaArchiMST()
{
    for(int i = 0; i < archiMST.size(); i++)
    {
        cout << "(" << tabella.cercaNodoReale(archiMST[i].indice1) << ", ";
        cout << tabella.cercaNodoReale(archiMST[i].indice2) << ")";
        cout << " con peso = " << archiMST[i].peso << endl;
    }
}



#endif