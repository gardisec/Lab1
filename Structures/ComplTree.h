#ifndef COMPLTREE_H
#define COMPLTREE_H

#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include "arr.h"
#include "MyQueue.h"

using namespace std;

struct Tree {
    string key;
    Tree* left;
    Tree* right;

    explicit Tree(string  val) : key(std::move(val)), left(nullptr), right(nullptr) {}

    void insertToTree(const string&);
    void printTree();
};

bool search(const string& value);
bool isCompleteBinaryTree(Tree* root);
Tree* treeFromString(const string& input);
string treeToString(Tree* root);

#endif