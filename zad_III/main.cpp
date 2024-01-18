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
    std::set<Node*> connections;
    Node(int _position):position(_position){
        connections.empty();
    }
};

std::map<std::string, std::vector<std::pair<std::string, int>>> segments, temp;
std::map<std::string, std::map<std::string, Node>> graphs;
Sequences sequences[5];

int main(){
    std::ifstream ifile("input.txt");
    std::string line;
    int qual_limit = 10, motif_size = 5;
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
    // std::cout << "input preferred quality threshold:\t";
    // std::cin >> qual_limit;
    // std::cout << "input expected motif size:\t";
    // while(true){
    //     std::cin >> motif_size;
    //     if(motif_size < 4 || motif_size > 9){
    //         std::cout << "motif size has to be between 4 and 9 included\t";
    //         continue;
    //     }
    //     break;
    // }
    for(int i = 0; i < 5; ++i){
        std::string k_mer = "";
        for(int j = 0; j < sequences[i].original_sequence.length(); ++j){
            if(sequences[i].qual[j] >= qual_limit){
                k_mer += sequences[i].original_sequence[j];
            }
            if(k_mer.length() == motif_size){
                segments[k_mer].push_back(std::make_pair(sequences[i].name, j));
                k_mer = k_mer.substr(1);
            }
        }
    }
    for(auto it = segments.begin(); it != segments.end(); ++it){
        if(it->second.size() >= 5){
            temp.insert(*it);
        }
    }
    segments = temp;
    
}