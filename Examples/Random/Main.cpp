
#include "StdAfx.h"
#include "SMathLib/RandomIntGenerator.h"
#include <iostream>
#include <fstream>

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
int _tmain()
{
	SMathLib::RandomIntGenerator _random(131, 143);
	std::ofstream fp;
	fp.open("Test.csv");
	for(int i=0 ; i<1000000 ; ++i)
	{
		int x = _random.generate();
		fp << x << "\n";
		//cout << x << "\n";
	}
	fp.close();
	
	std::cout << "\n";
	return 0;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
