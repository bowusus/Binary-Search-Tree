/*
___________________________________________________________________________________________

	Code by: Bernard Owusu Sefah
	Course: Non-Linear Data Structures
	Date: Febuary 14, 2020
	Topic: Implementation of a Binary Search Tree
___________________________________________________________________________________________
*/


#pragma once
#include <iostream>
#include <string>


using namespace std;


class BinarySearchTree
{
public:
	struct Node
	{
		string key;
		int count = 1;
		Node* left = NULL;
		Node* right = NULL;
		Node* child = NULL;
		Node* parent_Node = NULL;
	};
	Node* root;
	BinarySearchTree()
	{
		root = NULL;
	};
	void insert(string); // add item to the list
	void remove(string); // remove(delete) an item from the list * can't name the method delete because it is a C++ reserved word.
	void search(string); // search an item in the list
	void min(); // minimum value in the tree
	void max();
	void next(string);
	void previous(string);
	void parent(string);
	void child(string);
	void list();  // list the items in the list
	void inOrderTraversal(Node*, int i); // traverse the list of items
	void help(); // shows the command functions
};

string toLowerCase(string command);
