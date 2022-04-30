#ifndef _SOLVER_HH_
#define _SOLVER_HH_

#include "instance.hh"
#include "model.hh"

/**
 * Represents status of internal computations
 * performed by SAT solver. An intermediate state
 * may be
 * 1. SAT if all clauses are satisfied
 * 2. UNSAT if one clause cannot be satisfied
 * 3. UNKNOWN if some clauses are not SAT
 *      and have unassigned literals
 */
enum Status {
    SAT = 1,
    UNSAT = 0,
    UNKNOWN = -1,
};

/**
 * Interface function that accepts a SAT instance
 * and runs it through DPLL algorithm to return
 * a satisfying model.
 * 
 * The function returns 0 if no satisfying
 * interpretation could be found for the SAT instance.
 */
std::shared_ptr<Model> solve(Instance &);

#endif
