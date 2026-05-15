#include <iostream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <vector>

using namespace std;

struct Rec{
     int a,b ;
    Rec(int _a,int _b):a(_a),b(_b){}

};





int main (){
    vector<Rec> R;
    R.push_back(Rec(3,4));
    R.emplace_back(4,5);
    R.push_back(Rec(1,1));
    return 0;



}
