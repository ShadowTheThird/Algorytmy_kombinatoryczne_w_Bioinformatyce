#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> mapka;
    int babajaga[18] = {3, 2, 6, 4, 3, 4, 6, 2, 3, 2, 4, 6, 3, 6, 4, 2, 3, 9};
    for(int i = 0; i < 18; ++i){
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
    int a = 5;
    int *p = &a;
    int *pp = p+1;
}