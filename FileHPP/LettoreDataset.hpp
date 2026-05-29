#ifndef LETTURADATASET_HPP
#define LETTURADATASET_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


vector<vector<int>> cammini; 
// variabile globale che conterrà tutti i cammini letti dal dataset


void leggiDataset(string nomeFile)
//prende in input il nome del file
{
    ifstream file(nomeFile);

    if(!file.is_open())
    {
        // Controllo che il file sia stato aperto correttamente
        cout << "Errore nell'apertura del file" << endl;
        return;
    }

    string riga;
    // Variabile che conterrà ogni riga letta dal file



    while(getline(file, riga))
    {
        // Continuo finché riesco a leggere righe dal file
        stringstream ss(riga);
        // Trasformo la riga in uno stream leggibile

        vector<int> cammino;
        // Questo vettore rappresenta il cammino della riga corrente

        int nodo;
        // In questa variabile salvo ogni nodo letto

        while(ss >> nodo)
        {
            // Finché riesco a leggere numeri dalla riga li assegno a nodo e li aggiungo al cammino
            cammino.push_back(nodo);
        }


        if(cammino.size() > 0)
        {
            // Se il cammino non è vuoto lo aggiungo ai cammini totali
            cammini.push_back(cammino);
        }
    }

    cout << "Dataset letto correttamente" << endl;
}

#endif