#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    const int CAPACITY = 50;
    int numbers[CAPACITY];
    int size = 0;
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open("inFile.dat");
    if (!inputFile)
    {
        cout << "can't open" << endl;
        cout << "stop program";
        return 0;
    }
    while (inputFile >> numbers[size] && size <= 50)
    {
        size++;
    }
    inputFile.close();
    outputFile.open("outFile.dat");
    if (!outputFile)
    {
        cout << "can't open" << endl;
        return 0;
    }
    for (int i = size - 1; i >= 0; i--)
    {
        outputFile << numbers[i] << " ";
    }
    outputFile.close();
    return 0;
}

