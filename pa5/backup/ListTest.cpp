/*********************************************************************************
* Julian Lafond, jmlafond
* 2022 Winter CSE101 PA 5
* ListTest.cpp
* List Testing
*********************************************************************************/

#include<iostream>
#include<string>
#include"List.h"

using namespace std;

int main()
{
    	List A;
	List B;
	List C;
	for (int i = 1; i <= 20; i+=1)
	{
		A.insertAfter(i);
	}    
	for (int i = 1; i <= 10; i++)
	{
		B.insertBefore(i);
	}
    	cout << "A = " << A << endl;
    	cout << "Position of A " << A.position() << endl;
    	cout << "Length of A " << A.length() << endl;
	cout << "Position of B = " << B.position() << endl;
	cout << "Length of B = " << B.length() << endl;
	cout << endl;
	A.moveFront();
	B.moveBack();
	cout << "After moving" << endl;
	cout << "A = " << A << endl;
	cout << "B = " << B << endl;
	A.moveNext();
	B.movePrev();
	cout << "moveNext" << endl;
    	cout << "A = " << A << endl;
    	cout << "movePrev " << endl;
    	cout << "B = " << B << endl;
	cout << endl;
	cout << "A == B is " << (A==B?"true":"false") << endl;
	C = A.concat(B);
	cout << "After concat" << endl;
	cout << "C = " << C << endl;	
	cout << A.findNext(10) << endl;
	cout << B.findPrev(15) << endl;
	cout << "A.position() = " << A.position() << endl;
	cout << "B.position() = " << B.position() << endl;
	A.eraseBefore();
	B.eraseAfter();
	cout << B << endl;
	cout << A << endl;
	B.cleanup();
	cout << "After cleanup" << endl;
	cout << "B = " << B << endl;
	cout << B.position() << endl;
	A.setBefore(4);
	B.setAfter(5);
	cout << "After setting" << endl;
	cout << "A = " << A << endl;
	cout << "B = " << B << endl;
	cout << "Peek Next" << endl;
	cout << A.peekNext() << endl;
	cout << "Peek Prev" << endl;	
	cout << B.peekPrev() << endl;
	cout << "Get Front" << endl;	
	cout << A.front() << endl;
	cout << "Get Back" << endl;
	cout << B.back() << endl;
}
