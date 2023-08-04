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


AvlTree::AvlTree(): rootPtr(nullptr) {
}

AvlTree::~AvlTree(){

}

// General Functions
int AvlTree::getHeight() const{
    return getHeightHelper(rootPtr);
} // end getHeight

int AvlTree::getHeightHelper(TreeNode* subTreePtr) const{
    if(subTreePtr == nullptr)
        return 0;
    else
        return 1 + max(getHeightHelper(subTreePtr->leftChildPtr), getHeightHelper(subTreePtr->rightChildPtr));
}

int AvlTree::getNodeBalanceFactor(TreeNode* treePtr) const{
    return getHeightHelper(treePtr->leftChildPtr) - getHeightHelper(treePtr->rightChildPtr);
}

// Desired Functions

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
            for (char& c : word) {
                c = std::tolower(c);
            }
            if (!word.empty()) {
                // add the word to the tree
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
    /* Write Code Here */
}

void AvlTree::printTotalWordCount() const{
    /* Write Code Here */
}

void AvlTree::printWordFrequencies() const{
    /* Write Code Here */
}

void AvlTree::printMostFrequent() const{
    /* Write Code Here */
}

void AvlTree::printLeastFrequent() const{
    /* Write Code Here */
}

void AvlTree::printStandartDeviation() const{
    /* Write Code Here */
}

// Helper Functions
bool AvlTree::constains(const string& anItem) const{
    TreeNode* theNode = findNode(rootPtr, anItem);
    if(theNode == nullptr)
        return false;
    else
        return true;
} // end constains

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

    int currentNodeHight;
    int nodeBalanceFactor;
    if(treePtr->leftChildPtr != nullptr && treePtr->rightChildPtr != nullptr){
        nodeBalanceFactor = treePtr->leftChildPtr->getHeight() - treePtr->rightChildPtr->getHeight();
        currentNodeHight = 1+max(treePtr->leftChildPtr->getHeight(), treePtr->rightChildPtr->getHeight());
    }
    else if(treePtr->leftChildPtr != nullptr){
        nodeBalanceFactor = treePtr->leftChildPtr->getHeight();
        currentNodeHight = 1 + treePtr->leftChildPtr->getHeight();
    }
    else if(treePtr->rightChildPtr != nullptr){
        nodeBalanceFactor = - treePtr->rightChildPtr->getHeight();
        currentNodeHight = 1 + treePtr->rightChildPtr->getHeight();
    }
    else{
        nodeBalanceFactor = 0;
        currentNodeHight = 1;
    }

    treePtr->setHeight(currentNodeHight); // setting current Node Height
    // treePtr->setBalanceFactor(nodeBalanceFactor);

    // left-left case
    if(nodeBalanceFactor > 1 && newItem < treePtr->leftChildPtr->item){

    }

    // right-right case
    if(nodeBalanceFactor < -1 && newItem > treePtr->rightChildPtr->item){

    }

    // left-right case
    if(nodeBalanceFactor > 1 && newItem > treePtr->leftChildPtr->item){

    }

    // right-left case
    if(nodeBalanceFactor < -1 && newItem < treePtr->rightChildPtr->item){

    }


}
