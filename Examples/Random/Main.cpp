
#include "StdAfx.h"
#include "SMathLib/Random.h"
#include <iostream>
#include <fstream>

using namespace std;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
int _tmain()
{
	SMathLib::Random _random;
	ofstream fp;
	fp.open("Test.csv");
	for(int i=0 ; i<1000000 ; ++i)
	{
		int x = _random.UniformRand(131, 143);
		fp << x << "\n";
		//cout << x << "\n";
	}
	fp.close();
	
	cout << "\n";
	return 0;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
