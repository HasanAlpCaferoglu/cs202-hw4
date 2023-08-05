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

// Function prototype for displayNodeProperties and printWordToFile
void displayNodeProperties(string& anItem, int& count);
void printWordToFile(const string& fileName, string& anitem, int& count);
void findMaxFrequent(string& anItem, int& count, string& mostFreqString, int& maxCount );
void findLeastFrequent(string& anItem, int& count, string& leastFreqString, int& minCount );
void putCountsInArray( int*& anArray, int& position, int& count);

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
    void generateOutputFiles(const string& outputFileName1, const string& outputFileName2);
    void addWord(const string& newItem);
    void printHeight(const string& fileName) const;
    void printTotalWordCount(const string& fileName) const;
    void printWordFrequencies(const string& fileName) const;
    void printMostFrequent(const string& fileName);
    void printLeastFrequent(const string& fileName);
    void printStandartDeviation(const string& fileName);

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
    typedef void (*FunctionType)(const string& fileName, string& anItem, int& count);
    void inorderTraverse(FunctionType visit, const string& fileName) const;
    void inorderHelper(TreeNode* treePtr, FunctionType visit, const string& fileName) const;

    typedef void (*FunctionType2)(string& anItem, int& count, string& theString, int& theCount);
    void inorderTraverseForMinMax(FunctionType2 visitNode, string& theString, int& theCount);
    void inorderHelperForMinMax(TreeNode* treePtr, FunctionType2 visitNode, string& theString, int& theCount);

    typedef void (*FunctionType3)(int*& anArray, int& position, int& count);
    void inorderTraverseForStd(FunctionType3 visit, int*& anArray, int& position);
    void inorderHelperForStd(TreeNode* treePtr, FunctionType3 visit, int*& anArray, int& position);

};


#endif