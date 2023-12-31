/*
 * Title: Balanced Search Trees
 * Author: Hasan Alp Caferoglu
 * ID: 22203991
 * Section: 1
 * Assignment: 4
 * Description: TreeHode Header File
 */

#ifndef _TREE_NODE
#define _TREE_NODE

#include <string>
using namespace std;

class TreeNode
{
private:
    string item;
    int count;
    int height; // 1 if the node has no child
    TreeNode* leftChildPtr;
    TreeNode* rightChildPtr;
public:
    TreeNode();
    TreeNode(const string& anItem);
    ~TreeNode();

    // Get-Set Methods
    void setItem(const string& anItem);
    string getItem() const;
    int getCount() const;

    TreeNode* getLeftChildPtr() const;
    TreeNode* getRightChildPtr() const;
    void setLeftChildPtr( TreeNode* leftPtr);
    void setRightChildPtr( TreeNode* rightPtr);

    int getHeight() const;
    void setHeight(const int newHeight);

    // Other Member Functions
    void increaseCount();
    bool isLeaf() const;

    // friend class - giving permission to access the private data members to the friend class
    friend class AvlTree;
};


#endif