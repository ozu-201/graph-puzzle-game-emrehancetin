
#include <iostream>
#include <fstream>
#include "string"
#include "../Graph/Graph.h"
#include <vector>
using namespace std;
using namespace array;
bool controlWord(string &word){
    if(word.length() <3 || word.length()>5){
        return false;
    }
    return true;
}

string *read(int count){
    auto* words = new string[count];

    ifstream inputFile;

    inputFile.open("../src/Array/DartPuzzle/file.txt");

    if(!inputFile.is_open()){
        cerr << "Error: Unable to open the file." << endl;
        return words;
    }
    string line;
    int i = 0;
    while(getline(inputFile,line)){
        if(controlWord(line)){
            words[i] = line;
            i++;
        }
    }
    inputFile.close();
    return words;
}

int readCount(){
    ifstream inputFile;

    inputFile.open("../src/Array/DartPuzzle/file.txt");
    if(!inputFile.is_open()){
        cerr << "Error: Unable to open the file." << endl;
        return 0;
    }
    string line;
    int count= 0;
    while(getline(inputFile,line)){
        if (controlWord(line)) count++;
    }
    inputFile.close();
    return count;
}


int main(){
    cout << "Hello world" << endl;

    int count = readCount();
    string *words = read(count);
    auto *graph = new Graph(count);

    for(int i = 0; i < count; i++){
        graph->addWordAuto(words[i]);
    }

    delete[] words;

    //graph->Dijkstra("aaa","abb");
    graph->Dijkstra("aah","aar");

    // ------------------------------------
    // DO THE NECESSARY CHANGES ACCORDING TO YOUR IMPLEMENTATION
    // ------------------------------------
    // Test Case: Adding Edges with One-Letter Difference (3 letter words)
    Graph graph3(4);
    graph3.addWord("cat");
    graph3.addWord("cot");
    graph3.addWord("cog");
    graph3.addWord("dog");

    graph3.addEdge("cat", "cot");

    graph3.addEdge("cot", "cog");
    graph3.addEdge("cog", "dog");


    std::cout << "Test Case: Adding Edges with One-Letter Difference (3 letter words)\n";
    std::cout << "Shortest Path from 'cat' to 'dog' (BFS):\n";
    graph3.BFS("cat", "dog");
    std::cout << "Shortest Path from 'cat' to 'dog' (Dijkstra):\n";
    graph3.Dijkstra("cat", "dog");
    std::cout << "------------------------------------------\n";

    // Test Case: Adding Edges with One-Letter Difference (4 letter words)
    Graph graph4(3);
    graph4.addWord("dark");
    graph4.addWord("bark");
    graph4.addWord("barn");
    graph4.addEdge("dark", "bark");
    graph4.addEdge("bark", "barn");

    std::cout << "Test Case: Adding Edges with One-Letter Difference (4 letter words)\n";
    std::cout << "Shortest Path from 'dark' to 'barn' (BFS):\n";
    graph4.BFS("dark", "barn");
    std::cout << "Shortest Path from 'dark' to 'barn' (Dijkstra):\n";
    graph4.Dijkstra("dark", "barn");
    std::cout << "------------------------------------------\n";

    // Test Case: Adding Edges with One-Letter Difference (5 letter words)
    Graph graph5(3);
    graph5.addWord("stone");
    graph5.addWord("store");
    graph5.addWord("score");
    graph5.addEdge("stone", "store");
    graph5.addEdge("store", "score");

    std::cout << "Test Case: Adding Edges with One-Letter Difference (5 letter words)\n";
    std::cout << "Shortest Path from 'stone' to 'score' (BFS):\n";
    graph5.BFS("stone", "score");
    std::cout << "Shortest Path from 'stone' to 'score' (Dijkstra):\n";
    graph5.Dijkstra("stone", "score");
    std::cout << "------------------------------------------\n";


    return 0;
}
