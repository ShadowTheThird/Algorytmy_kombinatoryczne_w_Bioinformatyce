#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct Sequences{
    std::string name, original_sequence;
    std::vector<int> qual;
};

struct Node{
    int position;
    std::string name;
    std::set<Node*> connections;
    Node(int _position):position(_position){}
};

std::map<std::string, std::vector<std::pair<std::string, int>>> segments, temp;
std::map<std::string, std::vector<Node>> graphs;
Sequences sequences[5];

int main(){
    std::ifstream ifile("input.txt");
    std::string line;
    int qual_limit = 10, motif_size = 6;
    for(int i = 0; getline(ifile, line); ++i){
        if(line[0] == '>'){
            std::string sequence, quality;
            getline(ifile, sequence);
            getline(ifile, quality);
            sequences[i].name = line;
            sequences[i].original_sequence = sequence;
            for(int j = 0; j < quality.size(); ++j){
                std::string number = "";
                for(; isdigit(quality[j]); ++j){
                    number += quality[j];
                }
                sequences[i].qual.push_back(stoi(number));
            }
        }
        else{
            std::cout << "ERROR\nincorrect file format detected" << std::endl;
        }
    }
    // std::cin >> qual_limit >> motif_size;
    for(int i = 0; i < 5; ++i){
        std::string k_mer = "";
        std::set<int> positions;
        for(int j = 0; j < sequences[i].original_sequence.length(); ++j){
            if(sequences[i].qual[j] >= qual_limit){
                k_mer += sequences[i].original_sequence[j];
                positions.insert(j+1);
            }
            if(k_mer.length() == motif_size){
                segments[k_mer].push_back(std::make_pair(sequences[i].name, *positions.begin()));
                k_mer = k_mer.substr(1);
                positions.erase(positions.begin());
            }
        }
    }
    for(auto it = segments.begin(); it != segments.end(); ++it){
        if(it->second.size() >= 5){
            temp.insert(*it);
        }
    }
    segments = temp;
    for(auto it = segments.begin(); it!= segments.end(); ++it){
        std::cout << it->first << std::endl;
    }
    for(auto it = segments.begin(); it!= segments.end(); ++it){
        for(int i = 0; i < it->second.size(); ++i){
            graphs[it->first].push_back(Node(it->second[i].second));
        }
    }
    for(auto it = graphs.begin(); it!= graphs.end(); ++it){
        for(int i = 0; i < it->second.size(); ++i){
            for(int j = i+1; j < it->second.size(); ++j){
                if(it->second[i].position + 1 == it->second[j].position){
                    it->second[i].connections.insert(&it->second[j]);
                    it->second[j].connections.insert(&it->second[i]);
                }
            }
        }
    }
    for(auto it = graphs.begin(); it!= graphs.end(); ++it){
        for(int i = 0; i < it->second.size(); ++i){
            std::set<Node*> shared_connections = it->second[i].connections;
            shared_connections.insert(&it->second[i]);
            for(auto it2 = it->second[i].connections.begin(); it2 != it->second[i].connections.end(); ++it2){
                std::set<Node*> temp_shared_connections;
                int count_connections = 0;
                for(auto it3 = (*it2)->connections.begin(); it3!= (*it2)->connections.end(); ++it3){
                    if(shared_connections.find(*it3) != shared_connections.end()){
                        temp_shared_connections.insert(*it3);
                        ++count_connections;
                    }
                }
                if(count_connections >= 4){
                    temp_shared_connections.insert(*it2);
                    shared_connections = temp_shared_connections;
                }
            }
        }
    }
}