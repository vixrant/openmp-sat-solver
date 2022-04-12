#ifndef _SOLVER_HH_
#define _SOLVER_HH_

enum Status {
    UNSAT = 0,
    SAT = 1,
    UNKNOWN = -1,
};

struct Instance {
    int numc;
    int numv;
    int* mat;

    inline int elemAt(unsigned int c, unsigned int v) {
        return ((int*) mat)[c*numv + v];
    }

    ~Instance() {
        delete mat;
    }
};

bool solve(Instance&);

#endif
