#include "instance.hh"
#include <cstring>
#include <cstdlib>

/**
 * Initialises matrix as specified by dimacs
 * format "p <numc> <numv>".
 */
int Instance::initProblem(int nc, int nv) {
    // set metadata
    numc = nc;
    numv = nv;
    // initialise 1D contigious array
    mat = (int*) calloc(numc * numv, sizeof(int));
    // if unable to allocate memory, return 0
    if(mat == nullptr) {
        return -1;
    }
    // set all cells to 0
    memset(mat, 0, sizeof(int) * numc * numv);
    return 0;
}

/**
 * Adds literal from dimacs format
 */
int Instance::addDimacsLiteral(int c, int v) {
    // check bounds
    if(v > numv || v < -numv) {
        return -1;
    }
    int pol = v > 0 ? 1 : -1; // polarity in matrix
    v = abs(v) - 1;
    mat[c*numv + v] = pol; // set matrix cell to polarity
    return 0;
}

/**
 * Retrieves element from 2D matrix stored in 1D format
 */
int Instance::get(int c, int v) {
    return mat[c*numv + v];
}
