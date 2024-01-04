//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#ifndef DATASTRUCTURES_CPP_GRAPH_H
#define DATASTRUCTURES_CPP_GRAPH_H

#include "string"
#include "../../General/AbstractGraph.h"
#include "../../List/Graph/Edge.h"
using namespace std;
namespace array{
    class Graph : public AbstractGraph{
    private:
        int** edges;
        string* words;
        int lastVertex = 0;
        int findIndex(string word);
    public:
        explicit Graph(int vertexCount);
        ~Graph();
        void addEdge(int from, int to);
        void addEdge(int from, int to, int weight);
        void connectedComponentDisjointSet();
        Path* bellmanFord(int source);
        Path* dijkstra(int source);
        int** floydWarshall();
        void prim();

        int* getNeighbors(int vertex);
        int getNeighborCount(int vertex);
        void addWord(string word);
        void addWordAuto(string word);
        void BFS(string source,string target);
        void Dijkstra(string source,string target);
        void addEdge(string from,string to);
        void addEdge(string from,string to,int weight);
    protected:
        void depthFirstSearch(bool* visited, int fromNode) override;
        void breadthFirstSearch(bool* visited, int startNode) override;
        Edge* edgeList(int& edgeCount) override;
    };

}


#endif //DATASTRUCTURES_CPP_GRAPH_H
