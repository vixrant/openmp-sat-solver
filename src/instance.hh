#ifndef _INSTANCE_HH_
#define _INSTANCE_HH_

#include <boost/dynamic_bitset.hpp>

using boost::dynamic_bitset;

/**
 * General class of SAT instance
 * Created from DIMACS file.
 */
struct Instance {
    dynamic_bitset<> pos;
    dynamic_bitset<> neg;
    const int numc, numv;


    Instance(int nc, int nv):
        pos(nc*nv),
        neg(nc*nv),
        numc(nc),
        numv(nv)
        {};

    /** Adds literal from dimacs format */
    void addDimacsLiteral(int clause, int literal);
    /** Retrieves element from 2D matrix stored in 1D format */
    int get(int clause, int literal);
    /** Prints instance in matrix format */
    void print();
};

#endif
