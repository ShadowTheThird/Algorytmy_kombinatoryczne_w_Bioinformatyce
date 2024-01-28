#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Sequence{
    std::string name, original_sequence, modified_sequence;
    std::vector<int> qual, position;
};

struct Graph{
    std::string k_mer, name;
    int k_position;
    std::vector<std::pair<int,int>> adjecency;
    Graph(std::string _k_mer, std::string _name, int _k_position):k_mer(_k_mer), name(_name), k_position(_k_position){}
};

std::vector<Sequence> sequences(6);
std::vector<std::vector<Graph>> graph(6);

bool Mr_sorter(Graph key_1, Graph key_2){
    return key_1.adjecency.size() > key_2.adjecency.size();
}

int main(){
    std::ifstream ifile("input.txt");
    std::string line = "";
    int k = 5, q = 5;
    for(int i = 1; getline(ifile, line); ++i){
        if(line[0] == '>'){
            std::string sequence, quality;
            getline(ifile, sequence);
            getline(ifile, quality);
            sequences[i].name = line;
            sequences[i].original_sequence = sequence;
            for(int j = 0; j < quality.size(); ++j){
                std::string number = "";
                for(; isdigit(quality[j]) && j < quality.size(); ++j){
                    number += quality[j];
                }
                sequences[i].qual.push_back(stoi(number));
            }
        }
        else{
            std::cout << "ERROR\nincorrect file format detected" << std::endl;
        }
    }
    // for(int i=0; i >= 0 ; i++)
    // {
    //     std::cout << "Enter the length of the motif:\t";
    //     std::cin >> k;
    //     if(k>=4 && k <=9)
    //     {
    //         break;
    //     }
    //     else
    //     {
    //         std::cout << "ERROR\nprogram accepts only values between 4 and 9" << std::endl;
    //         continue;
    //     }
    // }
    // std::cout << "Enter the reliability of an individual nucleotide: ";
    // std::cin >> q;
    for(int i = 1; i<6; i++){
        if(sequences[i].original_sequence.length() == sequences[i].qual.size()){
            sequences[i].modified_sequence = "";
            for(int j = 0; j < sequences[i].original_sequence.length(); ++j){
                if(sequences[i].qual[j] >= q){
                    sequences[i].modified_sequence += sequences[i].original_sequence[j];
                    sequences[i].position.push_back(j+1);
                }
            }
        }
        else{
            std::cout << "ERROR:\tmissmatched sequence and qual lengths" << std::endl;
        }
    }
    for(int i = 1; i < 6; i++){
        for(int j = 0; j < sequences[i].modified_sequence.length() - k; ++j){
            graph[i].push_back(Graph(sequences[i].modified_sequence.substr(j, k), sequences[i].name, sequences[i].position[j]));
        }
    }
    for(int i = 1; i < 6; ++i){
        for(int j = 0; j < graph[i].size(); ++j){
            for(int l = i+1; l < 6; ++l){
                if (i==l){
                    continue;
                }
                int m, m_end;
                if(j - 10 * k < 0){
                    m = 0;
                }
                else{
                    m = j - 10 * k;
                }
                if(j + 10 * k < graph[l].size()){
                    m_end = j + 10 * k;
                }
                else{
                    m_end = graph[l].size();
                }
                for(; m < m_end; ++m)
                {
                    if(graph[i][j].k_mer == graph[l][m].k_mer){
                        graph[i][j].adjecency.push_back(std::make_pair(l,m));
                        graph[l][m].adjecency.push_back(std::make_pair(i,j));
                    }
                }
            }
        }
    }
    int shortest_sequence = sequences[1].modified_sequence.length(), ID = 1;
    for(int i = 2; i<6; i++){
        if(shortest_sequence > sequences[i].modified_sequence.length()){
            shortest_sequence = sequences[i].modified_sequence.length();
            ID = i;
        }
    }
    sort(graph[ID].begin(), graph[ID].end(), Mr_sorter);
    for(int i = 0; i < graph[ID].size(); ++i){
        if(graph[ID][i].adjecency.size() >= 4){
            bool exist[6] = {1,0,0,0,0,0};
            exist[ID] = 1;
            bool check = true;
            for(int j = 0; j < graph[ID][i].adjecency.size(); ++j){
                exist[graph[ID][i].adjecency[j].first] = 1;
            }
            for(int l = 0; l < 6; ++l){
                if(!exist[l]){
                    check = false;
                    break;
                }
            }
            if(check){
                
                
                std::cout << graph[ID][i].k_mer << std::endl;
                for(int j = 1; j < 6; ++j){
                    if(j == ID){
                        std::cout << graph[ID][i].name << ":\t" << graph[ID][i].k_position << std::endl;
                    }
                    else{
                        for(int l = 0; l < graph[ID][i].adjecency.size(); ++l){
                            if(graph[ID][i].adjecency[l].first == j){
                                std::cout << graph[j][graph[ID][i].adjecency[l].second].name << ":\t" << graph[j][graph[ID][i].adjecency[l].second].k_position << std::endl;
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }
        else{
            break;
        }
    }
    return 0;
}
