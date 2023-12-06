#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#define cout std::cout
#define endl std::endl;
#define ifstream std::ifstream
#define ofstream std::ofstream
#define pair std::pair
#define string std::string
#define vector std::vector

int main(){
    srand(time(NULL));
    ifstream qual("qual.txt"), fasta("fasta.txt");
    string qual_line = "", fasta_line = "";
    std::set<int> chosen;
    for(; chosen.size() < 5;){
        int random = rand()%500;
        if(chosen.find(random) == chosen.end()){
            chosen.insert(random);
        }
    }
    auto it = chosen.begin();
    ofstream ofile("output.txt");
    vector<pair<string,pair<string,string>>> format;
    getline(fasta, fasta_line), getline(qual, qual_line);
    for(int sequence = 0; it != chosen.end(); ++sequence){
        if(sequence == *it){
            string name = fasta_line;
            string sequence = "", quality = "";
            while(getline(fasta, fasta_line)){
                if(fasta_line[0] == '>'){
                    break;
                }
                sequence += fasta_line;
            }
            while(getline(qual, qual_line)){
                if(qual_line[0] == '>'){
                    break;
                }
                if(quality != ""){
                    quality += " ";
                }
                quality += qual_line;
            }
            format.push_back(std::make_pair(name, std::make_pair(sequence,quality)));
            ++it;
        }
        else{
            while(getline(fasta, fasta_line)){
                if(fasta_line[0] == '>'){
                    break;
                }
            }
            while(getline(qual, qual_line)){
                if(qual_line[0] == '>'){
                    break;
                }
            }
        }
    }
    int id = 0, shortest = format[0].second.first.length();
    for(int i = 1; i < format.size(); ++i){
        if(format[i].second.first.length() < shortest){
            id = i;
            shortest = format[i].second.first.length();
        }
    }
    int random = rand()%(format[id].second.first.length() - 40) + 31;
    for(int i = 0; i < 5; ++i){
        ofile << format[i].first << endl;
        int offset = rand()%81 - 40;
        while(random + offset + 9 > format[i].second.first.length()){
            offset = rand()%81 - 40;
        }
        string sequence = format[i].second.first.substr(0, random + offset), quality;
        sequence += "TTTTTTTTT";
        sequence += format[i].second.first.substr(random + offset + 9);
        ofile << sequence << endl;
        int k = 0;
        for(int j = 0; j < random + offset; ++j, ++k){
            while(format[i].second.second[k] != ' '){
                ++k;
            }
        }
        quality = format[i].second.second.substr(0, k);
        for(int j = 0; j < 9; ++j, ++k){
            while(format[i].second.second[k] != ' '){
                ++k;
            }
            quality += "99 ";
        }
        quality += format[i].second.second.substr(k);
        ofile << quality << endl;
    }
}