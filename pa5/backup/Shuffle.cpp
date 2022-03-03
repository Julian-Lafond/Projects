/*********************************************************************************
* Julian Lafond, jmlafond
* 2022 Winter CSE101 PA 5
* Shuffle.cpp
* Shuffle Client
*********************************************************************************/

#include <limits>
#include <iostream>
#include "List.h"

using namespace std;

void shuffle(List &D)
{
    	List one;
    	List two; 
    	D.moveFront(); 
    	int getlength = D.length();
	int half = getlength / 2;
    	for (int i = 1; i < half + 1; i+=1)
    	{
        	one.insertBefore(D.moveNext()); 
   	}
    	for (int j = half + 1; j <= D.length(); j+=1)
    	{
        	two.insertBefore(D.moveNext()); 
    	}
    	D.clear(); 
    	two.moveFront(); 
    	one.moveFront(); 
    	for (int k = 1; k <= half + 1; k+=1)
    	{
		if (two.length() > two.position())
        	{
            		D.insertBefore(two.moveNext());
        	}
		if (one.length() > one.position())
        	{
            		D.insertBefore(one.moveNext());
        	}
    	}
}


int main(int argc, char * argv[])
{
    	if(argc != 2) 
    	{
        	cout << "Invalid number of inputs" << endl;
        	exit(EXIT_FAILURE);
    	}
  	cout << "deck size       shuffle count" << endl;
    	cout << "------------------------------" << endl;
	List first;
	List second;
	string fp = argv[1];
    	int num = stoi(fp);
    	int length = num + 1;
	int mp[length];
	for (int i = 1; i < num + 1; i+=1)   
 	{
        	mp[i] = 0;
        	second.insertBefore(i);
        	first.insertBefore(i);
        	shuffle(first);
        	mp[i]+=1;
        	while(!(first == second))
        	{
            		shuffle(first);
            		mp[i]+=1;
        	}
            	string spacing = "            ";
        	cout << " " << i << spacing << mp[i] << endl; 
    	}
}
