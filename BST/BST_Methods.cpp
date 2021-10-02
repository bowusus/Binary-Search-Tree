/*
___________________________________________________________________________________________
	
	Code by: Bernard Owusu Sefah
	Course: Non-Linear Data Structures
	Date: Febuary 14, 2020
	Topic: Implementation of a Binary Search Tree
___________________________________________________________________________________________
*/

#include <string>
#include "BST_Methods.h"
#include <iostream>




using namespace std;

void BinarySearchTree::insert(string inputString)
/*
	when a user types in the insert command followed a string
	it should input a node with that string along with the value
	and sets its value to one if the node already exists, just
	increments the count.
*/

{
	bool exist = false;
	struct Node* currentNode;
	struct Node* newNode = new Node;
	struct Node* parentNode;
	newNode->key = inputString;
	newNode->left = NULL;
	newNode->right = NULL;
	parentNode = NULL;

	if (root == NULL) // checks to make sure the tree is empty
	{
		root = newNode;
		cout << newNode->key << " " << newNode->count << endl;
	}
	else if (root != NULL)
	{
		currentNode = root;
		while (currentNode != NULL)
		{
			if (currentNode->key == newNode->key)
			{
				exist = true;
				currentNode->count += 1;
				cout << currentNode->key << " " << currentNode->count << endl;
				break;
			}
			if (newNode->key > currentNode->key)
				currentNode = currentNode->right;
			else
			currentNode = currentNode->left;
		};

		if (exist == false)  //if the node does not exist, then creates the node.
		{
			currentNode = root;
			while (currentNode != NULL)
			{
				parentNode = currentNode;
				if (newNode->key > currentNode->key)
				{
					currentNode = currentNode->right;  // right to left
				}
				else
				{
					currentNode = currentNode->left; // changed from left to right
				};
			};
			if (newNode->key < parentNode->key)
			{
				parentNode->left = newNode;
			}
			else
			{
				parentNode->right = newNode;
			};
			newNode->parent_Node = parentNode;
			cout << newNode->key << " " << newNode->count << endl;
		};
	};
};

void BinarySearchTree::remove(string inputString)
/*	removes node with user entered input, if the count of the node equals 1, complete deletes node,
	if the count of the node is greater than 1, decreases count,
	if node doesn't exist, outputs string with 0.
*/

