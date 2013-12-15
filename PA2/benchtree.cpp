#include "BST.hpp"
#include "RST.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>
#include "countint.hpp"
using namespace std;

void invalidMessage()
{
    printf("Invalid command line arguments.\nParameter 1: 'bst', 'rst' or 'set'.\nParameter 2: 'sorted' or 'shuffled.'\n");
    printf("Parameter 3: Integer N as powers of 2.\nParameter 4: running times R.\n");
}

int main(int argc, char** argv)
{
    //verify the validation of the arguments
    if (argc != 5) {
        invalidMessage();
        return -1;
    }
    
    BST<countint> *customBST;
    set<countint> standardTree;
    string treeType(argv[1]);
    
    if (treeType != "bst" && treeType != "rst" && treeType != "set") {
        invalidMessage();
        return -1;
    }
    
    bool sorted;
    string st(argv[2]);
    if (st == "sorted") {
        sorted = true;
    }
    else if (st == "shuffled") {
        sorted = false;
    }
    else {
        invalidMessage();
        return -1;
    }
    int N = atoi(argv[3]);
    int R = atoi(argv[4]);
    
    srand((unsigned)time(0));
    cout << "# Benchmarking average number of comparisons for successful find"<< endl;
    cout << "# Data structure: " << treeType << endl;
    cout << "# Data: " << "st" << endl;
    cout << "# N is powers of 2, minus 1, from 1 to " << N << endl;
    cout << "# Averaging over " << R << " runs for each N" << endl;
    cout << "#" << endl;
    cout << "#" << "\t\t" << "avgcomps" << "\t" << "stdev" << endl;
    
    for (int j = 1; j < N; j<<=1, ++j) {
        vector<countint> v;
        v.clear();
        for (int i = 0; i < j; ++i) {
            v.push_back(i);
        }
        
        if (!sorted) {
            random_shuffle(v.begin(), v.end());
        }
        
        vector<countint>::iterator vit = v.begin();
        vector<countint>::iterator ven = v.end();
        
        //Total average number of comparisons
        double tavgcomps = 0;
        //Total squares of average numbers of comparisons
        double tsavgcomps = 0;
        //Compute the standard deviation: doing R runs for a particular N
        
        for (int i = 0; i < R; ++i) {
            if (treeType == "bst") {
                customBST = new BST<countint>();
            }
            else if (treeType == "rst") {
                customBST = new RST<countint>();
            }
            else if (treeType == "set") {
                standardTree.clear();
            }

            //insert nodes from vector
            if (treeType == "bst" || treeType == "rst") {
                for (vit = v.begin(); vit != ven; ++vit) {
                    customBST->insert(*vit);
                }
            }
            else {
                for (vit = v.begin(); vit != ven; ++vit) {
                    standardTree.insert(*vit);
                }
            }
            
            countint::clearcount();
            for (vit = v.begin(); vit != ven; vit++) {
                if (treeType == "bst" || treeType == "rst") {
                    customBST->find(*vit);
                }
                else {
                    standardTree.find(*vit);
                }
            }
            //For each run i, compute the average number of comparisons for a successful find
            double avgcomps = countint::getcount()/(double)j;
            //Total average numbers of comparisons of i runs
            tavgcomps += avgcomps;
            //Total squares of the average numbers of comparisons of i runs
            tsavgcomps += (avgcomps * avgcomps);
            
            if (treeType == "rst" || treeType == "bst") {
                delete customBST;
            }
        }
        //Overall average number of comparisons
        double oavgcomps = tavgcomps / (double)R;
        //Overall squared average number of comparisons
        double oavgscomps = tsavgcomps / (double)R;
        //Standard deviation;
        double stdev = sqrt(fabs(oavgscomps - oavgcomps*oavgcomps)); //use fabs to insure that sqrt accepts a non-positive value
        if (stdev < 0.000001) { //if the stdev is small enough we take it as 0
            stdev = 0;
        }
        cout << j << "\t\t" << oavgcomps <<  "\t\t" << stdev << endl;
    }
}