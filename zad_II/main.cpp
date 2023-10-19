#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#define cout std::cout
#define endl std::endl
#define string std::string
#define ifstream std::ifstream
#define ofstream std::ofstream
#define vector std::vector

struct Node{
    int key, entering, leaving;
    vector<int> neighbours;
    bool checked;
    Node(int _key){
        key = _key;
        checked = false;
    }
};

vector<Node> graph, original_graph;
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

int Search_Node(int key){
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
            return -1;
        }
    }
    return id;
}

void Linearity_test(Node first){
    for(int i = 0; i < first.neighbours.size(); ++i){
        for(int j = 0; j < first.neighbours.size(); ++j){
            if(i == j){
                continue;
            }
            int first_node = Search_Node(first.neighbours[i]), second_node = Search_Node(first.neighbours[j]);
            if(first_node== -1 || second_node == -1){
                continue;
            }
            if(graph[first_node].neighbours == graph[second_node].neighbours && !graph[first_node].neighbours.empty()){
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
    ifile.close();
    sort(graph.begin(), graph.end(), Node_sorting_function);
    for(int i = 0; i < graph.size(); ++i){
        for(int j = 0; j < graph.size(); ++j){
            if(i == j){
                continue;
            }
            if(!Type_test(graph[i], graph[j])){
                cout << "graf nie jest sprzezony" << endl;
                return 0;
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
    for(int i = 0; i < graph.size(); ++i){
        graph[i].leaving = 2*i;
        graph[i].entering = 2*i+1;
    }
    for(int i = 0; i < graph.size(); ++i){
        for(int j = 0; j < graph.size(); ++j){
            if(graph[i].neighbours == graph[j].neighbours){
                graph[j].entering = graph[i].entering;
            }
        }
        for(int j = 0; j < graph[i].neighbours.size(); ++j){
            graph[Search_Node(graph[i].neighbours[j])].leaving = graph[i].entering;
        }
    }
    for(int i = 0; i < 2*graph.size(); ++i){
        original_graph.push_back(Node(i));
        for(int j = 0; j < graph.size(); ++j){
            if(original_graph[i].key == graph[j].leaving){
                original_graph[i].neighbours.push_back(graph[j].entering);
                original_graph[i].checked = true;
            }
            if(original_graph[i].key == graph[j].entering){
                original_graph[i].checked = true;
            }
        }
    }
    for(int i = 0; i < original_graph.size(); ++i){
        if(!original_graph[i].checked){
            Node temp = original_graph[i];
            original_graph[i] = original_graph[original_graph.size()-1];
            original_graph[original_graph.size()-1] = temp;
            original_graph.pop_back();
            --i;
        }
    }
    ofstream ofile("output.txt");
    for(int i = 0; i < original_graph.size(); ++i){
        ofile << original_graph[i].key << ":\t";
        for(int j = 0; j < original_graph[i].neighbours.size(); ++j){
            ofile << original_graph[i].neighbours[j] << '\t';
        }
        ofile << endl;
    }
}