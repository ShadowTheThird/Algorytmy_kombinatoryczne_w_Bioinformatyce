#include <cmath>
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
        relevant_sequence.clear();
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
    bool Quantity_check(){
        if(quality.size() == full_sequence.length()){
            return true;
        }
        cout << "quality: " << quality.size() << "\tsequence: " << full_sequence.length();
        return false; 
    }
    bool Asses_relevancy(int _minimal_quality){
        if(relevant_sequence.empty()){
            for(int i = 0; i < quality.size(); ++i){
                if(quality[i] >= _minimal_quality){
                    relevant_sequence[i+1] = full_sequence[i];
                }
            }
            return true;
        }
        return false;
    }
};

struct Motif{
    int position;
    string sequence = "";
};

map<string, Sequence> sequences;
map<string, map<string, vector<int>>> graph, temp; //etykieta, plik, lokalizacja

Motif Search_first(){
    Motif motif;
    int lowest = graph.begin()->second.begin()->second[0];
    string sequence = graph.begin()->first;
    for(auto it_1 = graph.begin(); it_1 != graph.end(); ++it_1){
        for(auto it_2 = it_1->second.begin(); it_2 != it_1->second.end(); ++it_2){
            for(int i = 0; i < it_2->second.size(); ++i){
                if(it_2->second[i] < lowest){
                    lowest = it_2->second[i];
                    sequence = it_1->first;
                }
            }
        }
    }
    motif.position = lowest;
    motif.sequence = sequence;
    return motif;
}

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
        if(it->second.Quantity_check()){
            if(!it->second.Asses_relevancy(20)){
                cout << "process failed due to relevant_sequence overwrite attempt";
                return 0;
            }
        }
    }
    int k = 5;
    ofstream ofile("output.txt");
    for(auto it_1 = sequences.begin(); it_1 != sequences.end(); ++it_1){
        Motif *label = new Motif[k];
        int i = 0;
        for(auto it_2 = it_1->second.relevant_sequence.begin(); it_2 != it_1->second.relevant_sequence.end(); ++it_2, ++i){
            if(i < k){
                label[i].position = it_2->first;
                for(int j = 0; j <= i; ++j){
                    label[j].sequence += it_2->second;
                }
            }
            else{
                graph[label[i - (k*(i/k))].sequence][it_1->first].push_back(label[i - (k*(i/k))].position);
                label[i - (k*(i/k))].sequence = "", label[i - (k*(i/k))].position = it_2->first;
                for(int j = 0; j < k; ++j){
                    label[j].sequence += it_2->second;
                }
            }
        }
    }
    for(auto it = graph.begin(); it != graph.end(); ++it){
        if(it->second.size() == 5){
            temp[it->first] = it->second;
        }
    }
    graph.clear();
    graph = temp;
    temp.clear();
    while(graph.size()){
        Motif potential_motif = Search_first();
        bool within_range = true;
        for(auto it = graph[potential_motif.sequence].begin(); it != graph[potential_motif.sequence].end(); ++it){
            if(it->second.size() > 1){
                bool at_least_one_within_range = false;
                for(int i = 0; i < it->second.size(); ++i){
                    if(abs(it->second[i]-potential_motif.position) <= 10*k){
                        at_least_one_within_range = true;
                        break;
                    }
                }
                if(at_least_one_within_range){
                    continue;
                }
                within_range = false;
                break;
            }
            if(abs(it->second[0]-potential_motif.position) > 10*k){
                within_range = false;
                break;
            }
        }
        if(within_range){
            cout << graph[potential_motif.sequence].size() << endl;
            cout << potential_motif.sequence << endl;
            for(auto it = graph[potential_motif.sequence].begin(); it != graph[potential_motif.sequence].end(); ++it){
                cout << it->first << ":\t";
                if(it->second.size() > 1){
                    int lowest = abs(it->second[0] - potential_motif.position), position_id = 0;
                    for(int i = 0; i < it->second.size(); ++i){
                        if(abs(it->second[i] - potential_motif.position) < lowest){
                            lowest = abs(it->second[i] - potential_motif.position), position_id = i;
                        }
                    }
                    cout << it->second[position_id] << endl;
                    continue;
                }
                cout << it->second[0] << endl;
            }
            return 0;
        }
        graph.erase(potential_motif.sequence);
    }
}