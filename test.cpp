#include <iostream>
#include <vector>
using namespace std;

int main(){
    string text = "AAAACTGCAAGAAGAAGGTTTGAAT";
    string quality = "24 23 18 2 31 24 25 25 28 22 32 31 27 32 23 22 27 21 27 27 18 27 21 12 25 31 27 29 23 12 29 31 27 17 17 24 17 31 26 32 27 28 27";
    vector<int> temp_qual;
    cout << text.length() << endl;
    for(int i = 0; i < quality.size(); ++i){
        string number = "";
        for(; quality[i] != ' '; ++i){
            number += quality[i];
        }
        temp_qual.push_back(stoi(number));
    }
    cout << temp_qual.size() << endl;
}