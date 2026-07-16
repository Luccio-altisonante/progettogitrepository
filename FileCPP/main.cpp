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
    //scrivere g++ FileCPP/main.cpp -o nomedesiderato nel terminale per avviare. ./nomedesiderato per iniziare. 
    string nomeFile;

    cout << "Inserisci il nome del file presente nella cartella FileInput: ";
    cin >> nomeFile;

    leggiDataset("FileInput/" + nomeFile);

    if (cammini.empty())
    //Se il file non è stato letto potrebbe essere colpa del nome digitato male
    {
        cout << endl;
        cout << "Controllare il nome del file." << endl;
        return 0;
    }

    srand(static_cast<unsigned>(time(nullptr))); // seme iniziale per rand()

    costruisciArchi();
    
    costruisciGrafo();

    costruisciarchipesati();

    costruisciComponenti();

    selezionaArchiCCM();

    ordinaArchiCCM();

    costruisciMST();

    costruisciGrafoMST();
    
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

    //ora prendo l'input dall'utente.
    bool valido = true;
    while (valido)
    {
        int nodo1;
        int nodo2;

        cout << "Inserisci due nodi (-1 -1 per terminare): ";
        cin >> nodo1 >> nodo2;

        if (nodo1 == -1 && nodo2 == -1)
        {
            valido = false;
        }
        if ((!tabella.ricerca(nodo1)) || (!tabella.ricerca(nodo2)))
        {
            cout << "Errore: almeno uno dei due nodi non esiste." << endl;
            cout << endl;
            continue;
        }
        int minimax = trovaMinimax(nodo1, nodo2);

        if (minimax == -1)
        {
            cout << "Errore: almeno uno dei due nodi non appartiene alla componente connessa maggiore." << endl;
        }
        else
        {
            cout << "Valore minimax: " << minimax << endl;
        }

        cout << endl;
    }
}