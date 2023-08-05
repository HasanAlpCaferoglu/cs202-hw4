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
    cout << "--------------------" << endl;                 // DELETE LATER

    tree.generateTree(fileName);
    // Output file names
    string wordFreqFileName = "wordfreqs.txt";
    string statisticsFileName = "statistics.txt";

    tree.generateOutputFiles(wordFreqFileName, statisticsFileName);
    tree.printTotalWordCount(statisticsFileName);
    tree.printHeight(statisticsFileName);
    tree.printMostFrequent(statisticsFileName);
    tree.printLeastFrequent(statisticsFileName);
    tree.printStandartDeviation(statisticsFileName);
    tree.printWordFrequencies(wordFreqFileName);

   return 0;
}