{
	bool found = false;
	bool exist = false;
	Node* currentNode;
	Node* parentNode;
	Node* smallNode;
	currentNode = root;
	parentNode = NULL;
	smallNode = NULL;

	if (root == NULL) {
		cout << inputString + " " << "-1" << endl;
		return;
	};

	while (currentNode != NULL) // search for the node in the tree.
	{
		if (currentNode->key == inputString)
		{
			exist = true;
			break;
		}
		else
		{
			parentNode = currentNode;
			if (inputString > currentNode->key)
			{
				currentNode = currentNode->right;
			}
			else
			{
				currentNode = currentNode->left;
			};
		};
	};
	if (exist == false) //true if the node doesn't exist in the tree.
	{
		cout << inputString + " " << "-1" << endl;
	}
	else if (currentNode->count > 1) //decreases the count if it's greater than 1.
	{
		currentNode->count -= 1;
		cout << currentNode->key + " " << currentNode->count << endl;
	}
	else if (currentNode == root && currentNode->count == 1)
		//since there is no parent node this changes the method when the deleted node is the root.
	{
		if (root->left == NULL && root->right == NULL) //no right and left children.
		{
			root = NULL;
			delete currentNode;
			cout << inputString << " " << "0" << endl;
		}
		else if (root->left == NULL && root->right != NULL) //the tree has a right child.
		{
			smallNode = root->right;
			smallNode->parent_Node = NULL;
			root = smallNode;
			delete currentNode;
			cout << inputString << " " << "0" << endl;
		}
		else if (root->right == NULL && root->left != NULL) //the tree has a left child.
		{
			smallNode = root->left;
			smallNode->parent_Node = NULL;
			root = smallNode;
			delete currentNode;
			cout << inputString << " " << "0" << endl;
		}
		else if (root->right != NULL && root->left != NULL) //the tree has 2 children.
		{
			Node* nextSmallestElement;
			Node* secondSmallestElement;
			secondSmallestElement = NULL;
			nextSmallestElement = currentNode->right;
			if (nextSmallestElement->parent_Node != NULL)
			{
				secondSmallestElement = nextSmallestElement->parent_Node;
			}
			while (found == false)
			{
				if (nextSmallestElement->left != NULL)
				{
					secondSmallestElement = nextSmallestElement;
					nextSmallestElement = nextSmallestElement->left;
				}
				if (nextSmallestElement->left == NULL)
				{
					found = true;
				}
			}
			if (found == true)
			{
				if (currentNode->right != nextSmallestElement)
				{
					nextSmallestElement->right = currentNode->right;
					nextSmallestElement->right->parent_Node = nextSmallestElement;
				}
				if (currentNode->left != nextSmallestElement)
				{
					nextSmallestElement->left = currentNode->left;
					nextSmallestElement->left->parent_Node = nextSmallestElement;
				}

				currentNode->left = NULL;
				currentNode->right = NULL;

				if (secondSmallestElement->right == nextSmallestElement)
				{
					secondSmallestElement->right = NULL;
				}
				if (secondSmallestElement->left == nextSmallestElement)
				{
					secondSmallestElement->left = NULL;
				}
				delete currentNode;
				nextSmallestElement->parent_Node = NULL;
				root = nextSmallestElement;
				cout << inputString + " " << "0" << endl;
			}
		}
	}
	else if (currentNode->left == NULL && currentNode->right == NULL && currentNode->count == 1)
		// true when the node has no children and is being removed from the tree.
	{
		if (parentNode->right == currentNode && currentNode->count == 1)
		{
			parentNode->right = NULL;
			delete currentNode;
			cout << inputString << " " << "0" << endl;
		};
		if (parentNode->left == currentNode && currentNode->count == 1)
		{
			parentNode->left = NULL;
			delete currentNode;
			cout << inputString << " " << "0" << endl;
		};
	}
	else if (((currentNode->right && !currentNode->left) || (currentNode->left && !currentNode->right)) && currentNode->count == 1)
		// this is true when the node has one child and is being removed from the tree.
	{
		if (!currentNode->left && currentNode->right)
		{
			if (parentNode->left == currentNode)
			{
				smallNode = currentNode->right;
				smallNode->parent_Node = parentNode;
				parentNode->left = smallNode;
				delete currentNode;
				cout << inputString << " " << "0" << endl;
			}
			else
			{
				smallNode = currentNode->right;
				smallNode->parent_Node = parentNode;
				parentNode->right = smallNode;
				delete currentNode;
				currentNode = smallNode;
				cout << inputString << " " << "0" << endl;
			}
		}
		else if (!currentNode->right && currentNode->left)
		{
			if (parentNode->left == currentNode)
			{
				smallNode = currentNode->left;
				smallNode->parent_Node = parentNode;
				parentNode->left = smallNode;
				delete currentNode;
				cout << inputString << " " << "0" << endl;
			}
			else
			{
				smallNode = currentNode->left;
				smallNode->parent_Node = parentNode;
				parentNode->right = smallNode;
				delete currentNode;
				cout << inputString << " " << "0" << endl;
			}
		}
	}
	else if (currentNode->right && currentNode->left)
		// true when the node being removed has two children and finds the next smallest element and replaces the node being removed.
		//all pointers now adapt to the new node.
	{
		Node* nextSmallestElement;
		Node* secondSmallestElement;
		secondSmallestElement = NULL;
		nextSmallestElement = currentNode->right;

		if (nextSmallestElement->parent_Node != NULL) // NULL pointer errors without if statement.
		{
			secondSmallestElement = nextSmallestElement->parent_Node;
		}
		while (found == false) //this loop finds the left most child to find the successor.
		{
			if (nextSmallestElement->left != NULL)
			{
				secondSmallestElement = nextSmallestElement;
				nextSmallestElement = nextSmallestElement->left;
			}
			if (nextSmallestElement->left == NULL)
			{
				found = true;
			}
		}
		if (found == true) //successor is now found, all node pointers are adapt to replace deleted node with successor.
		{
			if (currentNode->right != nextSmallestElement)
			{
				nextSmallestElement->right = currentNode->right;
				nextSmallestElement->right->parent_Node = nextSmallestElement;
			}
			if (currentNode->left != nextSmallestElement)
			{
				nextSmallestElement->left = currentNode->left;
				nextSmallestElement->left->parent_Node = nextSmallestElement;
			}

			currentNode->left = NULL;
			currentNode->right = NULL;

			if (parentNode->right == currentNode)
			{
				parentNode->right = nextSmallestElement;
			}
			if (parentNode->left == currentNode)
			{
				parentNode->left = nextSmallestElement;
			}
			if (secondSmallestElement->right == nextSmallestElement)
			{
				secondSmallestElement->right = NULL;
			}
			if (secondSmallestElement->left == nextSmallestElement)
			{
				secondSmallestElement->left = NULL;
			}
			delete currentNode;
			nextSmallestElement->parent_Node = parentNode;
			cout << inputString + " " << "0" << endl;
		}
	}
};


