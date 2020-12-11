/*
        Mark Koszykowski
        ECE365 - DSA II
        Programming Assigment 3
*/

#include "graph.h"
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {
        string inFile, outFile, vertex;
        clock_t start, end;
        graph myGraph;

        cout << "Enter name of graph file: ";
        cin >> inFile;
        myGraph.makeGraph(inFile);

        do {
                cout << "Enter a valid vertex id for the starting vertex: ";
                cin >> vertex;
        }while(!myGraph.checkHash(vertex));

        start = clock();
        myGraph.dijkstra(vertex);
        end = clock();

        cout << fixed << setprecision(3);
        cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << (float)(end - start) / CLOCKS_PER_SEC << endl;
        cout << "Enter name of output file: ";
        cin >> outFile;

        myGraph.makeOut(outFile);
        return 0;
}
