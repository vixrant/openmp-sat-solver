#include "solver.hh"
#include "debug.hh"
#include <memory>
#include <iostream>

using namespace std;

bool unit_propagate(Instance& i, int* pmodel) {
    bool changed = false;
    for(int c = 0; c < i.numc; c++) {
        int cnt = 0;
        int last = -1;
        int unsat = 1;
        for(int v = 0; v < i.numv; v++) {
            int pol = i.elemAt(c, v);
            // literal not in clause
            if(pol == 0) {
                continue;
            }

            // assignment for literal sats the clause
            if(pmodel[v] == pol) {
                unsat = 0;
                break;
            }

            // assignment for literal does not sat the clause
            if(pmodel[v] != 0 && pmodel[v] != pol) {
                continue;
            }

            // no assignment for literal
            cnt++;
            last = v;
        }

        if(cnt*unsat == 1) {
            changed = true;
            pmodel[last] = i.elemAt(c, last);
            D(cout << "UP: " << last << "=" << pmodel[last] << " c:" << c << endl);
        }
    }
    return changed;
}

bool pure_literal_eliminate(Instance& i, int* pmodel) {
    bool changed = false;
    int pos[i.numv];
    int neg[i.numv];
    memset(pos, 0, sizeof(int) * i.numv);
    memset(neg, 0, sizeof(int) * i.numv);
    for(int c = 0; c < i.numc; c++) {
        for(int v = 0; v < i.numv; v++) {
            int pol = i.elemAt(c, v) * (pmodel[v] == 0);
            if(pol == 1)
                pos[v]++;
            else if(pol == -1)
                neg[v]++;
        }
    }

    for(int v = 0; v < i.numv; v++) {
        if(pmodel[v])
            continue;
        bool noPos = pos[v] == 0;
        bool noNeg = neg[v] == 0;
        bool eliminate = noPos ^ noNeg;
        if(eliminate) {
            pmodel[v] = (+1)*noNeg + (-1)*noPos;
            D(cout << "PLE: " << v << "=" << pmodel[v] << endl);
        }
        changed = changed || eliminate;
    }

    return changed;
}

Status check_sat(Instance& i, int* pmodel) {
    for(int c = 0; c < i.numc; c++) {
        int unasgn = 0;
        bool sat = false;
        for(int v = 0; v < i.numv && sat == false; v++) {
            int pol = i.elemAt(c, v);
            int asgn = pmodel[v];

            if(asgn == 0) {
                unasgn++;
            } else if(pol == 0) {
                continue;
            } else if(pol == asgn) {
                sat = true;
            }
        }

        // no partial assignment satisfied clause c
        if(sat == false) {
            // no more unassigned literals in this clause
            if(unasgn == 0)
                return UNSAT;
            // else we don't know what unassigned literals can be
            return UNKNOWN;
        }
    }

    // clause is sat
    return SAT;
}

bool _solve_util(Instance& i, int* prevmodel, int guessPtr, int* out) {
    // Make local pmodel state
    int pmodel[i.numv];
    memcpy(pmodel, prevmodel, sizeof(int) * i.numv);

    // Unit propagate
    while(unit_propagate(i, pmodel)) {
        continue;
    }

    // Pure literal eliminate
    while(pure_literal_eliminate(i, pmodel)) {
        continue;
    }

    // Check sat
    int status = check_sat(i, pmodel);

    if(status == SAT) {
        // Copy pmodel to out model
        memcpy(out, pmodel, sizeof(int) * i.numv);
        return true;
    }

    // Guess
    while(1) {
        // Find unassigned literal
        while(guessPtr != i.numv && pmodel[guessPtr] != 0) {
            guessPtr++;
        }

        if(guessPtr == i.numv) {
            break;
        }
        
        // Assign literal to true
        D(cout << "G: " << guessPtr << "=1" << endl);
        pmodel[guessPtr] = 1;
        if(_solve_util(i, pmodel, guessPtr + 1, out)) {
            return true;
        }
        D(cout << "BT: " << guessPtr << "=1" << endl);

        // Assign literal to false
        D(cout << "G: " << guessPtr << "=-1" << endl);
        pmodel[guessPtr] = -1;
        if(_solve_util(i, pmodel, guessPtr + 1, out)) {
            return true;
        }
        D(cout << "BT: " << guessPtr << "=-1" << endl);

        // Unassign guessed literal
        pmodel[guessPtr] = 0;
        guessPtr++;
    }

    // Cannot guess
    return false;
}

bool solve(Instance& i) {
    int pmodel[i.numv];
    memset(pmodel, 0, sizeof(int) * i.numv);
    bool sat = _solve_util(i, pmodel, 0, pmodel);
    D(
        for(int v = 0; v < i.numv; v++) {
            cout << v << "=" << pmodel[v] << endl;
        }
    );
    return sat;
}
