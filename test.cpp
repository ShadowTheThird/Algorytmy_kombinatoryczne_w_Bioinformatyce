#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> mapka;
    int babajaga[21] = {4, 2, 5, 6, 2, 3, 7, 9, 1, 4, 2, 3, 4, 6, 5, 5, 1, 2, 2, 3, 7};
    for(int i = 0; i < 21; ++i){
        int sum = 0;
        for(int j = i; j >= 0; --j){
            sum += babajaga[j];
            mapka.push_back(sum);
        }
    }
    sort(mapka.begin(), mapka.end());
    for(int i = 0; i < mapka.size(); ++i){
        cout << mapka[i] << ' ';
    }
}