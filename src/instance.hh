#ifndef _INSTANCE_HH_
#define _INSTANCE_HH_

/**
 * General class of SAT instance
 * Created from DIMACS file.
 */
struct Instance {
    int* mat; 
    int numc, numv;

    ~Instance() {
        delete mat;
    }

    int initProblem(int numc, int numv);
    int addDimacsLiteral(int clause, int literal);
    int get(int clause, int literal);
};

#endif
