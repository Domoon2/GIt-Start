#include <iostream>
#include <map>
#include <cstdio>
#include<cstring>
#include <iterator>
#include <ctime>

using namespace std;


int main()
{
	int a = 1;
	string members[] = { "1번","2번","3번","4번","5번","6번","7번","8번","9번"};
	map<int, string> clean_cycle;
	for (int i = 0; i < 9; i++)
	{
		clean_cycle[i] = members[i];
	}

	
	for (int j = 0; j < 25; j+=2)
	{
		
		cout << clean_cycle[j%9] << clean_cycle[(j + 1)%9] << endl;;
	}
	return 0;

	
}