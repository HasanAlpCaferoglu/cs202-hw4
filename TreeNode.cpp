/*
 * Title: Balanced Search Trees
 * Author: Hasan Alp Caferoglu
 * ID: 22203991
 * Section: 1
 * Assignment: 4
 * Description: TreeHode Implementation File
 */

#include "TreeNode.h"
 

TreeNode::TreeNode():count(0), balanceFactor(0), height(0), leftChildPtr(nullptr), rightChildPtr(nullptr)
{
}

TreeNode::TreeNode(const string& anItem):count(1), item(anItem), balanceFactor(0), height(1), leftChildPtr(nullptr), rightChildPtr(nullptr)
{
}

TreeNode::~TreeNode()
{
}

// Get-Set Methods

void TreeNode::setItem(const string& anItem){
    item = anItem;
    count = 1;
}

string TreeNode::getItem() const{
    return item;
}

int TreeNode::getCount() const{
    return count;
}

TreeNode* TreeNode::getLeftChildPtr() const{
    return leftChildPtr;
}

TreeNode* TreeNode::getRightChildPtr() const{
    return rightChildPtr;
}

void TreeNode::setLeftChildPtr(TreeNode* leftPtr){
    leftChildPtr = leftPtr;
}

void TreeNode::setRightChildPtr(TreeNode* rightPtr){
    rightChildPtr = rightPtr;
}

int TreeNode::getBalanceFactor() const{
    return balanceFactor;
} 

void TreeNode::setBalanceFactor(const int newBalanceFactor){
    balanceFactor = newBalanceFactor;
}

void TreeNode::incrementBalanceFactor(){
    balanceFactor++;
}

void TreeNode::decrementBalanceFactor(){
    balanceFactor--;
}

int TreeNode::getHeight() const{
    return height;
}

void TreeNode::setHeight(const int newHeight){
    height = newHeight;
}

void TreeNode::incrementHeight(){
    height++;
}

void TreeNode::decrementHeight(){
    height--;
}
// Other Member Functions

void TreeNode::increaseCount(){
    count++;
}

bool TreeNode::isLeaf() const{
    if(leftChildPtr == nullptr && rightChildPtr == nullptr)
        return true;
    else;
        return false;
}




