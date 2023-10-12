#include <fstream>
#include <iostream>
#include <vector>
#define cout std::cout
#define endl std::endl
#define ifstream std::ifstream

int main(){
    ifstream ifile("input.txt");
    if(!ifile.is_open()){
        cout << "file not found!";
        return 0;
    }
    
}