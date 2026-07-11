#ifndef CONTROLLODSU_HPP
#define CONTROLLODSU_HPP

#include <iostream>
#include <vector>

#include "ComponentiConnesse.hpp"

using namespace std;


vector<int> padri;
//grazie all'indicizzazione fatta nei moduli precedenti,
//padri[i] rappresenta il padre del nodo di indice i.
//Se padri[i] == i, allora il nodo i è il rappresentante del proprio insieme.


void inizializzaDSU()
{
    padri.clear();
    //necessario perché altrimenti se la funzione viene chiamata più volte
    //(come adesso, prima nel main direttamente, poi il main chiama costruisciMST che chiama inizializzaDSU)
    //non crea un vettore nuovo ma continua ad aggiungere gli elementi nuovi al vettore vecchio

    padri.resize(grafoadj.size());
    //Si inizializzano tutti i nodi del grafo e non solo quelli della componente maggiore perché questo
    //semplifica il codice e permette di lavorare sempre sugli stessi indici, rendendo inutile la funzione
    //trovaPosizioneNodo, e questo non aumenta la complessità finale, perché CostruzioneMST chiamerà le 
    //funzioni di questo modulo solo sugli archi della componente connessa maggiore.

    for (int i = 0; i < grafoadj.size(); i++)
    {
        padri[i] = i;
        //all'inizio sono tutti nodi singoli, quindi ognuno è il proprio rappresentante
        //non è più necessario memorizzare esplicitamente il nodo stesso,
        //perché la posizione i del vettore rappresenta già il nodo di indice i.
    }
}

// Grazie all'indicizzazione introdotta nel modulo IndicizzazioneHashTable, il nodo di indice i corrisponde
// direttamente alla posizione i del vettore padri. Non è quindi più necessaria la funzione per trovare la posizione
// del nodo all'interno del vettore che nella versione precedente effettuava una ricerca lineare.

int trovaRappresentante(int indiceNodo) 
{
    if (padri[indiceNodo] == indiceNodo)
    {
        return indiceNodo;
    }
    //se il padre di un certo nodo è il nodo stesso, dunque allora è lui il rappresentante,
    //quindi,chiamata la funzione trovaRappresentante, posso fare return nodo 
    else 
    {
        return trovaRappresentante(padri[indiceNodo]);
        //se il nodo non è il rappresentante, allora guardo se lo è suo padre, e così via,
        //il rappresentante che trovo sarà il rappresentante del mio nodo di partenza 
        //(e anche degli altri della catena)
    }

}


void unisci(int indiceNodo1, int indiceNodo2)
{
    int rappresentante1 = trovaRappresentante(indiceNodo1);
    int rappresentante2 = trovaRappresentante(indiceNodo2);

    //se due nodi hanno lo stesso rappresentante vuol dire che appartengono già allo stesso insieme,
    //quindi non devo fare niente

    if (rappresentante1 != rappresentante2)
    {
        padri[rappresentante2] = rappresentante1;
        //se i due nodi hanno due rappresentanti diversi, allora si deve creare la congiunzione fra i due insiemi,
        //imponendo che il padre del rappresentante2 diventi rappresentante1, e non più sè stesso.

        //si cambia il padre di rappresentante2 e non di nodo2 perché così tutti gli elementi che avevano
        //come rappresentante rappresentante2, quindi che appartenevano al secondo insieme, adesso avranno
        //rappresentante1 come rappresentante, e faranno tutti parte del primo insieme.
        //altrimenti solo nodo2 ed i suoi figli si sarebbero spostati nel primo insieme,
        //lasciando tutti gli altri nodi del secondo insieme lì dentro (anche se questo non deve esistere più)
    }
}


void stampaDSU()
{
    cout << endl;
    cout << "Esito DSU:" << endl;
    cout << endl;

    for (int i = 0; i < padri.size(); i++)
    {
        cout << "Nodo: " << tabella.cercaNodoReale(i);
        cout << ",";
        cout << " Padre: " << tabella.cercaNodoReale(padri[i]) << endl;
    }
}

#endif