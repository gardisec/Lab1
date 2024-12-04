#ifndef COMPLTREE_H
#define COMPLTREE_H

#include "arr.h"
#include<iostream>
using namespace std;

struct TreeNode
{
    int data;           //field to store the value of the element
    TreeNode *left;
    TreeNode *right;  //link field to the child node

    TreeNode() = default;
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

struct  CBTree
{
    TreeNode *root;
    TreeNode *temp;   //root - Root pointer to the ROOT of the Tree, temp - Temporary node pointer  pointing to the node to be inserted

    CBTree() : root(nullptr), temp(nullptr) {}
    CBTree(TreeNode* r) : root(), temp(nullptr) {}

        inline TreeNode* get_root(){
          return root;
        }

        void accept(int, TreeNode*);              //method to accept values to be inserted
        TreeNode* insert(TreeNode*,TreeNode*);  //method to insert node in the binary tree
        void display(TreeNode*);        //method to display the tree in InOrder traversal

        int height(TreeNode*);          //method to get height of a given node
        int balance(TreeNode*);             /*method to get the balance factor of a given node
                                    [Balance Factor = Height of Left Sub-Tree - Height of Right Sub-Tree] */
        bool check(TreeNode*);         //method to check any node with balance factor > 0
};
string treeToString(TreeNode* tree);
CBTree fromString(string str);


#endif //COMPLTREE_H
