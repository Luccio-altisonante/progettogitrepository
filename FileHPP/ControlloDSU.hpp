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
vector<int> dimensione;
//dimensione[i] memorizza il numero di nodi presenti nell'albero
//che ha come radice (rappresentante) il nodo i. Ha senso e viene usato
//solo se il nodo i è effettivamente un rappresentante.

void inizializzaDSU()
{
    padri.clear();
    dimensione.clear();
    //necessario perché altrimenti se la funzione viene chiamata più volte non crea vettori nuovi ma 
    //continua ad aggiungere gli elementi vecchi.

    padri.resize(grafoadj.size());
    dimensione.resize(grafoadj.size());
    //Si inizializzano tutti i nodi del grafo e non solo quelli della componente maggiore perché questo
    //semplifica il codice e permette di lavorare sempre sugli stessi indici, rendendo inutile la funzione
    //trovaPosizioneNodo, e questo non aumenta la complessità finale, perché CostruzioneMST chiamerà le 
    //funzioni di questo modulo solo sugli archi della componente connessa maggiore.

    for (int i = 0; i < grafoadj.size(); i++)
    {
        padri[i] = i;
        //all'inizio sono tutti nodi singoli, quindi ognuno è il proprio rappresentante.

        dimensione[i] = 1;
        //all'inizio ogni insieme contiene solo il nodo stesso, quindi la dimensione è 1.

        //non è più necessario memorizzare esplicitamente il nodo stesso,
        //perché la posizione i del vettore rappresenta già il nodo di indice i.
    }
}

//Grazie all'indicizzazione introdotta nel modulo IndicizzazioneHashTable, il nodo di indice i corrisponde
//direttamente alla posizione i del vettore padri. Non è quindi più necessaria la funzione per trovare la posizione
//del nodo all'interno del vettore che nella versione precedente effettuava una ricerca lineare.

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
        padri[indiceNodo] = trovaRappresentante(padri[indiceNodo]);
        return padri[indiceNodo];
        //Risalgo ricorsivamente fino al rappresentante dell'insieme e durante il ritorno 
        //della ricorsione aggiorno direttamente il padre del nodo corrente con il rappresentante trovato.
        //In questo modo le future ricerche saranno molto più veloci, perché la catena dei padri 
        //viene progressivamente "schiacciata". Questo sarà utile soprattutto quando nel modulo
        //CostruzioneMST dovremmo chiamare tante volte questa funzione.
        //Questa strategia si chiama path compression.
    }

}


void unisci(int indiceNodo1, int indiceNodo2)
{
    int rappresentante1 = trovaRappresentante(indiceNodo1);
    int rappresentante2 = trovaRappresentante(indiceNodo2);

    // se due nodi hanno lo stesso rappresentante vuol dire che appartengono già allo stesso insieme,
    // quindi non devo fare niente.
    if (rappresentante1 != rappresentante2)
    {
        //Prima decidevo arbitrariamente di appendere il secondo albero sotto al primo, ma questo poteva
        //portare a problemi di altezza, adesso applico la union by size:
        //confronto la dimensione dei due alberi e appendo l'albero più piccolo sotto la radice 
        //dell'albero più grande.

        if (dimensione[rappresentante1] >= dimensione[rappresentante2])
        {
            //Se l'albero 1 è più grande o uguale all'albero 2:
            //Il rappresentante1 diventa il padre del rappresentante2
            padri[rappresentante2] = rappresentante1;

            dimensione[rappresentante1] += dimensione[rappresentante2];
            //La dimensione dell'albero 1 aumenta, inglobando tutti i nodi dell'albero 2
        }
        else
        {
            //Se l'albero 2 è strettamente più grande dell'albero 1:
            //Il rappresentante2 diventa il padre del rappresentante1
            padri[rappresentante1] = rappresentante2;

            dimensione[rappresentante2] += dimensione[rappresentante1];
            //La dimensione dell'albero 2 aumenta, inglobando tutti i nodi dell'albero 1
        }
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