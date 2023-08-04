/*
 * Title: Balanced Search Trees
 * Author: Hasan Alp Caferoglu
 * ID: 22203991
 * Section: 1
 * Assignment: 4
 * Description: AvlTree Implementation File
 */

#include "AvlTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//------------------------------------------------------------ 
// Constructor and Destructor Section. 
//------------------------------------------------------------
AvlTree::AvlTree(): rootPtr(nullptr) {
}

AvlTree::~AvlTree(){

}

///------------------------------------------------------------ 
// General Functions
//------------------------------------------------------------
int AvlTree::getTreeHeight() const{
    // return getHeightHelper(rootPtr);
    return rootPtr->height;
} // end getHeight

bool AvlTree::constains(const string& anItem) const{
    TreeNode* theNode = findNode(rootPtr, anItem);
    if(theNode == nullptr)
        return false;
    else
        return true;
} // end constains

//------------------------------------------------------------ 
// Desired Functions
//------------------------------------------------------------

void AvlTree::generateTree(const string& fileName){
    fstream inFile(fileName);

    if(!inFile.is_open()){
        cout << "Error openning file: " << fileName << endl;
        return;
    }

    string line;
    
    while(getline(inFile, line)){
        istringstream iss(line);
        string word;

        // Examining the words in the line
        // words are extracted according to whitespaces
        while(iss >> word){
            // Deleting puctuations
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
            // Converting to lower case
            // for (char& c : word) {
            //     c = std::tolower(c);
            // }
            for (size_t i = 0; i < word.size(); ++i) {
                word[i] = std::tolower(word[i]);
            }
            if (!word.empty()) {
                // add the word to the tree
                cout << word << endl;           // DELETE LATER
                addWord(word);
            }
        } 
    }
}

void AvlTree::addWord(const string& newItem){
    if(constains(newItem))
        incrementCount(newItem);
    else
        addWordHelper(rootPtr, newItem);
}

void AvlTree::printHeight() const{
    // cout << rootPtr->item << endl;
    cout << getTreeHeight() << endl;
}

void AvlTree::printTotalWordCount() const{
    int totalWordCount = getNumberOfNodesHelper(rootPtr);
    cout << totalWordCount << endl;
}

void AvlTree::printWordFrequencies() const{
    inorderTraverse(displayNodeProperties);
}

void AvlTree::printMostFrequent() const{
    int maxCount = rootPtr->count;
    string mostFreqString = rootPtr->item;
    cout << mostFreqString << " " << maxCount << endl;
}

void AvlTree::printLeastFrequent() const{
    int minCount = rootPtr->count;
    string leastFreqString = rootPtr->item;
    cout << leastFreqString << " " << minCount << endl;
}

void AvlTree::printStandartDeviation() const{
    /* Write Code Here */
}

//------------------------------------------------------------ 
// Helper Functions 
//------------------------------------------------------------

TreeNode* AvlTree::findNode(TreeNode* subTreePtr, const string& target) const{
    if(subTreePtr == nullptr)
        return nullptr;
    else if(subTreePtr->item == target)
        return subTreePtr;
    else if(subTreePtr->item > target)
        return findNode(subTreePtr->leftChildPtr, target); // search the target in the left subtree
    else
        return findNode(subTreePtr->rightChildPtr, target); // search the target in the right subtree
} // end findNode

int AvlTree::getNumberOfNodesHelper(TreeNode* subTreePtr) const{
    if(subTreePtr == nullptr)
        return 0;
    else
        return 1 + getNumberOfNodesHelper(subTreePtr->leftChildPtr) + getNumberOfNodesHelper(subTreePtr->rightChildPtr); 
} // end getNumberOfNodesHelper

void AvlTree::incrementCount(const string& existingItem){
    TreeNode* theNode = findNode(rootPtr, existingItem);
    theNode->increaseCount();
}

