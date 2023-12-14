#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#define cout std::cout
#define cin std::cin
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
        cout << "sequence overwrite attempt detected" << endl;
        return false;
    }
    void Add_quality(vector<short> _quality){
        quality = _quality;
    }
    bool Quantity_check(){
        if(quality.size() == full_sequence.length()){
            return true;
        }
        cout << "quality: " << quality.size() << "\tsequence: " << full_sequence.length() << endl;
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
    Motif(string _sequence, int _position):sequence(_sequence),position(_position){}
    Motif(){}
};

map<string, Sequence> sequences;
map<string, map<string, vector<int>>> graph, temp;

int main(){
    ifstream ifile("input.txt");
    string line;
    while(getline(ifile, line)){
        if(line[0] == '>'){
            string sequence, quality;
            getline(ifile, sequence);
            getline(ifile, quality);
            if(!sequences[line].Add_sequence(sequence)){
                cout << "ERROR" << endl;
                return 0;
            }
            vector<short> temp_qual;
            for(int i = 0; i < quality.size(); ++i){
                string number = "";
                for(; quality[i] != ' '; ++i){
                    number += quality[i];
                }
                temp_qual.push_back(stoi(number));
            }
            sequences[line].Add_quality(temp_qual);
        }
        else{
            cout << "ERROR\nincorrect file format detected" << endl;
        }
    }
    int label_length = 5, relevant_quality = 20;
    cout << "input relevant quality threshold:\t";
    cin >> relevant_quality;
    while(true){
        cout << "input searched motif length:\t";
        cin >> label_length;
        if(label_length < 4 || label_length > 9){
            cout << "searched motifs length is to be between 4 and 9 inclusive" << endl;
            continue;
        }
        break;
    }
    for(auto it = sequences.begin(); it != sequences.end(); ++it){
        if(it->second.Quantity_check()){
            if(!it->second.Asses_relevancy(relevant_quality)){
                cout << "process failed due to relevant_sequence overwrite attempt";
                return 0;
            }
        }
        else{
            cout << it->first << "\nmissmatched sequence length and quality count";
            return 0;
        }
    }
    for(auto it_1 = sequences.begin(); it_1 != sequences.end(); ++it_1){
        Motif *label = new Motif[label_length];
        int i = 0;
        for(auto it_2 = it_1->second.relevant_sequence.begin(); it_2 != it_1->second.relevant_sequence.end(); ++it_2, ++i){
            if(i < label_length){
                label[i].position = it_2->first;
                for(int j = 0; j <= i; ++j){
                    label[j].sequence += it_2->second;
                }
            }
            else{
                int temp = i % label_length;
                graph[label[temp].sequence][it_1->first].push_back(label[temp].position);
                label[temp].sequence = "", label[temp].position = it_2->first;
                for(int j = 0; j < label_length; ++j){
                    label[j].sequence += it_2->second;
                }
            }
        }
        int temp = i % label_length;
        graph[label[temp].sequence][it_1->first].push_back(label[temp].position);
    }
    for(auto it = graph.begin(); it != graph.end(); ++it){
        if(it->second.size() == 5){
            temp[it->first] = it->second;
        }
    }
    graph.clear();
    graph = temp;
    temp.clear();
    for(auto it = graph.begin(); it != graph.end(); ++it){
        Motif potential_motif(it->first, it->second.begin()->second[0]);
        bool within_range = true;
        for(auto it = graph[potential_motif.sequence].begin(); it != graph[potential_motif.sequence].end(); ++it){
            if(it->second.size() > 1){
                bool at_least_one_within_range = false;
                for(int i = 0; i < it->second.size(); ++i){
                    if(abs(it->second[i]-potential_motif.position) <= 10*label_length){
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
            if(abs(it->second[0] - potential_motif.position) > 10*label_length){
                within_range = false;
                break;
            }
        }
        if(within_range){
            cout << potential_motif.sequence << endl;
            for(auto it = graph[potential_motif.sequence].begin(); it != graph[potential_motif.sequence].end(); ++it){
                cout << it->first << ":\t";
                if(it->second.size() > 1){
                    int lowest = abs(it->second[0] - potential_motif.position), position_id = 0;
                    for(int i = 1; i < it->second.size(); ++i){
                        if(abs(it->second[i] - potential_motif.position) < lowest){
                            lowest = abs(it->second[i] - potential_motif.position), position_id = i;
                        }
                    }
                    cout << it->second[position_id] << endl;
                    continue;
                }
                cout << it->second[0] << endl;
            }
            cout << endl;
        }
    }
    cout << "could not find more motifs with given parameters" << endl;
}