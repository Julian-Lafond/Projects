/*********************************************************************************
* Julian Lafond, jmlafond
* 2022 Winter CSE101 PA 8
* BigInteger.cpp
* Binary Tree ADT
*********************************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include "Dictionary.h"

using namespace std;

#define RED 3 
#define BLACK 4

Dictionary::Node::Node(keyType k, valType v)
{
	key = k;
	val = v;
	parent = nullptr;
	right = nullptr;
	left = nullptr;
	color = -1;
}

Dictionary::Dictionary()
{
	nil = new Node("",-1);
   	nil->color = BLACK;
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
        if (k < R->key)
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
	if (R!=nil && R!=nullptr)
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
		throw std::length_error("Dictionary: getValue(): key 'blah' does not exist");
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
		throw std::length_error("Dictionary: currentKey(): current undefined");
	}
	return current->key;
}
	

valType& Dictionary::currentVal() const
{
	if (hasCurrent() == false)
	{
		throw std::length_error("Dictionary: currentVal(): current undefined");
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

void Dictionary::LeftRotate(Node* N)
{
	Node* tmp = N;
        Node* ptr = N->right;
        tmp->right = ptr->left;
        if (ptr->left!=nil)
        {
                ptr->left->parent = tmp;
        }
        ptr->parent = tmp->parent;
        if (tmp->parent == nil)
        {
                root = ptr;
        }
        else if (tmp == tmp->parent->left)
        {
                tmp->parent->left = ptr;
        }
        else
        {
                tmp->parent->right = ptr;
        }
        ptr->left = tmp;
        tmp->parent = ptr;
}

void Dictionary::RightRotate(Node* N)
{
	Node* tmp = N;
        Node* ptr = N->left;
        tmp->left = ptr->right;
        if (ptr->right!=nil)
        {
                ptr->right->parent = tmp;
        }
        ptr->parent = tmp->parent;
        if (tmp->parent == nil)
        {
                root = ptr;
        }
        else if (tmp == tmp->parent->right)
        {
                tmp->parent->right = ptr;
        }
        else
        {
                tmp->parent->left = ptr;
        }
        ptr->right = tmp;
        tmp->parent = ptr;
}

void Dictionary::RB_InsertFixUp(Node* N)
{
	Node* ptr;
	while(N->parent->color == RED)
	{
		if (N->parent == N->parent->parent->left)
		{
			ptr = N->parent->parent->right;
			if (ptr->color == RED)
			{
				N->parent->color = BLACK;
				ptr->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			}
			else
			{
				if (N == N->parent->right)
				{
					N = N->parent;
					LeftRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				RightRotate(N->parent->parent);
			}
		}
		else
		{
			ptr = N->parent->parent->left;
			if (ptr->color == RED)
			{
				N->parent->color = BLACK;
				ptr->color = BLACK;
				N->parent->parent->color = RED;
				N = N->parent->parent;
			}
			else
			{
				if (N == N->parent->left)
				{
					N = N->parent;
					RightRotate(N);
				}
				N->parent->color = BLACK;
				N->parent->parent->color = RED;
				LeftRotate(N->parent->parent);
			}
		}
	}
	root->color = BLACK;
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
	tmp->color = RED;
	RB_InsertFixUp(tmp);
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

void Dictionary::RB_Transplant(Node* u, Node* v) 
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
	v->parent = u->parent;
}


void Dictionary::RB_DeleteFixUp(Node* N)
{
	Node *ptr;
	while(N!= root && N->color == BLACK)
	{
		if (N == N->parent->left)
		{
			ptr = N->parent->right;
			if (ptr->color == RED)
			{
				ptr->color = BLACK;
				N->parent->color = RED;
				LeftRotate(N->parent);
				ptr = N->parent->right;
			}
			if (ptr->left->color == BLACK && ptr->right->color == BLACK)
			{
				ptr->color = RED;
				N = N->parent;
			}
			else
			{
				if (ptr->right->color == BLACK)
				{
					ptr->left->color = BLACK;
					ptr->color = RED;
					RightRotate(ptr);
					ptr = N->parent->right;
				}
				ptr->color = N->parent->color;
				N->parent->color = BLACK;
				ptr->right->color = BLACK;
				LeftRotate(ptr->parent);
				N = root;
			}
		}
		else
		{
			ptr = N->parent->left;
			if (ptr->color == RED)
			{
				ptr->color = BLACK;
				N->parent->color = RED;
				RightRotate(N->parent);
				ptr = N->parent->left;
			}
			if (ptr->right->color == BLACK && ptr->left->color == BLACK)
			{
				ptr->color = RED;
				N = N->parent;
			}	
			else
			{
				if (ptr->left->color == BLACK)
				{
					ptr->right->color = BLACK;	
					ptr->color = RED;
					LeftRotate(ptr);
					ptr = N->parent->left;
				}
				ptr->color = N->parent->color;
				N->parent->color = BLACK;
				ptr->left->color = BLACK;
				RightRotate(N->parent);
				N = root;
			}
		}
	}
	N->color = BLACK;
}

void Dictionary::RB_Delete(Node* N)
{
	Node* ptr;
        Node* tmp = N;
        Node* tmp1 = tmp;
        int original = tmp1->color;
        if (tmp->left == nil)
        {
                ptr = tmp->right;
                RB_Transplant(tmp, tmp->right);
        }
        else if (tmp->right == nil)
        {
                ptr = tmp->left;
                RB_Transplant(tmp, tmp->left);
        }
        else
        {
                tmp1 = findMin(tmp->right);
                original = tmp1->color;
                ptr = tmp1->right;
                if (tmp1->parent == tmp)
                {
                        ptr->parent = tmp1;
                }
                else
                {
                        RB_Transplant(tmp1, tmp1->right);
                        tmp1->right = tmp->right;
                        tmp1->right->parent = tmp1;
                }
                RB_Transplant(tmp, tmp1);
                tmp1->left = tmp->left;
                tmp1->left->parent = tmp1;
                tmp1->color = tmp->color;
        }
        if (original == BLACK)
        {
                RB_DeleteFixUp(ptr);
        }
}


void Dictionary::remove(keyType k)
{	
	if (contains(k) == true)
	{       
        	Node* ptr;
        	ptr = search(root, k);
        	if (current == ptr)
        	{       
                	current = nil;
        	}
        	RB_Delete(ptr);
		delete ptr;
		num_pairs-=1;
	}
	else
	{
		throw std::length_error("Dictionary: remove(): key 'blah does not exist");
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
		throw std::length_error("Dictionary: end(): size out of range");

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
	

