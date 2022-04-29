#include "parser.hh"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void parse_dimacs(ifstream& f, Instance& i) {
    int numc, numv;
    int clause = 0;
    vector< vector<int> > clauses;

    string line;
    while(getline(f, line)) {
        stringstream lstream(line);
        string stok;
        int itok;
        
        // first token
        lstream >> stok;

        // comment
        if(stok == "c") {
            continue;
        }

        // problem definition
        if(stok == "p") {
            lstream >> stok;
            lstream >> numv;
            lstream >> numc;
            i.initProblem(numc, numv);
            continue;
        }

        // end
        if(stok == "%") {
            break;
        }

        // clause
        itok = stoi(stok);
        i.addDimacsLiteral(clause, itok);
        while(lstream >> itok) {
            if(itok == 0) {
                break;
            }
            i.addDimacsLiteral(clause, itok);
        }

        // increment clause id
        clause++;
    }
}
