#include "instance.hh"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

void Instance::addDimacsLiteral(int c, int dimacsLiteral) {
    int v = abs(dimacsLiteral) - 1;
    if(dimacsLiteral > 0) pos.set(c*numv + v);
    else neg.set(c*numv + v);
}

int Instance::get(int c, int v) {
    if(pos[c*numv + v]) return +1;
    if(neg[c*numv + v]) return -1;
    return 0;
}

void Instance::print() {
    for(int c = 0; c < numc; c++) {
        for(int v = 0; v < numv; v++) {
            cout << setfill(' ') << setw(2) << get(c, v) << " ";
        }
        cout << endl;
    }
}
