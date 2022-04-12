#include "parser.hh"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int* vecToMem(vector< vector<int> > clauses, int numc, int numv) {
    int* mat = (int*) calloc(numc * numv, sizeof(int));
    memset(mat, 0, sizeof(int) * numc * numv);

    for(int c = 0; c < numc; c++) {
        for(int v : clauses[c]) {
            if(v > 0) {
                mat[c*numv + abs(v) - 1] = +1;
            } else {
                mat[c*numv + abs(v) - 1] = -1;
            }
        }
    }

    return mat;
}

Instance* parse_dimacs(ifstream& f) {
    auto i = new Instance;
    vector< vector<int> > clauses;

    string line;
    while(getline(f, line)) {
        stringstream lstream(line);
        string stok;
        int itok;
        
        // first token
        lstream >> stok;
        if(stok == "c") {
            continue;
        }

        if(stok == "p") {
            lstream >> stok;
            lstream >> i->numv;
            lstream >> i->numc;
            continue;
        }

        if(stok == "%") {
            break;
        }

        itok = stoi(stok);
        vector<int> temp;
        temp.push_back(itok);
        while(lstream >> itok) {
            if(itok == 0) {
                break;
            }
            temp.push_back(itok);
        }
        clauses.push_back(temp);
    }

    i->mat = vecToMem(clauses, i->numc, i->numv);
    return i;
}
