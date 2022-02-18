/*********************************************************************************
* Julian Lafond, jmlafond
* 2022 Winter CSE101 PA 5
* List.cpp
* List ADT
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include <limits>

#include"List.h"
using namespace std;

//Node constructor
List::Node::Node(ListElement x)
{
	data = x;
	next = nullptr;
	prev = nullptr;
}

//creates a new list
List::List()
{
	frontDummy = new Node(-1);
	backDummy = new Node(-2);
	frontDummy->next = backDummy;
	frontDummy->prev = nullptr;
	backDummy->prev = frontDummy;
	backDummy->next = nullptr;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

//copy constructor
List::List(const List& L)
{	
	frontDummy = new Node(-1);
        backDummy = new Node(-2);
        frontDummy->next = backDummy;
 	frontDummy->prev = nullptr;
	backDummy->next = nullptr;
        backDummy->prev = frontDummy;
        beforeCursor = frontDummy;
        afterCursor = backDummy;
        pos_cursor = 0;
        num_elements = 0;	
	Node* N = L.frontDummy->next;
	while (N!=L.backDummy)
	{
		this->insertBefore(N->data);
		N = N->next;
	}
	this->moveFront();
}

//deconstructor
List::~List()
{
	clear();	
	delete frontDummy;
	delete backDummy;
}	

int List::length() const
{
	return num_elements;
}

ListElement List::front() const
{
	if (num_elements <= 0)
	{
		throw std::length_error("List: front(): cursor out of range");
	}
	return frontDummy->next->data;
}

ListElement List::back() const 
{
	if (pos_cursor <= 0)
	{
		throw std::length_error("List: back():: cursor out of range");
	}	
	return backDummy->prev->data;
}

int List::position() const
{
	if (pos_cursor < 0 || pos_cursor > num_elements)
	{
		throw std::length_error("List: position():: cursor out of range");
	}
	return pos_cursor;
}

ListElement List::peekNext() const
{
	if (pos_cursor >= num_elements)
	{
	      throw std::length_error("List: peekNext():: cursor is out of range");
	}
	return afterCursor->data;
}

ListElement List::peekPrev() const
{
	if (pos_cursor <= 0)
	{
	      throw std::length_error("List: peekPrev():: cursor is out of range");
	}
        return beforeCursor->data;
}

void List::clear()
{
	moveFront();
	while(frontDummy->next!=backDummy)
	{
		eraseAfter();	 
	}
}

void List::moveFront()
{
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	pos_cursor = 0;
}

void List::moveBack()
{
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	pos_cursor = num_elements;
}

	
ListElement List::moveNext()
{
	if (pos_cursor >= num_elements)
	{
		throw std::length_error("List: moveNext(): position is out of index");
	}
	beforeCursor = beforeCursor->next;
	afterCursor = afterCursor->next;
	pos_cursor+=1;
	return beforeCursor->data;
}

ListElement List::movePrev()
{
	if (pos_cursor <= 0)
	{
		throw std::length_error("List: movePrev(): position is out of index");
	}
	beforeCursor = beforeCursor->prev;
	afterCursor = afterCursor->prev;
	pos_cursor-=1;
	return afterCursor->data;
}
void List::insertAfter(ListElement x)
{
	Node* new_node = new Node(x);
	new_node->next = afterCursor;
	new_node->prev = beforeCursor;
	beforeCursor->next = new_node;
	afterCursor->prev = new_node;
	afterCursor = new_node;
	num_elements+=1;
}

		
void List::insertBefore(ListElement x)
{
	Node* new_node = new Node(x);
	new_node->next = afterCursor;
	new_node->prev = beforeCursor;
	beforeCursor->next = new_node;
	afterCursor->prev = new_node;
	beforeCursor = new_node;
	num_elements+=1;
	pos_cursor+=1;
}


void List::setAfter(ListElement x)
{
	if (pos_cursor >= num_elements)
	{
		throw std::length_error("List: setAfter(): Index out of range");
	}
	x = afterCursor->data;
}

void List::setBefore(ListElement x)
{
	if (position() <= 0)
	{
		throw std::length_error("List: setBefore(): Index out of range");
	}
	x = beforeCursor->data;
}

void List::eraseAfter()
{
	if (pos_cursor >= num_elements)
        {
                throw std::length_error("List: eraseAfter(): Index out of range");
	}
	Node *N = afterCursor;
        afterCursor = afterCursor->next;
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
        num_elements-=1;
        delete N;
}

void List::eraseBefore()
{
        if (position() <= 0)
        {
                throw std::length_error("List: eraseBefore(): Index out of range");
	} 
	Node *N = beforeCursor;
        beforeCursor = beforeCursor->prev;
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
	pos_cursor-=1;
        num_elements-=1;
        delete N;
}


int List::findNext(ListElement x)
{
	while (pos_cursor != num_elements)
	{
		if (afterCursor->data == x)
		{
			moveNext();
			return pos_cursor;
		}
		moveNext();
	}
	return -1;		
}
				
int List::findPrev(ListElement x)
{
	while (pos_cursor != 0)
        {
                if (beforeCursor->data == x)
                {
                        movePrev();
                        return pos_cursor;
                }
      		movePrev(); 
       } 
       return -1;
}

void List::cleanup()
{		
	if(num_elements != 0) 
	{ 
		int num = 0;
		int start = pos_cursor;
		int curr = 0;
 		moveFront();
	       	while(num_elements != pos_cursor) 
        	{
        	    	num = peekNext(); 
            		moveNext(); 
            		curr = pos_cursor;
            		while(findNext(num) >= 0) 
            		{ 
                		if(pos_cursor < start + 1) 
                		{
                    			start-=1; 
                		}
                		eraseBefore(); 
            		}
            		moveFront();
			for (int i = 1; i < curr + 1; i+=1)
			{
				moveNext();
			}
		} 
        	moveFront();
    		for (int m = 1; m < start + 1; m+=1)
	    	{
            		moveNext();
        	}
    	}		
}


List List::concat(const List& L) const
{
	List new_list = List();
  	Node *second_node = L.backDummy->prev;
 	Node *first_node = this->backDummy->prev;
 	while (L.frontDummy != second_node) 
	{
    		new_list.insertAfter(second_node->data);
    		second_node = second_node->prev;
	}
	while (frontDummy != first_node)
        {
                new_list.insertAfter(first_node->data);
                first_node = first_node->prev;
        }
        return new_list;
}


string List::to_string() const
{
	string paren = "( ";	
	Node* temp = nullptr;
	for (temp = frontDummy->next; temp!=backDummy; temp = temp->next)
    	{
        	if(temp == backDummy->prev) 
        	{	 
            		paren += std::to_string(temp->data);
        	}
        	else 
        	{
            		paren += std::to_string(temp->data) + ","; 
        	}
   	 }
    	paren += " )";
    	return paren; 
}


bool List::equals(const List& R) const
{	
	bool check;
	check = false;
 	Node* second;
  	Node* first;
  	first = frontDummy->next;
 	second = R.frontDummy->next;
  	check =(num_elements == R.num_elements);
  	while(first != backDummy && check)
	{
    		check = (first->data == second->data);
    		first = first->next;
    		second = second->next;
  	}
  	return check;
}


ostream& operator<<(ostream& stream, List& L )
{
	  return stream << L.List::to_string();

}

bool operator==(const List& A,  const List& B )
{
	  return A.List::equals(B);
}

	
List& List::operator=( const List& L )
{
	List ptr (L);
	if( this != &L ) 
    	{
        	swap(backDummy, ptr.backDummy); 
        	swap(frontDummy, ptr.frontDummy);
        	swap(num_elements, ptr.num_elements);
        	swap(afterCursor, ptr.afterCursor);
        	swap(beforeCursor, ptr.beforeCursor);
        	swap(pos_cursor, ptr.pos_cursor);
    	}
    	return *this;
}