void BinarySearchTree::search(string inputString)
/*  this method searches for a node that maches the input string
	entered by the user and provides an output.
	If the eneterd input exist return the entered input and "1"
	If the entered input does not exist return the entered input
	and "0"
*/
{
	bool exist = false;
	Node* currentNode;
	currentNode = root;

	if (root == NULL)          
	{
		cout << inputString + " " << "0" << endl;
		return;
	};
	while (currentNode != NULL)
	{
		if (currentNode->key == inputString)
		{
			exist = true;
			break;
		}
		else
		{
			if (inputString > currentNode->key)
				currentNode = currentNode->right;
			else
				currentNode = currentNode->left;
		};
	};
	if (exist == true)
	{
		cout << currentNode->key + " " << currentNode->count << endl;
	}
	if (exist == false)
	{
		cout << inputString + " " << "0" << endl;
	}
}

void BinarySearchTree::min()
/*
	this method outputs the smallest value in the Binary Tree
*/
{
	struct Node* currentNode;
	if (root == NULL)
		cout << endl;
	else
	{
		currentNode = root;
		while (currentNode->left)
			currentNode = currentNode->left;
		cout << currentNode->key << " " << endl;
	};
};

void BinarySearchTree:: parent(string inputString)
/* this method outputs the parentNode of the BinarySearchTree
	if the root node of the tree does not have any inputs 
	outputs a blank line.*/
{

	bool exist = false;
	Node* currentNode;
	currentNode = root;

	if (root == NULL)
{
	cout << " " << endl;
	return;
};
	while (currentNode != NULL)
{
	if (currentNode->key == inputString)
	{
		exist = true;
		break;
	}
	else
	{
		if (inputString > currentNode->key)
			currentNode = currentNode->right;
		else
			currentNode = currentNode->left;
	};
};
if (exist == true)
{
	if (currentNode->parent_Node == NULL) {
		cout << " " << endl;
	} else
	cout << currentNode->parent_Node->key + " "  << endl;
}else
{
	cout << inputString + " " << "0" << endl;
}
}
///search for node
//when you find node 
//if(node.left == NULL)
//print null
//else pint node.left


void BinarySearchTree::child(string inputString)
/*
	this method takes the user input finds it and if it is the tree 
	prints the left and right child of the tree, if the node doesn't 
	a child prints NULL
*/
{

	bool exist = false;
	Node* currentNode;
	currentNode = root;

	if (root == NULL)
	{
		cout << " " << endl;
		return;
	};
	while (currentNode != NULL)
	{
		if (currentNode->key == inputString)
		{
			exist = true;
			break;
		}
		else
		{
			if (inputString > currentNode->key)
				currentNode = currentNode->right;
			else
				currentNode = currentNode->left;
		};
	}
	if (exist == true)
	{
		if (currentNode->left == NULL)  // left child exist print NULL 
		{
			cout << "NULL, ";
		}
		else
		cout << currentNode->left << ",";  
		if (currentNode->right == NULL)  // print right child, if doesn't exist print NULL
		{
			cout << "NULL, ";
		}
		else
		cout << currentNode->right->key << endl;
	}
	else
	{
		cout << inputString + " " << "0" << endl;
		
	}
}

	

void BinarySearchTree::next(string inputString)
/*
	the mehtod finds the next smallest value in the tree compared to the user
	input. If the input is exist in the tree, it finds the next item
	as long as it is not the max value. if the input does not exist
	a blank line is printed.
*/
{
		bool exists = false;
		bool found = false;
		Node* currentNode;
		Node* parentNode;
		currentNode = root;
		parentNode = NULL;

		if (root == NULL) {
			cout << endl;
			return;
		};

		while (currentNode != NULL) //finds the node that contains input if it exists.
		{
			if (currentNode->key == inputString)
			{
				exists = true;
				break;
			}
			else
			{
				parentNode = currentNode;
				if (inputString > currentNode->key)
				{
					currentNode = currentNode->right;
				}
				else
				{
					currentNode = currentNode->left;
				};
			};
		};
		if (exists == true) //true if the node it exists
		{
			if (currentNode->right != NULL) //if three has a right child, finds lowest left branch of the tree.
			{
				currentNode = currentNode->right;
				while (found == false)
				{
					parentNode = currentNode;
					if (currentNode->left != NULL)
					{
						currentNode = currentNode->left;
					}
					if (currentNode->left == NULL)
					{
						found = true;
						cout << currentNode->key << endl;
					}
				}
			}
			else if (parentNode == NULL)//if the first case fails, checks the tree to see if it has a parentNode.
			{
				cout << endl;
			}
			else if (currentNode->right == NULL) //if the tree has a parentNode, goes up the tree by following parent pointer and finds a successor.
			{
				while (found == false)
				{
					if (parentNode->left != NULL)
					{
						if (parentNode->left == currentNode)
						{
							found = true;
							cout << parentNode->key << endl;
							break;
						}
					}
					if (parentNode->parent_Node != NULL)
					{
						currentNode = currentNode->parent_Node;
						parentNode = parentNode->parent_Node;
					}
					else if (parentNode->parent_Node == NULL)
					{
						cout << endl;
						break;
					}

				}
			}
		}
		if (exists == false)
		{
			cout << endl;
		}
	}

