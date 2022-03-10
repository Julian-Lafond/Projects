/*********************************************************************************
* Julian Lafond, jmlafond
* 2022 Winter CSE101 PA 7
* BigInteger.cpp
* Binary Tree ADT
*********************************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include "Dictionary.h"

using namespace std;

Dictionary::Node::Node(keyType k, valType v)
{
	key = k;
	val = v;
	parent = nullptr;
	right = nullptr;
	left = nullptr;
}

Dictionary::Dictionary()
{
	nil = new Node("",-1);
   	this->root = this->current = nil;
	this->num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D)
{
	nil = new Node("",-1);
        this->root = this->current = nil;
	preOrderCopy(D.root, D.nil);
	this->num_pairs = 0;
}	
		
Dictionary::~Dictionary()
{
	clear();
	delete nil;
}

int Dictionary::size() const
{
	return num_pairs;
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const
{	
	if (R == nil || k == R->key)
	{
		return R;
	}
        else if (k < R->key)
        {
                return search(R->left, k);
        }
        else
        {
                return search(R->right, k);
        }
}

void Dictionary::inOrderString(std::string& s, Node* R) const
{
	if (R!=nil )
	{
		inOrderString(s, R->left);
		s.append(R->key);
		s.append(" : ");
		string str;
		s.append(std::to_string(R->val));
		s.append("\n");
		inOrderString(s, R->right);
	}
}



Dictionary::Node* Dictionary::findMin(Node* R)
{
	if (R != nil)
	{
		while(R->left != nil)
		{
			R = R->left;
		}	
		return R;
	}
	else 
	{
		return nil;
	}
}

Dictionary::Node* Dictionary::findMax(Node* R)
{
	if (R!=nil)
	{
		while(R->right!=nil)
		{
			R = R->right;
		}
		return R;
	}
	else
	{
		return nil;
	}
}

void Dictionary::preOrderString(std::string& s, Node* R) const
{
	if (R!= nil)
	{
		s.append(R->key);
		s.append("\n");
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

void Dictionary::postOrderDelete(Node* R)
{
	if (R!=nil)
	{
		postOrderDelete(R->left);
		postOrderDelete(R->right);
		delete R;
		num_pairs-=1;
	}	
	R = nil;
}
	
bool Dictionary::contains(keyType k) const
{
	Node *tmp = search(root,k);
	if (tmp == nil)
	{
		return false;
	}
	else
	{
		return true;
	}
}

valType& Dictionary::getValue(keyType K) const
{	
	if (contains(K) == false)
	{
		throw std::length_error("Dictionary: getVaule(): pair does not exist");
	}
	Node* tmp = search(root, K);
	return tmp->val;
}

bool Dictionary::hasCurrent() const
{	
	if (current != nil)
	{
		return true;
	}
	return false;		
}


keyType Dictionary::currentKey() const
{
	if (hasCurrent() == false)
	{	
		throw std::length_error("Dictionary: currentKey(): current is undefined");
	}
	return current->key;
}
	

valType& Dictionary::currentVal() const
{
	if (hasCurrent() == false)
	{
		throw std::length_error("Dictionary: currentVal(): current is undefined");
	}
	return this->current->val;
}


void Dictionary::clear() 
{
	postOrderDelete(root); 
	root = nil;
	current = nil;	
	num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v)
{
	Node *ta = nil;
	Node *ptr = root;
	Node *tmp = new Node(k,v);	
	while(ptr != nil)
	{
		ta = ptr;
		if (k < ptr->key)
		{
			ptr = ptr->left;	
		}
		else if (k == ptr->key)
		{		
			break;
		}
		else
		{
			ptr = ptr->right;	
		}
	}
	tmp->parent = ta;
	if (ta == nil)
	{
		root = tmp; 
	}
	else if (k < ta->key)
	{
		ta->left = tmp;
	}
        else if (k == ta->key)
        {
		ta->val = v;
		delete tmp;        
        	return;
	}
	else
	{
		ta->right = tmp;
	}
	tmp->left = nil;
	tmp->right = nil;
	num_pairs+=1;	
}

void Dictionary::preOrderCopy(Node* R, Node* N)
{
	if (R->val!=-1)
        {
                setValue(R->key, R->val);        
	        preOrderCopy(R->left, N);
                preOrderCopy(R->right, N);

        }

}

void Dictionary::Transplant(Node* u, Node* v) 
{
	if (u->parent == nil)
	{
		root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	if (v!= nil)
	{
		v->parent = u->parent;
	}
}

void Dictionary::remove(keyType k)
{
	if (contains(k) == false)
	{
		throw std::length_error("Dictionary: remove(): Pair does not exist");
	}
	else
	{
		Node* ptr = search(root, k);
		if (ptr->left == nil)
		{
			Transplant(ptr, ptr->right);
			if (current == ptr)
			{
				current = nil;
			}
		}
		else if (ptr->right == nil)
		{
			Transplant(ptr, ptr->left);
			if (current == ptr)
                        {
                                current = nil;
                        }
		}
		else
		{
			Node* temp = findMin(root->right);
			if (temp->parent!=ptr)
			{
				Transplant(temp, temp->right);
				if (current == ptr)
                        	{
                                	current = nil;
                        	}
				temp->right = ptr->right;
				temp->right->parent = temp;
			}
			Transplant(ptr, temp);
			temp->left = temp->left;
			temp->left->parent = temp;
		}
		delete ptr;
		num_pairs -= 1;
	}
}

void Dictionary::begin()
{
	if (size() > 0)
	{
		this->current = findMin(this->root);
	}	
	else
	{
		throw std::length_error("Dictionary: begin(): size out of range");
	}
}

void Dictionary::end()
{	
	if (size() > 0)
	{
		Node* temp = findMax(root);
		current = temp;
	}
	else
	{	
		throw std::length_error("Dictionary: begin(): size out of range");

	}
}

Dictionary::Node* Dictionary::success(Node* root, Node* N)
{
	if (N->right != nil)
	{
		return findMin(N->right);
	}
	Node* ptr = N->parent;
	while ((ptr != nil) && (N == ptr->right))
	{
		N = ptr;
		ptr = ptr->parent;
	}
	return ptr;
}

void Dictionary::next()
{	
	if (hasCurrent() == false)
	{
		throw std::length_error("Dictionary: next(): current undefined");
	}
	else
	{
		current = success(root, current);		
	}	
}

Dictionary::Node* Dictionary::pre(Node* root, Node* N)
{
	if (N->left != nil)
	{
		return findMax(N->left);
	}
	Node* ptr = N->parent;
	while ((ptr != nil) && (N == ptr->left))
	{
		N = ptr;
		ptr = ptr->parent;
	}
	return ptr;	
}

void Dictionary::prev()
{
	if (hasCurrent() == false)
	{
		throw std::length_error("Dictionary: prev(): current undefined");
	}
	else
	{
		current = pre(root, current);
	}
}



string Dictionary::to_string() const
{
	string s = "";
	inOrderString(s, this->root);
	return s;
}

string Dictionary::pre_string() const
{
	std::string s = "";
	preOrderString(s, this->root);
	return s;
}

bool Dictionary::equals(const Dictionary& D) const
{
	std::string a = "";
	std::string b = "";
	this->preOrderString(a, this->root);
	D.preOrderString(b, D.root);
	return a == b;	
}


std::ostream& operator<<( std::ostream& stream, Dictionary& D )
{
	return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B )
{
	if (A.Dictionary::equals(B) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Dictionary &Dictionary::operator=( const Dictionary& D)
{	
	if (this != &D)
	{
		Dictionary temp = D;
		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
	}
	return *this;
}
	

