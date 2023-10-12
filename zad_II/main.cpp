#include <fstream>
#include <iostream>
#include <vector>
#define cout std::cout
#define endl std::endl
#define string std::string
#define ifstream std::ifstream
#define vector std::vector

struct Node{
    int key;
    vector<int> neighbours;
    Node(int _key){
        key = _key;
    }
};

vector<Node> graph;

int main(){
    ifstream ifile("input.txt");
    if(!ifile.is_open()){
        cout << "file not found!";
        return 0;
    }
    string line;
    for(int i = 0; getline(ifile, line); ++i){
        string number = "";
        int k = 0;
        for(;isdigit(line[k]); ++k){
            number += line[k];
        }
        graph.push_back(Node(stoi(number)));
        for(; line[k] != '\0'; ++k){
            if(isdigit(line[k])){
                number = "";
                for(; isdigit(line[k]); ++k){
                    number += line[k];
                }
                graph[i].neighbours.push_back(stoi(number));
            }
        }
    }
    for(int i = 0; i < graph.size(); ++i){
        cout << graph[i].key << ":\t";
        for(int j = 0; j < graph[i].neighbours.size(); ++j){
            cout << graph[i].neighbours[j] << '\t';
        }
        cout << endl;
    }
}