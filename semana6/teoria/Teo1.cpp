#include <vector>   
#include <iostream>
using namespace std;


void insertion_sort(vector<int>& v){
    for(int j = 1; j< v.size(); j++){
        int key =v[j];
        int i =j -1;
        while(i>=0 &&v[i]> key){
            v[i+1]=v[i];
            i--;
        }
        v[i+1]=key;
    }
}

int main(){
    vector<int> v = {5,2,4,6,1,3};
    insertion_sort(v);
    for(int i : v){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}