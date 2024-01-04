//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#include "Graph.h"
#include "../DisjointSet.h"
#include "../Queue.h"
#include "../Heap/Heap.h"
#include "../Heap/MinHeap.h"
#include <iostream>

using namespace std;

namespace array{

    Graph::Graph(int vertexCount) : AbstractGraph(vertexCount){
        words = new string[vertexCount];
        edges = new int*[vertexCount];
        for (int i = 0; i < vertexCount; i++){
            edges[i] = new int[vertexCount];
        }
        for (int i = 0; i < vertexCount; i++){
            for (int j = 0; j < vertexCount; j++){
                edges[i][j] = 0;
            }
        }
    }

    Graph::~Graph() {
        for (int i = 0; i < vertexCount; i++){
            delete[] edges[i];
        }
        delete[] edges;
    }

    void Graph::addEdge(int from, int to) {
        edges[from][to] = 1;
        edges[to][from] = 1;
    }

    void Graph::addEdge(int from, int to, int weight) {
        edges[from][to] = weight;
        edges[to][from] = weight;
    }

    // Adds an edge between two vertices identified by their string labels.
    // If either vertex is not found, an error message is printed.
    void Graph::addEdge(string from, string to) {
        int fromIndex = findIndex(from);
        int toIndex = findIndex(to);

        if (fromIndex == -1 || toIndex == -1) {
            cout << "Not found" << endl;
            return;
        }

        addEdge(fromIndex, toIndex);
    }
    // Adds a weighted edge between two vertices identified by their string labels.
    // If either vertex is not found, an error message is printed.
    void Graph::addEdge(string from,string to,int weight){
        int fromIndex = findIndex(from);
        int toIndex = findIndex(to);

        if(fromIndex == -1 || toIndex == -1){
            cout << "Not found" << endl;
            return;
        }

        addEdge(fromIndex,toIndex,weight);
    }
    // Adds a new word to the graph. The word is stored and its index is incremented.
    void Graph::addWord(string word){
        words[lastVertex] = word;
        lastVertex++;
    }
    // Adds a new word to the graph and automatically creates edges to existing words
    // that differ by only one character.
    void Graph::addWordAuto(string word) {
        words[lastVertex] = word;
        lastVertex++;

        for(int i = 0;i<lastVertex;++i){
            string temp = words[i];

            if(temp.length() == word.length()){
                int count = 0;
                for(int j = 0; j < temp.length();++j){
                    if(temp[j] != word[j]){
                        count++;
                    }
                }
                if(count == 1){
                    addEdge(i,lastVertex-1);
                }
            }
        }
    }
    // Finds the index of a word in the graph. Returns -1 if the word is not found.
    int Graph::findIndex(string word){
        for(int i = 0;i<lastVertex;i++){
            if(words[i] == word){
                return i;
            }
        }
        return -1;
    }
    // Performs a Breadth-First Search (BFS) from a source word to a target word.
    // Prints the shortest path between these words if one exists.
    void Graph::BFS(std::string source, std::string target) {
        int sourceIndex = findIndex(source);
        int targetIndex = findIndex(target);

        if(sourceIndex == -1 || targetIndex == -1){
            cout << "Not found" << endl;
            return;
        }

        if(sourceIndex == targetIndex){
            cout << source << " " << target << endl;
            return;
        }
        auto parents = Queue(lastVertex);

        bool *visited = new bool[lastVertex];
        for(int i = 0;i<lastVertex;++i){
            visited[i] = false;
        }

        int *map = new int[lastVertex];
        for(int i =0; i<lastVertex;++i){
            map[i] = -1;
        }

        parents.enqueue(Element(sourceIndex));

        while(!parents.isEmpty()){
            Element element = parents.dequeue();
            int index = element.getData();
            visited[index] = true;

            int neighbourCount = getNeighborCount(index);
            int *neigbors = getNeighbors(index);

            for(int i  =0;i<neighbourCount;++i){
                int neighbor = neigbors[i];
                if(!visited[neighbor]){
                    visited[neighbor] = true;
                    map[neighbor]  =index;

                    if(neighbor == targetIndex){
                        string path;
                        for(int at = targetIndex; at!=-1;at = map[at]){
                            path = words[at] + " " + path;
                        }
                        cout << path << endl;
                        return;
                    }
                    parents.enqueue(Element(neighbor));

                }
            }
            delete[] neigbors;
        }
        delete[] visited;
        delete[] map;
        cout << "Not found" << endl;
    }
    // Performs Dijkstra's algorithm to find the shortest path from a source word to a target word.
    // This method assumes that all edges have the same weight.
    // Prints the shortest path if one exists.
    void Graph::Dijkstra(string source, string target) {
        int sourceIndex = findIndex(source);
        int targetIndex = findIndex(target);

        if (sourceIndex == -1 || targetIndex == -1) {
            cout << "Not found" << endl;
            return;
        }

        if (sourceIndex == targetIndex) {
            cout << source << " " << target << endl;
            return;
        }

        auto parents = Queue(lastVertex);

        bool *visited = new bool[lastVertex];
        for (int i = 0; i < lastVertex; ++i) {
            visited[i] = false;
        }

        int *map = new int[lastVertex];
        for (int i = 0; i < lastVertex; ++i) {
            map[i] = -1;
        }

        parents.enqueue(Element(targetIndex));

        int distance = 1;

        while (!parents.isEmpty()) {
            Element element = parents.dequeue();
            int index = element.getData();
            visited[index] = true;

            int neighborCount = getNeighborCount(index);
            int *neighbors = getNeighbors(index);

            for (int i = 0; i < neighborCount; ++i) {
                int neighbor = neighbors[i];

                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    map[neighbor] = distance;

                    parents.enqueue(Element(neighbor));
                }
            }

            delete[] neighbors;
            distance++;
        }

