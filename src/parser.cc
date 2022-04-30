#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "parser.hh"

using namespace std;

shared_ptr<Instance> parse_dimacs(const char* fname) {
    ifstream f(fname);
    shared_ptr<Instance> i = nullptr;
    int numc, numv;
    int clause = 0;

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
            i = make_shared<Instance>(numc, numv);
            continue;
        }

        // end
        if(stok == "%") {
            break;
        }

        // clause
        itok = stoi(stok);
        i->addDimacsLiteral(clause, itok);
        while(lstream >> itok) {
            if(itok == 0) {
                break;
            }
            i->addDimacsLiteral(clause, itok);
        }

        // increment clause id
        clause++;
    }

    return i;
}
