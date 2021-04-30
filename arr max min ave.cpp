#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int smallest = +100000000;
    int largest = -100000000;
    double average;
    int sum = 0;
    const int SIZE = 5;
    int numbers[SIZE] = {};
    for (int i = 0; i < SIZE; i++)
    {
        cin >> numbers[i];
        if (numbers[i] < smallest)
        {
            smallest = numbers[i];
        }
        if (numbers[i] > largest)
        {
            largest = numbers[i];
        }
        sum += numbers[i];
    }
    average = sum / SIZE;
    cout << "큰거는" << largest << endl;
    cout << "작은거는" << smallest << endl;
    cout << "평균" << average << endl;
    return 0;
}

    