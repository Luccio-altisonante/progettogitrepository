#include <iostream>
#include "../FileHPP/LettoreDataset.hpp"
#include "../FileHPP/CostruzioneGrafo.hpp"
#include "../FileHPP/GestioneFrequenze.hpp"
#include "../FileHPP/ComponentiConnesse.hpp"

using namespace std;

int main()
{
    leggiDataset("FileInput/datasetprova.txt");

    cout << endl;
    cout << "Cammini letti dal file:" << endl;
    cout << endl;

    for (int i = 0; i < cammini.size(); i++)
    {
        for (int j = 0; j < cammini[i].size(); j++)
        {
            cout << cammini[i][j] << " ";
        }

        cout << endl;
    }
    
    //fin qui prova di LettoreDataset

    cout << endl;
    cout << "Archi costruiti:" << endl;
    cout << endl;

    costruisciArchi();

    stampaArchi();

    cout << endl;
    cout << "Grafo costruito:" << endl;
    cout << endl;

    costruisciGrafo();

    stampaGrafo();

    //fin qui prova di CostruzioneGrafo

    cout << endl;
    cout << "Archi pesati:" << endl;
    cout << endl;

    costruisciarchipesati();

    stampaarchipesati();
    //fin qui prova di GestioneFrequenze

    cout << endl;
    cout << "Componenti connesse:" << endl;
    cout << endl;

    costruisciComponenti();

    stampaComponenti();
    //fin qui prova di ComponentiConnesse

    return 0;
}