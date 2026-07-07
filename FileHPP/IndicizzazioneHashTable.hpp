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
};

#endif