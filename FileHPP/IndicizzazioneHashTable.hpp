#ifndef IndicizzazioneHashTable_HPP
#define IndicizzazioneHashTable_HPP

#include<iostream>
#include <vector>
#include <cstdlib>

using namespace std;


struct NodoConIndice
{
    int nodoReale;
    int indiceCorrisp;
};
//il primo elemento sarà il valore del nodo, il secondo l'indice corrispondente


class HashUniversale
{
private:
    long long p;
    long long a;
    long long b;

public:
    HashUniversale(long long _p = 998244353)
    {
        p = _p;

        a = rand() % (p - 1) + 1;
        b = rand() % p;
    }

    long long calcolaHash(long long x)
    {
        return (a * x + b) % p;
    }

    void rehash()
    {
        a = rand() % (p - 1) + 1;
        b = rand() % p;
    }

    void stampaParametri()
    {
        cout << "a = " << a << ", b = " << b << ", p = " << p << endl;
    }
};


class HashTable
{
private:
    int m;
    vector<vector<NodoConIndice>> tabella;
    vector<int> indiciToNodi;
    HashUniversale hasher;

    int hash(int nodo)
    {
        int h = hasher.calcolaHash(nodo) % m;

        if (h < 0)
        {
            h += m;
        }

        return h;
    }


    void rehash(int nuovoM)
    {
        hasher.rehash();
        
        m = nuovoM;
        vector<vector<NodoConIndice>> nuovaTabella(m);

        for (int i = 0; i < tabella.size(); i++)
        {
            for (int j = 0; j < tabella[i].size(); j++)
            {
                int h = hash(tabella[i][j].nodoReale);
                nuovaTabella[h].push_back(tabella[i][j]);
            }
        }
        tabella = nuovaTabella;
    }


    void inserisciNodo(int x)
    {    
        //la funzione viene chiamata da cercaIndice, do per scontato che il nodo non sia già stato inserito
        NodoConIndice nuovoNodo;
        nuovoNodo.nodoReale = x;
        nuovoNodo.indiceCorrisp = indiciToNodi.size();
        //assegno gli indici per ordine di arrivo:
        //quando arriva il primo nodo il vector ha dimensione 0 -> va in posizione 0;
        //quando arriva il secondo nuovo nodo il vector ha dimensione 1 -> va in posizion 1, e coì via.

        indiciToNodi.push_back(x);
        //così la posizione i del vettore corrisponde al nodo reale di indice i

        int h = hash(x);
        tabella[h].push_back(nuovoNodo);

        if (tabella[h].size() > 5)
        {
            rehash(2 * m + 1);
        }
    }

public:
    HashTable(int size) : m(size), tabella(size), hasher() {}

    int cercaIndice(int nodo)
    {
        int h = hash(nodo);

        for (int i = 0; i < tabella[h].size(); i++)
        {
            if (tabella[h][i].nodoReale == nodo)
            {
                return tabella[h][i].indiceCorrisp;
            }
        }

        inserisciNodo(nodo);
        return cercaIndice(nodo);
    }

    int cercaNodoReale(int indice)
    {
        return indiciToNodi[indice];
    }

    void stampaHashTable()
    {   
        cout << "Struttura finale della hash table:" << endl;
        cout << endl;

        for (int i = 0; i < tabella.size(); i++)
        {
            cout << "Scatola " << i << ": ";

            if (tabella[i].size() == 0)
            {
                cout << "vuota";
            }
            else
            {
                for (int j = 0; j < tabella[i].size(); j++)
                {
                    cout << "[nodoReale = " << tabella[i][j].nodoReale
                         << ", indiceCorrisp = " << tabella[i][j].indiceCorrisp << "] ";
                }
            }

            cout << endl;
        }
    }

    void stampaParametri()
    {
        hasher.stampaParametri();
    };


    //per il modulo CostruzioneGrafo ho bisogno di sapere quanti nodi distinti ci sono
    int numeroNodiDistinti()
    {
        return indiciToNodi.size();
        //ogni volta che aggiungo un nodo distinto aggiungo una posizione a indiciToNodi
    }
};

#endif