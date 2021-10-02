/*
___________________________________________________________________________________________

   Code by: Bernard Owusu Sefah
   Course: Non-Linear Data Structures
   Date: Febuary 14, 2020
   Topic: Implementation of a Binary Search Tree
___________________________________________________________________________________________
*/




#include "PreCompiled_Header.h"
#include "BST_Methods.h"
#include <iostream>
#include <string>

// BST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;


int main()
{
    BinarySearchTree tree;
    string command;
    string key;

    cin >> command;
    command = toLowerCase(command);

    while (command != "quit")
    {
        command = toLowerCase(command);
        if (command == "insert")
        {
            cin >> key;
            tree.insert(key);
        }
        if (command == "delete")
        {
            cin >> key;
            tree.remove(key);
        }
        if (command == "search")
        {
            cin >> key;
            tree.search(key);
        }
           if (command == "min")
            {
                
                tree.min();
            }
              if (command == "max")
            {

                tree.max();
            }
            if (command == "next")
            {
                cin >> key;
                tree.next(key);
            }
            if (command == "previous")
            {
                cin >> key;
                tree.previous(key);
            }
            if (command == "list")
            {
                tree.list();
            }
            if (command == "parent")
            {
                cin >> key;
                tree.parent(key);
            }
            if (command == "child")
            {
                cin >> key;
               tree.child(key);
            }
            if (command == "help")
                tree.help();

             

        cin.clear();
        cin >> command;
    }
}
