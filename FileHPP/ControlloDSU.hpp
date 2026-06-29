#ifndef CONTROLLODSU_HPP
#define CONTROLLODSU_HPP

#include <iostream>
#include <vector>

#include "ComponentiConnesse.hpp"

using namespace std;

struct NodoDSU
{
    int nodo;
    int padre;
};
//è la struct che mi permette di fare effettivamente la DSU:
//per ogni nodo memorizzo chi è il padre, se il padre è uguale al nodo, 
//allora sarà quello il rappresentante del suo gruppo

vector<NodoDSU> nodiDSU;
//contiene tutti i nodi della componente connessa maggiore, assieme ai rispettivi padri

void inizializzaDSU()
{
    for (int i = 0; i < componentemaggiore.size(); i++)
    {
        NodoDSU nuovonodoDSU;

        nuovonodoDSU.nodo = componentemaggiore[i];
        nuovonodoDSU.padre = componentemaggiore[i];
        //all'inizio sono tutti nodi singoli, quindi ognuno è il proprio rappresentante

        nodiDSU.push_back(nuovonodoDSU);
    }
}




int trovaPosizioneNodo(int nodo)
{
    //il nodo i non sarà per forza nella posizione i (o i-1) del vettore nodiDSU,
    //potrebbe essere ovunque, e dato che mi serve sapere la posizione uso una funzione che la trovi
    for (int i = 0; i < nodiDSU.size(); i++)
    {
        if (nodiDSU[i].nodo == nodo)
        {
            return i;
        }
    }
    return -1;

}



int trovaRappresentante(int nodo) 
{
    int indice = trovaPosizioneNodo(nodo);

    if (nodiDSU[indice].padre == nodo)
    {
        return nodo;
    }
    //se il padre di un certo nodo è il nodo stesso, dunque allora è lui il rappresentante,
    //quindi,chiamata la funzione trovaRappresentante, posso fare return nodo 
    else 
    {
        return trovaRappresentante(nodiDSU[indice].padre);
        //se il nodo non è il rappresentante, allora guardo se lo è suo padre, e così via,
        //il rappresentante che trovo sarà il rappresentante del mio nodo di partenza 
        //(e anche degli altri della catena)
    }

}




void unisci(int nodo1, int nodo2)
{
    int rappresentante1 = trovaRappresentante(nodo1);
    int rappresentante2 = trovaRappresentante(nodo2);

    //se due nodi hanno lo stesso rappresentante vuol dire che appartengono già allo stesso insieme,
    //quindi non devo fare niente

    if (rappresentante1 != rappresentante2)
    {
        int indice = trovaPosizioneNodo(rappresentante2);
        nodiDSU[indice].padre = rappresentante1;
        //se i due nodi hanno due rappresentanti diversi, allora devo creare la congiunzione fra i due insiemi,
        //imponendo che il padre del rappresentante2 diventi rappresentante1, e non più sè stesso.

        // si cambia il padre di rappresentante2 e non di nodo2 perché così tutti gli elementi che avevano
        // come rappresentante rappresentante2, quindi che appartenevano al secondo insieme, adesso avranno
        // rappresentante1 come rappresentante, e faranno tutti parte del primo insieme.
        // altrimenti solo nodo2 ed i suoi figli si sarebbero spostati nel primo insieme,
        // lasciando tutti gli altri nodi dell secondo insieme lì dentro (anche se questo non deve esistere più)
    }
}




void stampaDSU()
{
    cout << endl;
    cout << "Esito DSU:" << endl;
    cout << endl;

    for (int i = 0; i < nodiDSU.size(); i++)
    {
        cout << "Nodo: " << nodiDSU[i].nodo;
        cout << ",";
        cout << " Padre: " << nodiDSU[i].padre << endl;
    }
}

#endif