void AvlTree::addWordHelper(TreeNode*& treePtr, const string& newItem){
    if(treePtr==nullptr){
        treePtr =  new TreeNode(newItem);
        return;
    }
    else if(treePtr->item > newItem){
        addWordHelper(treePtr->leftChildPtr, newItem);
    }
    else{
        addWordHelper(treePtr->rightChildPtr, newItem);
    }

    // find the balance factor of the current node
    int nodeBalanceFactor;
    if(treePtr->leftChildPtr != nullptr && treePtr->rightChildPtr != nullptr){
        nodeBalanceFactor = treePtr->leftChildPtr->getHeight() - treePtr->rightChildPtr->getHeight();
    }
    else if(treePtr->leftChildPtr != nullptr){
        nodeBalanceFactor = treePtr->leftChildPtr->getHeight();
    }
    else if(treePtr->rightChildPtr != nullptr){
        nodeBalanceFactor = - treePtr->rightChildPtr->getHeight();
    }
    else{
        nodeBalanceFactor = 0;
    }

    // Examine the imbalance cases
    // left-left case
    if(nodeBalanceFactor > 1 && newItem < treePtr->leftChildPtr->item){
        rightRotate(treePtr);
    }

    // right-right case
    if(nodeBalanceFactor < -1 && newItem > treePtr->rightChildPtr->item){
        leftRotate(treePtr);
    }

    // left-right case
    if(nodeBalanceFactor > 1 && newItem > treePtr->leftChildPtr->item){
        leftRightRotate(treePtr);
    }

    // right-left case
    if(nodeBalanceFactor < -1 && newItem < treePtr->rightChildPtr->item){
        rightLeftRotate(treePtr);
    }

} // end addWordHelper

void AvlTree::updateNodeHeight(TreeNode*& node){  
    if(node->leftChildPtr != nullptr && node->rightChildPtr != nullptr){
        node->height = 1+max(node->leftChildPtr->getHeight(), node->rightChildPtr->getHeight());
    }
    else if(node->leftChildPtr != nullptr){
        node->height = 1 + node->leftChildPtr->getHeight();
    }
    else if(node->rightChildPtr != nullptr){
        node->height = 1 + node->rightChildPtr->getHeight();
    }
    else{
        node->height = 1;
    }
} // end updateNodeHeight

//------------------------------------------------------------ 
// Rotation Functions
//------------------------------------------------------------

void AvlTree::leftRotate(TreeNode*& node){
    TreeNode* p = node->rightChildPtr;
    node->rightChildPtr = p->leftChildPtr;
    updateNodeHeight(node); // update the height of node after its right child changed
    p->leftChildPtr = node;
    updateNodeHeight(p); // update the height of node p after its left child changed
    node = p;

    //update heights

    node->height = 1+max(node->leftChildPtr->getHeight(), node->rightChildPtr->getHeight());
    p->height = 1+max(p->leftChildPtr->getHeight(), p->rightChildPtr->getHeight());

} // end leftRotate

void AvlTree::rightRotate(TreeNode*& node){
    TreeNode* p = node->leftChildPtr;
    node->leftChildPtr = p->rightChildPtr;
    updateNodeHeight(node); // update the height of node after its left child changed
    p->rightChildPtr = node;
    updateNodeHeight(p); // update the height of node p after its right child changed
    node = p;
} // end rightRotate

void AvlTree::leftRightRotate(TreeNode*& node){
    leftRotate(node->leftChildPtr);
    rightRotate(node);
} // end leftRightRotate

void AvlTree::rightLeftRotate(TreeNode*& node){
    rightRotate(node->rightChildPtr);
    leftRotate(node);
} // end rightLeftRotate

//------------------------------------------------------------ 
// Global Functions Functions
//------------------------------------------------------------
void displayNodeProperties(string& anItem, int& count){
    cout << "\"" << anItem << "\" appears " << count << " time(s)" << endl;
}

//------------------------------------------------------------ 
// Traversal Functions
//------------------------------------------------------------
void AvlTree::inorderTraverse(FunctionType visit) const{
    inorderHelper(rootPtr, visit);
} // end inorderTraverse

void AvlTree::inorderHelper(TreeNode* treePtr, FunctionType visit) const{
    if(treePtr != nullptr){
        inorderHelper(treePtr->leftChildPtr, visit);
        string theNodeItem = treePtr->item;
        int theItemCount = treePtr->count;
        visit(theNodeItem, theItemCount);
        inorderHelper(treePtr->rightChildPtr, visit);
    } // end if
} // end inorder


