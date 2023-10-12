#include <fstream>
#include <iostream>
#include <vector>
#define cout std::cout
#define endl std::endl
#define ifstream std::ifstream
#define vector std::vector

struct Node{
    int key;
    vector<int> neighbours;
};

vector<Node> graph;

int main(){
    ifstream ifile("input.txt");
    if(!ifile.is_open()){
        cout << "file not found!";
        return 0;
    }
    
}