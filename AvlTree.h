/*
 * Title: Balanced Search Trees
 * Author: Hasan Alp Caferoglu
 * ID: 22203991
 * Section: 1
 * Assignment: 4
 * Description: AvlTree Header File
 */

#ifndef _AVL_TREE
#define _AVL_TREE

#include "TreeNode.h"
#include <iostream>
using namespace std;

class AvlTree
{
private:
    TreeNode* rootPtr;
public:
    AvlTree();
    ~AvlTree();

    // General Funtions
    int getHeight() const;
    int getHeightHelper(TreeNode* subTreePtr) const;
    int getNodeBalanceFactor(TreeNode* treePtr) const;
    

    // Desired Functions
    void generateTree(const string& fileName);
    void addWord(const string& newItem);
    void printHeight() const;
    void printTotalWordCount() const;
    void printWordFrequencies() const;
    void printMostFrequent() const;
    void printLeastFrequent() const;
    void printStandartDeviation() const;

protected:
    // Helper Functions
    bool constains(const string& anItem) const;
    TreeNode* findNode(TreeNode* subTreePtr, const string& target) const;
    void incrementCount(const string& existingItem);
    void addWordHelper(TreeNode*& treePtr, const string& newItem);

};


#endif