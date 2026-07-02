#include <iostream>
#include "../FileHPP/LettoreDataset.hpp"
#include "../FileHPP/CostruzioneGrafo.hpp"
#include "../FileHPP/GestioneFrequenze.hpp"
#include "../FileHPP/ComponentiConnesse.hpp"
#include "../FileHPP/ControlloDSU.hpp"
#include "../FileHPP/CostruzioneMST.hpp"

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

    

    costruisciComponenti();

    trovaComponenteMaggiore();

    
    cout << endl;
    stampaComponenteMaggiore();
    cout << endl;
    //fin qui prova di ComponentiConnesse




    cout << "Iniziale struttura DSU della componente maggiore: " << endl;

    inizializzaDSU();
    stampaDSU();
    

    for (int i=0; i < componentemaggiore.size() - 1; i++) 
    {
        unisci(componentemaggiore[i],componentemaggiore[i+1]);
        cout << endl << "Struttura DSU della componente maggiore dopo " << i+1 << " unioni:" << endl;
        stampaDSU();

    }
    //fin qui prova di ControlloDSU





    cout << endl;
    cout << "Archi della componente connessa maggiore:" << endl;
    cout << endl;

    selezionaArchiCCM();

    stampaArchiCCM();

    cout << endl;
    cout << "Archi della componente connessa maggiore dopo l'ordinamento:" << endl;
    cout << endl;

    ordinaArchiCCM();
    stampaArchiCCM();

    costruisciMST();

    cout << endl;
    cout << "Archi dell'MST:" << endl;
    cout << endl;

    stampaArchiMST();

    //fin qui prova di primo pezzo di CostruzioneMST

    return 0;
}