        if (map[sourceIndex] != -1) {
            string path = source;

            while (sourceIndex != targetIndex) {
                int min = INT_MAX;
                int minIndex = -1;

                int neighborCount = getNeighborCount(sourceIndex);
                int *neighbors = getNeighbors(sourceIndex);
                for (int i = 0; i < neighborCount; ++i) {
                    int neighbor = neighbors[i];

                    if (map[neighbor] < min) {
                        min = map[neighbor];
                        minIndex = neighbor;
                    }
                }

                path += " " + words[minIndex];
                sourceIndex = minIndex;

                delete[] neighbors;
            }

            cout << path << endl;
        } else {
            cout << "Not found" << endl;
        }

        delete[] visited;
        delete[] map;
    }

    int Graph::getNeighborCount(int vertex) {
        int count = 0;
        for(int i = 0; i<vertexCount;i++){
            if(edges[vertex][i]>0){
                count++;
            }
        }
        return count;
    }

    int *Graph::getNeighbors(int vertex) {
        int *neighbors = new int[getNeighborCount(vertex)];
        int index = 0;
        for(int i = 0;i<vertexCount;i++){
            if(edges[vertex][i]>0){
                neighbors[index] = i;
                index++;
            }
        }
        return neighbors;
    }

    void Graph::connectedComponentDisjointSet() {
        DisjointSet sets = DisjointSet(vertexCount);
        for (int fromNode = 0; fromNode < vertexCount; fromNode++){
            for (int toNode = 0; toNode < vertexCount; toNode++){
                if (edges[fromNode][toNode] > 0){
                    if (sets.findSetRecursive(fromNode) != sets.findSetRecursive(toNode)){
                        sets.unionOfSets(fromNode, toNode);
                    }
                }
            }
        }
    }

    void Graph::depthFirstSearch(bool *visited, int fromNode) {
        for (int toNode = 0; toNode < vertexCount; toNode++){
            if (edges[fromNode][toNode] > 0){
                if (!visited[toNode]){
                    visited[toNode] = true;
                    depthFirstSearch(visited, toNode);
                }
            }
        }
    }

    void Graph::breadthFirstSearch(bool *visited, int startNode) {
        int fromNode;
        Queue queue = Queue(100);
        queue.enqueue( Element(startNode));
        while (!queue.isEmpty()){
            fromNode = queue.dequeue().getData();
            for (int toNode = 0; toNode < vertexCount; toNode++) {
                if (edges[fromNode][toNode] > 0) {
                    if (!visited[toNode]){
                        visited[toNode] = true;
                        queue.enqueue( Element(toNode));
                    }
                }
            }
        }
    }

    Path *Graph::bellmanFord(int source) {
        Path* shortestPaths = initializePaths(source);
        for (int i = 0; i < vertexCount - 1; i++){
            for (int fromNode = 0; fromNode < vertexCount; fromNode++){
                for (int toNode = 0; toNode < vertexCount; toNode++){
                    int newDistance = shortestPaths[fromNode].getDistance() + edges[fromNode][toNode];
                    if (newDistance < shortestPaths[toNode].getDistance()){
                        shortestPaths[toNode].setDistance(newDistance);
                        shortestPaths[toNode].setPrevious(fromNode);
                    }
                }
            }
        }
        return shortestPaths;
    }

    Path *Graph::dijkstra(int source) {
        Path* shortestPaths = initializePaths(source);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert( HeapNode(shortestPaths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            for (int toNode = 0; toNode < vertexCount; toNode++){
                int newDistance = shortestPaths[fromNode].getDistance() + edges[fromNode][toNode];
                if (newDistance < shortestPaths[toNode].getDistance()){
                    int position = heap.search(toNode);
                    heap.update(position, newDistance);
                    shortestPaths[toNode].setDistance(newDistance);
                    shortestPaths[toNode].setPrevious(fromNode);
                }
            }
        }
        return shortestPaths;
    }

    int **Graph::floydWarshall() {
        int** distances;
        distances = new int*[vertexCount];
        for (int i = 0; i < vertexCount; i++){
            distances[i] = new int[vertexCount];
            for (int j = 0; j < vertexCount; j++){
                distances[i][j] = edges[i][j];
            }
        }
        for (int k = 0; k < vertexCount; k++){
            for (int i = 0; i < vertexCount; i++){
                for (int j = 0; j < vertexCount; j++){
                    int newDistance = distances[i][k] + distances[k][j];
                    if (newDistance < distances[i][j]){
                        distances[i][j] = newDistance;
                    }
                }
            }
        }
        return distances;
    }

    Edge *Graph::edgeList(int &edgeCount) {
        Edge* list;
        edgeCount = 0;
        for (int i = 0; i < vertexCount; i++){
            for (int j = 0; j < vertexCount; j++){
                if (edges[i][j] > 0){
                    edgeCount++;
                }
            }
        }
        list = new Edge[edgeCount];
        int index = 0;
        for (int i = 0; i < vertexCount; i++){
            for (int j = 0; j < vertexCount; j++){
                if (edges[i][j] > 0){
                    list[index] = Edge(i, j, edges[i][j]);
                    index++;
                }
            }
        }
        return list;
    }

    void Graph::prim() {
        Path* paths = initializePaths(0);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(paths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            for (int toNode = 0; toNode < vertexCount; toNode++){
                if (paths[toNode].getDistance() > edges[fromNode][toNode]){
                    int position = heap.search(toNode);
                    heap.update(position, edges[fromNode][toNode]);
                    paths[toNode].setDistance(edges[fromNode][toNode]);
                    paths[toNode].setPrevious(fromNode);
                }
            }
        }
    }

}
