#include "solver.hh"
#include "instance.hh"
#include "model.hh"
#include <memory>

using namespace std;

Status _bcp(Instance& i, Model& imodel) {
    bool change = 1;
    for(int c = 0; c < i.numc; c++) {
        
    }
}

bool _solve_util(Instance& i, Model& m, int guessPtr) {
    // Do unit propagate
    auto status = _bcp(i, m);
    if(status != UNKNOWN) return status;

    // Check if guess pointer literal has been assigned
    // If yes, check next literal to guess
    while(guessPtr < i.numv && m.get(guessPtr) != 0) {
        guessPtr++;
    }

    // Check if all literals have been assigned
    // Then we cannot deduce anything
    if(guessPtr == i.numv) {
        return 0;
    }

    // status variable
    bool sat;

    // Guess -> T
    m.set(guessPtr, +1);
    sat = _solve_util(i, m, guessPtr + 1);
    // Return SAT only if SAT
    if(sat) return true;

    // Guess -> F
    m.set(guessPtr, -1);
    sat = _solve_util(i, m, guessPtr + 1);
    // We cannot guess anything anymore, so return as is
    return sat;
}

//////////////////////////////////////////////////////////////////////

shared_ptr<Model> solve(Instance& i) {
    // Create a model to be returned
    auto m = new Model(i.numv);

    // Pass it to solver with initial guess pointer as 0
    auto sat = _solve_util(i, *m, 0);
    if(!sat) {
        delete m;
        return 0;
    }

    // Wrap in smart pointer for collection
    return make_shared<Model>(m);
};
