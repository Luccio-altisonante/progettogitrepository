#include <iostream>
#include <string>
#include "../FileHPP/LettoreDataset.hpp"
#include "../FileHPP/IndicizzazioneHashTable.hpp"
#include "../FileHPP/CostruzioneGrafo.hpp"
#include "../FileHPP/GestioneFrequenze.hpp"
#include "../FileHPP/ComponentiConnesse.hpp"
#include "../FileHPP/ControlloDSU.hpp"
#include "../FileHPP/CostruzioneMST.hpp"
#include "../FileHPP/RisoluzioneMinimax.hpp"


using namespace std;

int main()
{
    string nomeFile;

    cout << "Inserisci il nome del file presente nella cartella FileInput: ";
    cin >> nomeFile;

    leggiDataset("FileInput/" + nomeFile);

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

    srand(static_cast<unsigned>(time(nullptr))); // seme iniziale per rand()

    //HashTable tabellaNodi(5); 
    //per il dataset di prova, la dimensione iniziale è piccola per testare il rehashing 

    //for (int i = 0; i < cammini.size(); i++)
    //{
    //    for (int j = 0; j < cammini[i].size(); j++)
    //    {
    //        tabellaNodi.cercaIndice(cammini[i][j]);
    //    }
    //}
    //tabellaNodi.stampaParametri();
    //tabellaNodi.stampaHashTable();

    //fin qui prova di IndicizzazioneHashTable


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
    stampaTabellaArchiPesati();
    stampaarchipesati();
    //fin qui prova di GestioneFrequenze

    

    costruisciComponenti();

    cout << endl;
    stampaComponenteMaggiore();
    cout << endl;
    //fin qui prova di ComponentiConnesse




    //cout << "Iniziale struttura DSU della componente maggiore: " << endl;

    inizializzaDSU();
    //stampaDSU();
    

    //for (int i=0; i < componentemaggiore.size() - 1; i++) 
    //{
    //    unisci(componentemaggiore[i],componentemaggiore[i+1]);
    //    cout << endl << "Struttura DSU della componente maggiore dopo " << i+1 << " unioni:" << endl;
    //    stampaDSU();

    //}
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

    costruisciGrafoMST();
    cout << endl;
    cout << "Grafo del MST tramite liste di adiacenza: ";
    cout << endl;
    stampaGrafoMST();

    cout << endl;
    cout << "Esempi di alcuni percorsi minimax con nodi casuali del dataset:" << endl;
    cout << endl;

    int i = 0;

    while (i < 4)
    {
        int indice1 = rand() % tabella.numeroNodiDistinti();
        int indice2 = rand() % tabella.numeroNodiDistinti();

        int nodo1 = tabella.cercaNodoReale(indice1);
        int nodo2 = tabella.cercaNodoReale(indice2);

        int minimax = trovaMinimax(nodo1, nodo2);
        
        
        if ((minimax != -1) && (minimax != -2) && (minimax != 0))
        {
            cout << "Percorso minimax fra " << nodo1 << " e " << nodo2 << ": ";
            cout << minimax;
            cout << endl;
            i++;
        }
        
    }

    //fin qui prova di RisoluzioneMinimax

    return 0;
}