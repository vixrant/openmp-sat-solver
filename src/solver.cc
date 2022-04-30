#include <memory>
#include <iostream>
#include <omp.h>
#include "solver.hh"
#include "instance.hh"
#include "debug.hh"

using namespace std;

Status _bcp(Instance& i, Model& m) {
    bool change;
    bool allsat;
    do {
        // If no change is performed in this iteration, there will not be another iteration
        change = 0;
        // Assume all clauses are SAT, unless found otherwise
        allsat = 1;

        for(int c = 0; c < i.numc; c++) {
            int sat, min, max;

            sat = 0; // Flag clause as not SAT
            min = i.numv; // Set min unassigned to upper out bound
            max = -1; // Set max unassigned to lower out bound

            for(int v = 0; v < i.numv; v++) {
                int pol, assgn;

                // Polarity in clause
                pol = i.get(c, v);

                // Literal absent from clause
                if(pol == 0) {
                    continue;
                }

                // Assignment of literal
                assgn = m.get(v);

                // Unassigned literal, add to min or max
                if(m.get(v) == 0) {
                    min = min < v ? min : v;
                    max = max > v ? max: v;
                }
                // Assigned literal, check if it satisfies clause
                else {
                    if(pol == assgn) {
                        sat = 1;
                    }
                }
            }

            // Add clause's status to status of formula
            allsat &= sat;

            // Clause is unsat 
            if(!sat) {
                // No unassigned literals, so we break out
                if(max == -1) {
                    return UNSAT;
                }

                // Check if it is a unit clause
                if(min == max) {
                    // Assign unit clause's literal
                    int p = i.get(c, max);
                    D(cout << "Unit clause: " << c << " setting " << max << " to " << p << endl);
                    m.set(max, p);
                    // Go on with another iteration
                    change = 1;
                }
            }
        } // end of clause checking

        // Check allsat
        if(allsat) {
            D(cout << "All sat" << endl);
            return SAT;
        }

        // Check conflict
        if(m.isConflict()) {
            D({
                cout << "Conflict branch" << endl;
                cout << m.pos << endl;
                cout << m.neg << endl;
            });
            return UNSAT;
        }

        // No conflicts, so continue to next iteration
    } while(change);

    // Formula is neither SAT nor UNSAT
    return UNKNOWN;
}

shared_ptr<Model> _solve_util(Instance& i, Model* prevm, int guessPtr) {
    // Copy model
    shared_ptr<Model> m;
    if(prevm) {
        m = make_shared<Model>(*prevm);
    } else {
        m = make_shared<Model>(i.numv);
    }

    // Do unit propagate
    auto status = _bcp(i, *m);

    // If unit propagate solved instance, return model
    if(status == SAT) {
        return m;
    }

    // If unit propagate found conflict, return nullptr
    if(status == UNSAT) {
        return nullptr;
    }

    // Check if guess pointer literal has been assigned
    // If yes, check next literal to guess
    while(guessPtr < i.numv && m->get(guessPtr) != 0) {
        guessPtr++;
    }

    // Check if all literals have been assigned
    // Then we cannot deduce anything
    if(guessPtr == i.numv) {
        return nullptr;
    }

    // Guess -> T
    D(cout << "Guess " << guessPtr << " -> T" << endl);
    m->set(guessPtr, +1);
    D({
        cout << m->pos << endl;
        cout << m->neg << endl;
    });
    auto mT = _solve_util(i, m.get(), guessPtr + 1);
    // Return SAT only if SAT
    if(mT) return mT;

    // Guess -> F
    D(cout << "Guess " << guessPtr << " -> F" << endl);
    m->reset(guessPtr);
    m->set(guessPtr, -1);
    D({
        cout << m->pos << endl;
        cout << m->neg << endl;
    });
    auto mF = _solve_util(i, m.get(), guessPtr + 1);
    // We cannot guess anything anymore, so return as is
    return mF;
}

//////////////////////////////////////////////////////////////////////

shared_ptr<Model> solve(Instance& i) {
    // Pass it to solver with initial guess pointer as 0
    return _solve_util(i, 0, 0);
};
