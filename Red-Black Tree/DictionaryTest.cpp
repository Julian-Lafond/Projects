/*********************************************************************************
* Julian Lafond, jmlafond
* 2022 Winter CSE101 PA 8
* DictionaryTest.cpp
* Test for Dictionary.cpp
*********************************************************************************/
#include <limits>
#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[])
{
	Dictionary A;
        A.setValue("Mark", 3);
        A.setValue("Jim", 2);
        A.setValue("Bob", 4);
        cout << "Size is " << A.size() << endl; 
        cout << "Is jim in the tree (true = 1 false = 0): " << A.contains("Jim") << endl;
        
        cout << endl;
        cout << A << endl;
        cout << "Value of Mark is " << A.getValue("Mark") << endl;
        cout << "Value of Jim is " << A.getValue("Jim") << endl;
        cout << "Value of Bob is " << A.getValue("Bob") << endl;
        cout << endl;

        cout << endl;
        A.begin();
        cout << "Current is at beginnig" << endl;
        cout << "Has current is " << A.hasCurrent() << endl;
        cout << "Current key is " << A.currentKey() << endl;
        cout << "Current val is " << A.currentVal() << endl;
        
        cout << endl;
        A.next();
        cout << "Moved current Next" << endl;
        cout << "Has current is " << A.hasCurrent() << endl;
        cout << "Current key is " << A.currentKey() << endl; 
        cout << "Current val is " << A.currentVal() << endl;
        
        cout << endl;
        A.prev();
        cout << "Moved current prev " << endl;
        cout << "Has current is " << A.hasCurrent() << endl;
        cout << "Current key is " << A.currentKey() << endl;
        cout << "Current val is " << A.currentVal() << endl;
	cout << endl;
        
	cout << endl;
        A.end();
        cout << "Moved current Back " << endl;
        cout << "Has current is " << A.hasCurrent() << endl;
        cout << "Current key is " << A.currentKey() << endl;
        cout << "Current val is " << A.currentVal() << endl;
        
        cout << endl;
        cout << "After removing" << endl;
        A.remove("Jim");
        cout << "Is jim in the tree (true = 1 false = 0):" << A.contains("Jim") << endl;
        
        cout << endl;
        cout << "Tree after removing " << endl;
        cout << A << endl;
        
        Dictionary B;
        B.setValue("Mark", 3);
        B.setValue("Bob", 4);
        cout << "A and B is equals (true = 1 false = 0) " << B.equals(A) << endl;
        
        cout << endl;
        cout << "String representation " << A.to_string() << endl;
        cout << "Prestring representation " << A.pre_string() << endl;
        
        cout << endl; 
        A.clear();
        cout << "After clearing " << endl;
        cout << A << endl;

}
