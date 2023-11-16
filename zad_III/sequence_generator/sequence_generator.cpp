#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define cout std::cout
#define endl std::endl;
#define ifstream std::ifstream
#define ofstream std::ofstream
#define string std::string
#define vector std::vector



int main(){
    srand(time(NULL));
    ifstream fasta_file("input.txt");
    string file_name, sequence, qual, changed_sequence;
    int random_value;
    vector<int> changed_qual;
    if(!fasta_file.is_open()){
        cout << "couldn't open file" << endl;
        return 0;
    }
    getline(fasta_file, file_name);
    getline(fasta_file, sequence);
    getline(fasta_file, qual);
    while(true){
        random_value = rand()%sequence.length();
        if(random_value > 10){
            break;
        }
    }
    for(int i = 0; i < qual.length(); ++i){
        if(changed_qual.size() == random_value){
            for(int i = 0; i < 9; ++i){
                changed_qual.push_back(99);
            }
        }
        if(isdigit(qual[i])){
            string number = "";
            for(; isdigit(qual[i]); ++i){
                number += qual[i];
            }
            changed_qual.push_back(stoi(number));
        }
    }
    changed_sequence = sequence.substr(0,random_value);
    changed_sequence += "AACCCCAAT";
    changed_sequence += sequence.substr(random_value);
    fasta_file.close();
    if(changed_qual.size() == changed_sequence.size()){
        ofstream fasta_file("output.txt");
        int number_start = file_name.find("length=") + 7;
        string number = "";
        while(isdigit(file_name[number_start])){
            number += file_name[number_start];
            ++number_start;
        }
        int x = number_start - number.length();
        number = std::to_string(stoi(number) + 9);
        for(int i = 0; i < number.length(); ++i){
            file_name[x + i] = number[i];
        }
        fasta_file << file_name << endl;
        fasta_file << changed_sequence << endl;
        for(int i = 0; i < changed_qual.size(); ++i){
            fasta_file << changed_qual[i] << " ";
        }
    }
    return 0;
}