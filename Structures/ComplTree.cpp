#include "ComplTree.h"
#include "queue.h"
#include "arr.h"
bool CBTree :: check(TreeNode *root)
{
    //traversing the nodes of the subtree to check any node with balance factor > 0
    if(root == nullptr)
        return false;
    bool x = check(root->left);
        if(balance(root))
            return true;
    bool y = check(root->right);

    return (x || y);    //If any node present with balance factor > 0
}

void CBTree :: accept(int value, TreeNode* root) {

    temp->data = value;
    root = insert(root, temp);

}

TreeNode* CBTree :: insert(TreeNode* root,TreeNode* temp) {
    //Inserting a node in the tree
    if(root == nullptr)
        return temp;
    else if(balance(root)==0 && check(root->right))  //Condition to insert node in the right sub-tree
        root->right = insert(root->right,temp);
    else if(balance(root)==0)                      //condition to insert node in the left sub-tree
        root->left = insert(root->left,temp);
    else if(balance(root)==1 && check(root->left))   //condition to insert node in the left sub-tree
        root->left = insert(root->left,temp);
    else if(balance(root)==1)
        root->right = insert(root->right,temp);      //condition to insert node in right sub-tree

    return root;
}

void CBTree :: display(TreeNode *root)
{
    //Traversing the tree in InOrder way using recursion
    if(root == NULL)
        return;
    display(root->left);
    cout<<root->data<<"\t";
    display(root->right);
}
int CBTree :: height(TreeNode *r)
{
    if(r == NULL)
        return 0;
    else
    {
        int lheight = height(r->left)+1;
        int rheight = height(r->right)+1;

    return (lheight > rheight) ? lheight : rheight; //returns maximum height
    }
}

int CBTree :: balance(TreeNode *r)
{
        if(r == NULL)
            return 0;
        int lHeight = height(r->left)+1;
        int rHeight = height(r->right)+1;

        return (lHeight - rHeight); //[Balance Factor = Height of Left Sub-Tree - Height of Right Sub-Tree]
}

string treeToString(TreeNode* root) {
    if (!root) {
        return "";
    }
    arr<int> result;
    result.push_back(root->data);
    treeToString(root->left);
    treeToString(root->right);

}

CBTree fromString(string str) {
    arr<string> tempPairs = splitToArr(str, ",");
    TreeNode* root = new TreeNode();
    CBTree tree;
    tree.accept(stoi(tempPairs.data[0]), root);
    for (int i = 1; i < tempPairs.size; i++) {
        arr<string> temp = splitToArr(tempPairs.data[i], " ");
        for (int j = 0; j < temp.size; j++) {
            if (temp.size % 2 == 1 && temp.size != j - 1) {
                tree.accept(stoi(temp.data[j]), root->left);
                tree.accept(stoi(temp.data[j + 1]), root->right);
            } else {
                tree.accept(stoi(temp.data[j]), root->left);
            }
        }

    }





}



