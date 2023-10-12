#include <algorithm>
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
bool coupled = true, linear = true;

bool Node_sorting_function(Node first, Node second){
    return first.key < second.key;
}

bool Coupling_sorting_function(int i, int j){
    if(i == j){
        coupled = false;
    }
    return i < j;
}

void Check_coupling(vector<int> first, vector<int> second){
    for(int i = 0, j = 0; i < first.size() && j < second.size();){
        if(first[i] == second[j]){
            if(first != second){
                coupled = false;
            }
            return;
        }
        else{
            if(first[i] > second[j]){
                ++j;
            }
            else{
                ++i;
            }
        }
    }
}

Node Search_Node(int key){
    int id = key;
    if(id >= graph.size()){
        id = graph.size() - 1;
    }
    for(int falesafe = 20; graph[id].key != key; --falesafe){
        if(graph[id].key < key){
            ++id;
        }
        else{
            --id;
        }
        if(!falesafe){
            return Node(-1);
        }
    }
    return graph[id];
}
void Linearity_test(Node first){
    for(int i = 0; i < first.neighbours.size(); ++i){
        for(int j = 0; j < first.neighbours.size(); ++j){
            if(i == j){
                continue;
            }
            Node first_node = Search_Node(first.neighbours[i]), second_node = Search_Node(first.neighbours[j]);
            if(first_node.key == -1 || second_node.key == -1){
                continue;
            }
            if(first_node.neighbours == second_node.neighbours && !first_node.neighbours.empty()){
                linear = false;
                return;
            }
        }
    }
}

bool Type_test(Node first, Node second){
    sort(first.neighbours.begin(), first.neighbours.end(), Coupling_sorting_function);
    sort(second.neighbours.begin(), second.neighbours.end(), Coupling_sorting_function);
    Check_coupling(first.neighbours, second.neighbours);
    Linearity_test(first);
    if(coupled){
        return true;
    }
    return false;
}

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
    sort(graph.begin(), graph.end(), Node_sorting_function);
    for(int i = 0; i < graph.size(); ++i){
        for(int j = 0; j < graph.size(); ++j){
            if(i == j){
                continue;
            }
            if(!Type_test(graph[i], graph[j])){
                cout << "graf nie jest sprzezony" << endl;
                goto non_coupled;
            }
        }
    }
    if(coupled){
        if(linear){
            cout << "graf jest liniowy" << endl;
        }
        else{
            cout << "graf jest sprzezony, ale nie liniowy" << endl;
        }
    }
non_coupled:
    cout << "";
    // for(int i = 0; i < graph.size(); ++i){
    //     cout << graph[i].key << ":\t";
    //     for(int j = 0; j < graph[i].neighbours.size(); ++j){
    //         cout << graph[i].neighbours[j] << '\t';
    //     }
    //     cout << endl;
    // }
}