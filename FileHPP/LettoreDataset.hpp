#ifndef LETTURADATASET_HPP
#define LETTURADATASET_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


vector<vector<int>> cammini; 
//variabile globale che conterrà tutti i cammini letti dal dataset


void leggiDataset(string nomeFile)
//prende in input il nome del file
{
    ifstream file(nomeFile);

    if(!file.is_open())
    {
        //controllo che il file sia stato aperto correttamente
        cout << "Errore nell'apertura del file" << endl;
        return;
    }

    string riga;
    //variabile che conterrà ogni riga letta dal file



    while(getline(file, riga))
    {
        //continuo finché riesco a leggere righe dal file
        stringstream ss(riga);
        //trasformo la riga in uno stream leggibile

        string primaparte;
        //contiene la prima parte della riga, che non serve al progetto, non verrà utilizzata

        string percorso;
        //contiene il cammino degli Autonomous Systems letto dal file in input

        ss >> primaparte;
        //leggo la prima parte della riga

        if (!(ss >> percorso))
        {
            continue;
            //se la riga è vuota passo alla riga successiva, così da non salvare un nodo 0 inesistente.
        }

        vector<int> cammino;
        //questo vettore rappresenta il cammino della riga corrente

        int nodo = 0;
        //variabile che userò per costruire ogni nodo del cammino

        for (char carattere : percorso)
        //scorro tutto il percorso considerando i caratteri
        {
            if (carattere == '|')
            {
                //ho terminato di leggere un nodo
                cammino.push_back(nodo);
                nodo = 0;
                //e resetto la variabile nodo per crearne uno nuovo
            }
            else
            {
                nodo = nodo * 10 + (carattere - '0');
                //Aggiorno il nodo aggiungendo cifra dopo cifra. Per fare questo sfrutto la
                //proprietà di consecutività del codice ASCII, per cui 'numero'-'0' restituisce un
                //intero di valore uguale proprio a numero 
            }
        }
        cammino.push_back(nodo);
        //inserisco anche l'ultimo nodo del cammino, che non è seguito dal carattere |

        if(cammino.size() > 0)
        {
            cammini.push_back(cammino);
            //se il cammino non è vuoto lo aggiungo ai cammini totali
        }
    }

    cout << "Dataset letto correttamente" << endl;
}

#endif