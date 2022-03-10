#include <limits>
#include <iostream>
#include "Dictionary.h"
#include <fstream> 
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>	

using namespace std;

int main(int argc, char * argv[])
{	
	ifstream in;	
   	ofstream out;
	if( argc != 3 )
	{
      		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
     	 	return(EXIT_FAILURE);
   	}
   	in.open(argv[1]);
   	if( !in.is_open() )
	{
      		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      		return(EXIT_FAILURE);
   	}
   	out.open(argv[2]);
   	if( !out.is_open() )
	{
      		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      		return(EXIT_FAILURE);
   	}
	Dictionary A;
	int i = 1;
	string line;
	while (getline(in, line))
        {
		A.setValue(line, i);
		i+=1;
	}
	out << A.to_string() << endl;
	out << A.pre_string() << endl;
	in.close();
	out.close();
	return 0; 		
}

