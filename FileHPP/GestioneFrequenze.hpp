#ifndef GESTIONEFREQUENZE_HPP
#define GESTIONEFREQUENZE_HPP

#include <iostream>
#include <vector>

#include "CostruzioneGrafo.hpp"

using namespace std;

struct ArcoPesatoIndicizzato
{
    int indice1; //indice corrispondente al primo nodo
    int indice2; //indice corrispondente al secondo nodo
    int peso;
};


//ricalca la struttura della hash table per nodi, con le dovute modifiche
class HashUniversaleArchi
{
private:
    long long p;
    long long a;
    long long b;
    long long c;

public:
    HashUniversaleArchi(long long _p = 998244353)
    {
        p = _p;
        a = rand() % (p - 1) + 1;
        b = rand() % (p - 1) + 1;
        c = rand() % p;
    }

    long long calcolaHashArco(long long indice1, long long indice2)
    {
        return (a * indice1 + b * indice2 + c) % p;
    }

    void rehash()
    {
        a = rand() % (p - 1) + 1;
        b = rand() % (p - 1) + 1;
        c = rand() % p;
    }
};

class HashTableArchiPesati
{
private:
    int m;
    vector<vector<ArcoPesatoIndicizzato>> tabellaArchi;
    HashUniversaleArchi hasher;

    int hash(int indice1, int indice2)
    {
        int h = hasher.calcolaHashArco(indice1, indice2) % m;

        return h;
    }


    void rehash(int nuovoM)
    {
        hasher.rehash();
        m = nuovoM;

        vector<vector<ArcoPesatoIndicizzato>> nuovaTabella(m);

        for (int i = 0; i < tabellaArchi.size(); i++)
        {
            for (int j = 0; j < tabellaArchi[i].size(); j++)
            {
                int indice1 = tabellaArchi[i][j].indice1;
                int indice2 = tabellaArchi[i][j].indice2;

                int h = hash(indice1, indice2);
                nuovaTabella[h].push_back(tabellaArchi[i][j]);
            }
        }

        tabellaArchi = nuovaTabella;
    }

public:
    HashTableArchiPesati(int size) : m(size), tabellaArchi(size), hasher() {}


    //se l'arco non esite già lo inserisco, altrimenti aumento il peso dell'arco già presente di 1
    void inserisciArco(int indice1, int indice2)
    {
        //dato che il grafo è non orientato, uso sempre l'arco con estremi ordinati
        if (indice1 > indice2)
        {
            swap(indice1, indice2);
        }

        int h = hash(indice1, indice2);

        for (int i = 0; i < tabellaArchi[h].size(); i++)
        {
            if (tabellaArchi[h][i].indice1 == indice1 && tabellaArchi[h][i].indice2 == indice2)
            {
                tabellaArchi[h][i].peso++;
                return;
            }
        }

        ArcoPesatoIndicizzato nuovoArco;
        nuovoArco.indice1 = indice1;
        nuovoArco.indice2 = indice2;
        nuovoArco.peso = 1;

        tabellaArchi[h].push_back(nuovoArco);

        if (tabellaArchi[h].size() > 5)
        {
            rehash(2 * m + 1);
        }
    }


    //per avere il vettore finale degli archi pesati, che serve in CostruzioneMST
    vector<ArcoPesatoIndicizzato> estraiArchiPesati()
    {
        vector<ArcoPesatoIndicizzato> vettorefinale;

        for (int i = 0; i < tabellaArchi.size(); i++)
        {
            for (int j = 0; j < tabellaArchi[i].size(); j++)
            {
                vettorefinale.push_back(tabellaArchi[i][j]);
            }
        }

        return vettorefinale;
    }



    void stampaTabellaArchiPesati()
    {
        for (int i = 0; i < tabellaArchi.size(); i++)
        {
            cout << "Scatola " << i << ": ";

            if (tabellaArchi[i].size() == 0)
            {
                cout << "vuota";
            }
            else
            {
                for (int j = 0; j < tabellaArchi[i].size(); j++)
                {
                    int indice1 = tabellaArchi[i][j].indice1;
                    int indice2 = tabellaArchi[i][j].indice2;

                    cout << "[" << tabella.cercaNodoReale(indice1)
                         << "," << tabella.cercaNodoReale(indice2)
                         << " con peso = " << tabellaArchi[i][j].peso
                         << "] ";
                }
            }

            cout << endl;
        }
    }
};

vector<ArcoPesatoIndicizzato> archipesati;
//vector contenente tutti gli archi pesati

HashTableArchiPesati tabellaArchi(3);
//per ora di dimensione piccola per il mio dataset e per testare il reash,
//poi diventerà di dimensione proporzionale a archi.size()

void costruisciarchipesati()
{
    for (int i = 0; i < archi.size(); i++)
    {
        int indice1 = archi[i].first;
        int indice2 = archi[i].second;

        tabellaArchi.inserisciArco(indice1, indice2);
    }

    archipesati = tabellaArchi.estraiArchiPesati();
}


void stampaarchipesati()
{
    cout << endl;
    cout << "Archi pesati: " << endl;
    cout << endl;
    for (int i = 0; i < archipesati.size(); i++)
    {
        int nodoReale1 = tabella.cercaNodoReale(archipesati[i].indice1);
        int nodoReale2 = tabella.cercaNodoReale(archipesati[i].indice2);

        if (nodoReale1 > nodoReale2)
        {
            int temp = nodoReale1;
            nodoReale1 = nodoReale2;
            nodoReale2 = temp;
        }
        cout << "(" << nodoReale1 << ", " << nodoReale2 << ") ";
        cout << "peso = " << archipesati[i].peso << endl;
    }
}


void stampaTabellaArchiPesati()
{
    tabellaArchi.stampaTabellaArchiPesati();
}

#endif