/*
        Mark Koszykowski
        ECE365 - DSA II
        Programming Assignment 3
*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include "heap.h"
#include <list>
#include <string>

class graph {
        struct edge;
        struct node;
        public:
                void makeGraph(const std::string &inFile);
                bool checkHash(const std::string &vertex);
                void dijkstra(const std::string &vertex);
                void makeOut(const std::string &outFile);
        private:
                struct edge {
                        node *dest;
                        int cost;
                };

                struct node {
                        std::string id;
                        int dist;
                        bool known;
                        std::list<edge> adjList;
                        std::list<std::string> shortPath;
                };

                std::list<node> nodeList;
                hashTable encountered;
};

#endif //_GRAPH_H
