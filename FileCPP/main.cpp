#include <iostream>
#include "../FileHPP/LettoreDataset.hpp"

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

    return 0;
}