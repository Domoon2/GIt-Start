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
	string members[] = { "1��","2��","3��","4��","5��","6��","7��","8��","9��"};
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