void BinarySearchTree::previous(string inputString)
/*
	searches for the previous smallest value in the binary tree and compare
	it to the user input, if the user input exist, find the previous value as
	long as it is not the min value else if the user input doesn't exist
	prints a blank line.
*/
{
	bool exist = false;
	bool found = false;
	Node* currentNode;
	Node* parentNode;
	currentNode = root;
	parentNode = NULL;

	if (root == NULL)
	{
		cout << endl;
		return;
	};

	while (currentNode != NULL) // search the tree to find the node with the input
	{
		if (currentNode->key == inputString)
		{
			exist = true;
			break;
		}
		else
		{
			parentNode = currentNode;
			if (inputString > currentNode->key)
				currentNode = currentNode->right;
			else
			currentNode = currentNode->left;

		};

	};
	if (exist == true) // true if the node exist.
	{
		if (currentNode->left != NULL) // follows left child and then the right child till finds the leaf node that branch
		{
			currentNode = currentNode->left;
			while (currentNode->right)
				currentNode = currentNode->right;
			cout << currentNode->key << " " << currentNode->count << endl;
		}

		else if (currentNode->parent_Node == NULL) // if the first case fail with no parent node, predecessor don't exist.
			cout << endl;

		else if (currentNode->left == NULL) // if the parent node exist, follow the parent pointer till it finds the successor node.
		{
			while (found == false)
			{
				parentNode = currentNode->parent_Node;
				if (parentNode->right != NULL)
				{
					if (parentNode->right == currentNode)
					{
						found = true;
						cout << parentNode->key << endl;
						break;
					}
				}
				if (parentNode->parent_Node != NULL)
				{
					currentNode = currentNode->parent_Node;
					parentNode = parentNode->parent_Node;
				}
				else if (parentNode->parent_Node == NULL)
				{
					cout << endl;
					break;
				}

			}
		}
	}
	if (exist == false) // user input doesn't exist in the tree, print a blank line
	{
		cout << endl;
	}
}

void BinarySearchTree::list()
/*
	this method uses inorder traversal to create a list of all nodes in the tree
	if there are no nodes in the tree the output is then represented by a blank
	line.
*/
{
	if (root == NULL)
	{
		cout << "" <<  endl;
		return;
	};
		Node* currentNode;
		currentNode = root;
		int i = 1;
		cout << "Set Contains: " ;
		inOrderTraversal(currentNode, i);
}

void BinarySearchTree::inOrderTraversal(Node* currentNode, int i)
/*
evaluates every node and its children recursivly.
	works its way from left to right to print the nodes
	in ascending value order. a -> z, and 1 -> 9.
*/
{
	
	//return;
	if (currentNode != NULL)
	{
		if (currentNode->left)
			inOrderTraversal(currentNode->left, ++i);
		if (i != 1) {
			cout << " ";
		}
		cout << "(" << i << ")" << currentNode->key + " " << currentNode->count;
		if (currentNode->right)
			inOrderTraversal(currentNode->right, ++i);
	}
	else return;
}

void BinarySearchTree::max()
/*
	the max method finds the node with the highest value in the tree.
	if the tree doesn't exist, then prints a blankspace.
*/
{
	bool exists = false;
	struct Node* currentNode;

	if (root == NULL)
		cout << endl;
	else
	{
		currentNode = root;
		while (currentNode->right)
			currentNode = currentNode->right;
		cout << currentNode->key << " " << currentNode->count << endl;
	}
};

void BinarySearchTree::help()
/* this method shows shows the command inputs available
	for the Binary search tree
*/
{

	cout << "insert <string>\n" << "delete <string>\n" << "min\n" << "max\n"
		<< "search <string>\n" <<"parent <string>\n" <<"child <string>\n" << "next <string>\n" << "previous <string>\n" << "list\n" << "quit\n";
}

string toLowerCase(string command)

{
	for (char& i : command)        //for each letter in the string.
	{
		if (i >= 'A' && i <= 'Z') //true if the letter is any capital letter.
			i = i + 32;          //adds 32 to its ascii value to get its lowercase counterpart.
	}
	return command;
};

