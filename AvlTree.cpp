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

}

void AvlTree::printTotalWordCount() const{

}

void AvlTree::printWordFrequencies() const{

}

void AvlTree::printMostFrequent() const{

}

void AvlTree::printLeastFrequent() const{

}

void AvlTree::printStandartDeviation() const{

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

}

void AvlTree::addWordHelper(TreeNode*& treePtr, const string& newItem){

}

