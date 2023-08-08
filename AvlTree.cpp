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
#include <cmath>
#include <vector>
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

    string aWord;

    while(inFile >> aWord){
        int startPos = 0;
        int endPos = 1;

        while(startPos < aWord.size()){
            // get the first non-punct char 
            while( ispunct(aWord[startPos]) && startPos < aWord.size() ){
                startPos++;
            }
            
            endPos = startPos+1;   // set endPost
            // get the positon of a char upto a punctionation
            while( !ispunct(aWord[endPos]) && endPos < aWord.size()){
                endPos++;
            }
            
            string wordToBeAdded = aWord.substr(startPos, endPos-startPos); // Extract the substring
            // convert to lowercase
            int length = endPos-startPos;
            for(int i = 0; i < length; i++){
                wordToBeAdded[i] = tolower(wordToBeAdded[i]);
            }
            startPos = endPos+1;    //update the startPos for the next possible word

            if(!wordToBeAdded.empty()){
                addWord(wordToBeAdded); // addition of the word to the AVL tree
            } 
        }
    }
}

void AvlTree::generateOutputFiles(const string& outputFileName1, const string& outputFileName2){
    // Output file names
    string wordFreqFileName = "wordfreqs.txt";
    string statisticsFileName = "statistics.txt";

    // Open the output files
    ofstream outFile1(outputFileName1);
    ofstream outFile2(outputFileName2);

    // check if the files are open
    if (!outFile1.is_open() || !outFile2.is_open()) {
        cout << "Error: Unable to open the output files." << endl;
        return;
    }

    // Close the output files
    outFile1.close();
    outFile2.close();

}

void AvlTree::addWord(const string& newItem){
    if(constains(newItem))
        incrementCount(newItem);
    else
        addWordHelper(rootPtr, newItem);
}

void AvlTree::printHeight(const string& fileName) const{
    // Open the output files
    ofstream statisticsFile(fileName, std::ios::app);
    // check if the files are open
    if (!statisticsFile.is_open()) {
        cout << "Error: Unable to open the output file " << fileName << endl;
        return;
    }

    int treeHeight = getTreeHeight();
    statisticsFile << "Tree Height: " << treeHeight << endl;

    // Close the output files
    statisticsFile.close();

}

void AvlTree::printTotalWordCount(const string& fileName) const{
    // Open the output files
    ofstream statisticsFile(fileName, std::ios::app);
    // check if the files are open
    if (!statisticsFile.is_open()) {
        cout << "Error: Unable to open the output file " << fileName << endl;
        return;
    }

    int totalWordCount = getNumberOfNodesHelper(rootPtr);
    statisticsFile << "Total Word Count: " << totalWordCount << endl;

    // Close the output files
    statisticsFile.close();

}

void AvlTree::printWordFrequencies(const string& fileName) const{
    inorderTraverse(printWordToFile, fileName);
}

void AvlTree::printMostFrequent(const string& fileName) {
    int maxCount = rootPtr->count;              // initial assignment
    string mostFreqString = rootPtr->item;      // initial assignment

    // Open the output files
    ofstream statisticsFile(fileName, std::ios::app);
    // check if the files are open
    if (!statisticsFile.is_open()) {
        cout << "Error: Unable to open the output file " << fileName << endl;
        return;
    }

    inorderTraverseForMinMax(findMaxFrequent, mostFreqString, maxCount);
    vector<string> allMostFreqStrings;
    inorderTraverseOtherMinMax(findOtherMaxMinFrequentWords, maxCount, allMostFreqStrings);

    if(allMostFreqStrings.empty()){
        statisticsFile << "Most Frequent: " << mostFreqString << " " << maxCount << endl;
    } else{
        statisticsFile << "Most Frequent: ";
        for (int i = 0; i != allMostFreqStrings.size(); ++i)
            statisticsFile << allMostFreqStrings[i] << " " << maxCount << " ";
        statisticsFile << endl;
    }

    // Close the output files
    statisticsFile.close();
}

void AvlTree::printLeastFrequent(const string& fileName) {
    int minCount = rootPtr->count;              // initial assignment
    string leastFreqString = rootPtr->item;     // initial assignment

    // Open the output files
    ofstream statisticsFile(fileName, std::ios::app);
    // check if the files are open
    if (!statisticsFile.is_open()) {
        cout << "Error: Unable to open the output file " << fileName << endl;
        return;
    }

    inorderTraverseForMinMax(findLeastFrequent, leastFreqString, minCount);
    vector<string> allLeastFreqStrings;
    inorderTraverseOtherMinMax(findOtherMaxMinFrequentWords, minCount, allLeastFreqStrings);

    if(allLeastFreqStrings.empty()){
        statisticsFile << "Least Frequent: " << leastFreqString << " " << minCount << endl;
    } else{
        statisticsFile << "Least Frequent: ";
        for (int i = 0; i != allLeastFreqStrings.size(); ++i)
            statisticsFile << allLeastFreqStrings[i] << " " << minCount << " ";
        statisticsFile << endl;
    }

    // Close the output files
    statisticsFile.close();

}

