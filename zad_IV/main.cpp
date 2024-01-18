#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::vector<int> thingy_thing;
std::multiset<int> values;

bool Mapper(){
    if(!values.size()){
        return true;
    }
    std::set<int> inner_values(values.begin(), values.end());
    for(auto it = inner_values.begin(); it != inner_values.end(); ++it){
        std::vector<int> erased;
        int new_key = *it, sum = 0;
        thingy_thing.push_back(new_key);
        bool suitable = true;
        for(int i = thingy_thing.size() - 1; i >= 0; --i){
            sum += thingy_thing[i];
            if(values.find(sum) != values.end()){
                values.erase(values.find(sum));
                erased.push_back(sum);
            }
            else{
                suitable = false;
                break;
            }
        }
        if(suitable){
            if(Mapper()){
                return true;
            }
        }
        thingy_thing.pop_back();
        for(int i = 0; i < erased.size(); ++i){
            values.insert(erased[i]);
        }
    }
    return false;
}

int main(){
    std::ifstream ifile("input.txt");
    std::string line;
    getline(ifile,line);
    for(int i = 0; i < line.length(); ++i){
        std::string number = "";
        for(;isdigit(line[i]); ++i){
            number += line[i];
        }
        if(number != ""){
            values.insert(stoi(number));
        }
    }
    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
    if(ceil((sqrt(1 + 8 * values.size()) - 3)/2) != floor((sqrt(1 + 8 * values.size()) - 3)/2)){
        std::cout << "incomplete data set" << std::endl;
        return 0;
    }
    int key = *(values.rbegin()) - *(++values.rbegin());
    if(values.find(key) != values.end()){
        values.erase(values.find(key));
        thingy_thing.push_back(key);
        if(Mapper()){
            for(int i = 0; i < thingy_thing.size(); ++i){
                std::cout << thingy_thing[i] << ' ';
            }
            std::cout << std::endl;
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::cout << "time elapsed:\t" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
            return 0;
        }
    }
    std::cout << "couldn't recreate map based on provided data set" << std::endl;
}