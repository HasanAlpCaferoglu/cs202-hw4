/*
 * Title: Balanced Search Trees
 * Author: Hasan Alp Caferoglu
 * ID: 22203991
 * Section: 1
 * Assignment: 4
 * Description: main file
 */

#include "AvlTree.h"
#include <iostream>
#include <string>
using namespace std;


int main( int argc, char** argv ) {

    AvlTree tree;
    string fileName(argv[1]);

    tree.generateTree(fileName);
    tree.printHeight();
    tree.printTotalWordCount();
    // tree.printWordFrequencies();
    tree.printMostFrequent();
    tree.printLeastFrequent();

   return 0;
}