/*
        Mark Koszykowski
        ECE365 - DSA II
        Programming Assignment 3
*/

#include "graph.h"
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

void graph::makeGraph(const string &inFile) {
        ifstream graphFile (inFile);
        string begin, end, cost, line;
        node *beginNode, *endNode;
        
        while(getline(graphFile, line)) {
                istringstream iss (line);
                iss >> begin >> end >> cost;
                node temp;
                
                if(!(encountered.contains(begin))) {
                        temp.id = begin;
                        temp.dist = INT_MAX;
                        temp.known = false;
                        
                        nodeList.push_back(temp);
                        encountered.insert(begin, &nodeList.back());
                }
                beginNode = static_cast<node*>(encountered.getPointer(begin, nullptr));
                
                if(!(encountered.contains(end))) {
                        temp.id = end;
                        temp.dist = INT_MAX;
                        temp.known = false;

                        nodeList.push_back(temp);
                        encountered.insert(end, &nodeList.back());
                }
                endNode = static_cast<node*>(encountered.getPointer(end, nullptr));
                
                edge edge;
                edge.dest = endNode;
                edge.cost = stoi(cost);
                beginNode->adjList.push_back(edge);
        }
        graphFile.close();
}

bool graph::checkHash(const string &vertex) {
        return encountered.contains(vertex);
}

void graph::dijkstra(const string &vertex) {
        node *start = static_cast<node*>(encountered.getPointer(vertex, nullptr));

        heap distHeap(nodeList.size());

        start->dist = 0;
        start->shortPath.push_back(vertex);
        for(list<node>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
                distHeap.insert(it->id, it->dist, &(*it));
        }

        node *tempNode = nullptr;
        while(!distHeap.deleteMin(nullptr, nullptr, &tempNode)) {
                tempNode->known = true;
                for(list<edge>::iterator it = tempNode->adjList.begin(); it != tempNode->adjList.end(); it++) {
                        if(!it->dest->known && tempNode->dist != INT_MAX && (tempNode->dist + it->cost < it->dest->dist)) {
                                it->dest->shortPath.assign(tempNode->shortPath.begin(), tempNode->shortPath.end());
                                it->dest->shortPath.push_back(it->dest->id);

                                it->dest->dist = it->cost + tempNode->dist;
                                distHeap.setKey(it->dest->id, it->dest->dist);
                        }
                }
        }
}

void graph::makeOut(const string &outFile) {
        ofstream shortFile (outFile);
        for(list<node>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
                shortFile << it->id << ": ";

                if(it->shortPath.empty()) {
                        shortFile << "NO PATH" << endl;
                }
                else {
                        shortFile << it->dist << " [";
                        for(list<string>:: iterator sit = it->shortPath.begin(); sit != it->shortPath.end(); sit++) {
                                shortFile << *sit;
                                if(next(sit, 1) != it->shortPath.end()) {
                                        shortFile << ", ";
                                }
                        }
                        shortFile << "]" << endl;
                }
        }
        shortFile.close();
}
