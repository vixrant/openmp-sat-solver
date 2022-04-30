#include <memory>
#include <iostream>
#include <algorithm>
#include <omp.h>
#include "solver.hh"
#include "instance.hh"
#include "debug.hh"

using namespace std;

Status _bcp
(Instance &i, Model &m)
{
    bool change; // Loop when model changes

    do
    {
        change = 0; // If no change is performed in this iteration, there will not be another iteration

        bool allsat = 1;    // Assume all clauses are SAT, unless found otherwise
        bool roadblock = 0; // No assignable variables for a clause

        #pragma omp parallel \
            for \
            if(ROW_STRIP == 1) \
            shared(i, m, change) \
            reduction(&&: allsat) \
            reduction(||: roadblock) \
            num_threads(i.numc)
        for (int c = 0; c < i.numc; c++)
        {
            bool sat = 0;      // Flag clause as not SAT
            int minv = i.numv; // Set min unassigned to upper out bound
            int maxv = -1;     // Set max unassigned to lower out bound

            #pragma omp parallel \
                for \
                if(COL_STRIP == 1) \
                shared(i, m) \
                reduction(||: sat) \
                reduction(min: minv) \
                reduction(max: maxv) \
                num_threads(i.numv)
            for (int v = 0; v < i.numv; v++)
            {
                // Polarity in clause
                int pol = i.get(c, v);
                // Literal absent from clause
                if (pol == 0)
                {
                    continue;
                }

                // Assignment of literal
                int assgn = m.get(v);
                // Unassigned literal, add to min or max
                if (m.get(v) == 0)
                {
                    minv = min(minv, v);
                    maxv = max(maxv, v);
                }
                // Assigned literal, check if it satisfies clause
                else if (pol == assgn)
                {
                    sat = 1;
                }
            } // end of min, max, sat search

            // Add clause's status to status of formula
            allsat &= sat;

            // Clause is unsat
            if (!sat)
            {
                // No unassigned literals, so we break out
                if (maxv == -1)
                {
                    roadblock = 1;
                }
                // Check if it is a unit clause
                else if (minv == maxv)
                {
                    // Assign unit clause's literal
                    int p = i.get(c, maxv);
                    D(cout << "Unit clause: " << c << " setting " << maxv << " to " << p << endl);
                    m.set(maxv, p);
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

        // Check if an UNSAT clause has no variables left to assign
        if(roadblock) {
            D(cout << "UNSAT clause" << endl);
            return UNSAT;
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
    } while (change);

    // Formula is neither SAT nor UNSAT
    return UNKNOWN;
}

shared_ptr<Model> _solve_util
(Instance &i, Model *prevm, int guessPtr)
{
    // Copy model
    shared_ptr<Model> m;
    if (prevm)
    {
        m = make_shared<Model>(*prevm);
    }
    else
    {
        m = make_shared<Model>(i.numv);
    }

    // Do unit propagate
    auto status = _bcp(i, *m);

    // If unit propagate solved instance, return model
    if (status == SAT)
    {
        return m;
    }

    // If unit propagate found conflict, return nullptr
    if (status == UNSAT)
    {
        return nullptr;
    }

    // Check if guess pointer literal has been assigned
    // If yes, check next literal to guess
    while (guessPtr < i.numv && m->get(guessPtr) != 0)
    {
        guessPtr++;
    }

    // Check if all literals have been assigned
    // Then we cannot deduce anything
    if (guessPtr == i.numv)
    {
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
    if (mT)
        return mT;

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

shared_ptr<Model> solve
(Instance &i)
{
    // Pass it to solver with initial guess pointer as 0
    return _solve_util(i, 0, 0);
};
