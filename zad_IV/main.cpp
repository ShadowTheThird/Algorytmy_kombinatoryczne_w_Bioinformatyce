#include <fstream>
#include <iostream>
#include <map>
#include <vector>

std::vector<int> map_boi;
std::map<int, int> slicing_tree;
int sum = 0;
    
bool MapCreator(int id){
    for(auto it = slicing_tree.begin(); it != slicing_tree.end(); ++it){
        if(slicing_tree.find(map_boi[id] + it->first) != slicing_tree.end()){
            if(it->second){
                map_boi.push_back(it->first);
                --it->second;
                int map_sum = 0;
                for(int i = 0; i < map_boi.size(); ++i){
                    map_sum += map_boi[i];
                }
                if(map_sum == sum){
                    auto it_inner = slicing_tree.begin();
                    for(; it_inner != slicing_tree.end(); ++it_inner){
                        if(it_inner->second){
                            break;
                        }
                    }
                    if(it_inner == slicing_tree.end()){
                        return true;
                    }
                }
            }
        }
    }
}

int main(){
    std::ifstream ifile("input.txt");
    std::string line, sequence = "";while(getline(ifile, line)){
        if(sequence != ""){
            sequence += " ";
        }
        sequence += line;
    }
    for(int i = 0; i < sequence.length(); ++i){
        std::string number = "";
        for(;sequence[i] != ' '; ++i){
            number += sequence[i];
        }
        if(number != ""){
            ++slicing_tree[stoi(number)];
        }
    }
    auto it = slicing_tree.end();
    sum = it->first, --it->second;
    map_boi.push_back((--it)->first - (--it)->first);
    if(slicing_tree.find(map_boi[0]) != slicing_tree.end()){
        --slicing_tree[map_boi[0]];
    }
    else{
        std::cout << "incomplete segmentation table" << std::endl;
        return 0;
    }

    std::cout << "incomplete segmentation table" << std::endl;
}