void AvlTree::printStandartDeviation(const string& fileName){
    // Open the output files
    ofstream statisticsFile(fileName, std::ios::app);
    // check if the files are open
    if (!statisticsFile.is_open()) {
        cout << "Error: Unable to open the output file " << fileName << endl;
        return;
    }

    int itemCount = getNumberOfNodesHelper(rootPtr);
    int* countArray = new int[itemCount];
    int position = 0;
    inorderTraverseForStd(putCountsInArray, countArray, position);

    float sum = 0;
    for(int i = 0; i < itemCount; i++){
        sum += countArray[i];
    }
    float mean = sum / itemCount;
    
    float sumOfDifferenceSquare = 0;
    for(int i = 0; i < itemCount; i++){
        sumOfDifferenceSquare += pow((countArray[i] - mean), 2);
    }

    float standardDeviation = sqrt(sumOfDifferenceSquare / itemCount);
    statisticsFile << "Standard Deviation: " << standardDeviation << endl;

    // delete the array
    delete[] countArray;
    countArray = nullptr;

    // Close the output files
    statisticsFile.close();
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
    else if(nodeBalanceFactor < -1 && newItem > treePtr->rightChildPtr->item){
        leftRotate(treePtr);
    }
    // left-right case
    else if(nodeBalanceFactor > 1 && newItem > treePtr->leftChildPtr->item){
        leftRightRotate(treePtr);
    }
    // right-left case
    else if(nodeBalanceFactor < -1 && newItem < treePtr->rightChildPtr->item){
        rightLeftRotate(treePtr);
    }
    // if there is no imbalance just update the height
    else{
        updateNodeHeight(treePtr);
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
// Traversal Functions
//------------------------------------------------------------
void AvlTree::inorderTraverse(FunctionType visit, const string& fileName) const{
    inorderHelper(rootPtr, visit, fileName);
} // end inorderTraverse

void AvlTree::inorderHelper(TreeNode* treePtr, FunctionType visit, const string& fileName) const{
    if(treePtr != nullptr){
        inorderHelper(treePtr->leftChildPtr, visit, fileName);
        string theNodeItem = treePtr->item;
        int theItemCount = treePtr->count;
        visit(fileName, theNodeItem, theItemCount);
        inorderHelper(treePtr->rightChildPtr, visit, fileName);
    } // end if
} // end inorderHelper

void AvlTree::inorderTraverseForMinMax(FunctionType2 visitNode, string& theString, int& theCount) {
    inorderHelperForMinMax(rootPtr, visitNode, theString, theCount);
} // end inorderTraverseForMinMax

void AvlTree::inorderHelperForMinMax(TreeNode* treePtr, FunctionType2 visitNode, string& theString, int& theCount) {
    if(treePtr != nullptr){
        inorderHelperForMinMax(treePtr->leftChildPtr, visitNode, theString, theCount);
        string theNodeItem = treePtr->item;
        int theItemCount = treePtr->count;
        visitNode(theNodeItem, theItemCount, theString, theCount);
        inorderHelperForMinMax(treePtr->rightChildPtr, visitNode, theString, theCount);
    } // end if
} // end inorderHelperForMinMax

void AvlTree::inorderTraverseOtherMinMax(FunctionType4 visit, int& countMinMax, vector<string>& wordsMinMax ){
    inorderHelperOtherMinMax(rootPtr, visit, countMinMax, wordsMinMax);
}

void AvlTree::inorderHelperOtherMinMax(TreeNode* treePtr, FunctionType4 visit, int& countMinMAx, vector<string>& wordsMinMax){
    if(treePtr != nullptr){
        inorderHelperOtherMinMax(treePtr->leftChildPtr, visit, countMinMAx, wordsMinMax);
        string theNodeItem = treePtr->item;
        int theItemCount = treePtr->count;
        visit(theNodeItem, theItemCount, countMinMAx, wordsMinMax);
        inorderHelperOtherMinMax(treePtr->rightChildPtr, visit, countMinMAx, wordsMinMax);
    }
}

void AvlTree::inorderTraverseForStd(FunctionType3 visit, int*& anArray, int& position){
    inorderHelperForStd(rootPtr, visit, anArray, position);
} // end inorderTraverseForStd

void AvlTree::inorderHelperForStd(TreeNode* treePtr, FunctionType3 visit, int*& anArray, int& position){
    if(treePtr != nullptr){
        inorderHelperForStd(treePtr->leftChildPtr, visit, anArray, position);
        int theItemCount = treePtr->count;
        visit(anArray, position, theItemCount);
        inorderHelperForStd(treePtr->rightChildPtr, visit, anArray, position);
    } // end if
} // end inorderHelperForStd


//------------------------------------------------------------ 
// Global Functions Functions
//------------------------------------------------------------
void displayNodeProperties(string& anItem, int& count){
    cout << "\"" << anItem << "\" appears " << count << " time(s)" << endl;
}

void printWordToFile(const string& fileName, string& anItem, int& count){
    // Open the output files
    ofstream wordFreqFile(fileName, std::ios::app);
    // check if the files are open
    if (!wordFreqFile.is_open()) {
        cout << "Error: Unable to open the output file " << fileName << endl;
        return;
    }
    // print word and its count
    wordFreqFile << anItem << " " << count << endl;
    // close file
    wordFreqFile.close();
}

void findMaxFrequent(string& anItem, int& count, string& mostFreqString, int& maxCount ){
    if(count > maxCount){
        maxCount = count;
        mostFreqString = anItem;
    }
}

void findLeastFrequent( string& anItem, int& count, string& leastFreqString, int& minCount ){
    if(count < minCount){
        minCount = count;
        leastFreqString = anItem;
    }
}

void findOtherMaxMinFrequentWords(string& anItem, int& count, int& countMinMax, vector<string>& wordsMinMax ){
    if(count == countMinMax)
        wordsMinMax.push_back(anItem);
}

void putCountsInArray( int*& anArray, int& position, int& count){
    anArray[position] = count;
    position++;
}