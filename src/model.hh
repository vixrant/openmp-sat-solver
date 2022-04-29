#ifndef _MODEL_HH_
#define _MODEL_HH_

#include <cstring>

/**
 * General class of SAT interpretation
 */
struct Model {
    bool* pos; 
    bool* neg; 
    int numv;

    Model(int numv): numv(numv) {
        pos = new bool[numv];
        neg = new bool[numv];
        memset(pos, 0, sizeof(bool) * numv);
        memset(neg, 0, sizeof(bool) * numv);
    } 

    ~Model() {
        delete pos;
        delete neg;
    }

    int initModel(int numv);
    int set(int v, int p);
    int reset(int v);
    int get(int v);
    bool isConflict();
};

#endif
