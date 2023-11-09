#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#define cout std::cout
#define endl std::endl
#define string std::string
#define ifstream std::ifstream
#define ofstream std::ofstream
#define vector std::vector
#define map std::map

struct Sequence{
    string full_sequence; 
    map<int, char> relevant_sequence;
    vector<short> quality;
    Sequence(){
        full_sequence = "";
    }
    bool Add_sequence(string _sequence){
        if(full_sequence == ""){
            full_sequence = _sequence;
            return true;
        }
        return false;
    }
    void Add_quality(int _quality){
        quality.push_back(_quality);
    }
    bool Asses_relevancy(int _minimal_quality){
        if(relevant_sequence.empty()){
            for(int i = 0; i < quality.size(); ++i){
                if(quality[i] >= _minimal_quality){
                    relevant_sequence[i] = full_sequence[i];
                }
            }
            return true;
        }
        return false;
    }
};

map<string, Sequence> sequences;

int main(){
    string fasta = "fasta\\sequence_0.fasta", qual = "qual\\sequence_0.qual", fasta_line_1 = "", fasta_line_2 = "", qual_line_1 = "", qual_line_2 = "";
    ifstream fasta_file, qual_file;
    for(int i = 1; i <= 5; ++i){
        fasta[15] = i+'0', qual[14] = i+'0';
        fasta_file.open(fasta), qual_file.open(qual);
        // cout << fasta << endl;
        getline(fasta_file, fasta_line_1), getline(qual_file, qual_line_1);
        getline(fasta_file, fasta_line_2), getline(qual_file, qual_line_2);
        // cout << fasta_line_1 << '\t' << fasta_line_2 << endl;
        if(!sequences[fasta_line_1].Add_sequence(fasta_line_2)){
            cout << "process failed due to full_sequence overwrite attempt";
            return 0;
        }
        for(int k = 0; k < qual_line_2.length(); ++k){
            string number = "";
            for(;isdigit(qual_line_2[k]); ++k){
                number += qual_line_2[k];
            }
            if(number != ""){
                sequences[qual_line_1].Add_quality(stoi(number));
            }
        }
        // cout << sequences[fasta_line_1].full_sequence << endl;
        // for(int j = 0; j < sequences[qual_line_1].quality.size(); ++j){
        //     cout << sequences[qual_line_1].quality[j] << '\t';
        // }
        // cout << endl;
        fasta_file.close(), qual_file.close();
    }
    for(auto it = sequences.begin(); it != sequences.end(); ++it){
        if(it->second.Asses_relevancy(20)){
            cout << "process failed due to relevant_sequence overwrite attempt";
            return 0;
        }
    }
    cout << sequences.rbegin()->second.full_sequence << endl;
    for(auto it = sequences.rbegin()->second.relevant_sequence.begin(); it != sequences.rbegin()->second.relevant_sequence.end(); ++it){
        cout << it->second;
    }
}