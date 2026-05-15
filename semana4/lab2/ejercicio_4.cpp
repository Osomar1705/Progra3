#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



int manin(){
    string figs="CDET";
    vector<string> baraja(52);
    int i=0;
    generate(baraja.begin(),baraja.end(),[&]()->string{return to_string((i++)%13+1) + figs[i/13];});
    for_each(baraja.begin(),baraja.end(),[](string x)->void{cout<< x << ' ';});
    return 0;

}