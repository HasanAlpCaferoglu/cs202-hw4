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
    //------------------------------------------------------------ 
    // Constructor and Destructor Section. 
    //------------------------------------------------------------
    AvlTree();
    ~AvlTree();

    //------------------------------------------------------------ 
    // General Functions
    //------------------------------------------------------------
    int getTreeHeight() const;
    bool constains(const string& anItem) const;

    //------------------------------------------------------------ 
    // Desired Functions
    //------------------------------------------------------------
    void generateTree(const string& fileName);
    void addWord(const string& newItem);
    void printHeight() const;
    void printTotalWordCount() const;
    void printWordFrequencies() const;
    void printMostFrequent() const;
    void printLeastFrequent() const;
    void printStandartDeviation() const;

protected:
    //------------------------------------------------------------ 
    // Helper Functions 
    //------------------------------------------------------------
    TreeNode* findNode(TreeNode* subTreePtr, const string& target) const;
    int getNumberOfNodesHelper(TreeNode* subTreePtr) const;
    void incrementCount(const string& existingItem);
    void addWordHelper(TreeNode*& treePtr, const string& newItem);
    void updateNodeHeight(TreeNode*& node);

    // int getHeightHelper(TreeNode* subTreePtr) const;     // NOT NEEDED
    // int getNodeBalanceFactor(TreeNode* treePtr) const;   // NOT NEEDED

    //------------------------------------------------------------ 
    // Rotation Functions
    //------------------------------------------------------------
    void leftRotate(TreeNode*& node);
    void rightRotate(TreeNode*& node);
    void leftRightRotate(TreeNode*& node);
    void rightLeftRotate(TreeNode*& node);

    //------------------------------------------------------------ 
    // Traversal Functions
    //------------------------------------------------------------
    typedef void (*FunctionType)(string& anItem, int& count);
    void inorderTraverse(FunctionType visit) ;
    void inorderHelper(TreeNode* treePtr, FunctionType visit) ;

};


#endif