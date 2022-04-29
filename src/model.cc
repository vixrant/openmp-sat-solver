#include "model.hh"

int Model::initModel(int nv) {
    numv = nv;
    pos = new bool[nv];
    if(pos == 0) return -1;
    neg = new bool[nv];
    if(neg == 0) return -1;
    return 0;
}

int Model::set(int v, int p) {
    if(v >= numv) return -1;
    if(p == +1) pos[v] = 1;
    else neg[v] = 1;
    return 0;
}

int Model::reset(int v) {
    if(v >= numv) return -1;
    pos[v] = 0;
    neg[v] = 0;
    return 0;
}

int Model::get(int v) {
    if(v >= numv) return -1;
    if(pos[v] == 1) return 1;
    else return -1;
}

bool Model::isConflict() {
    for(int v = 0; v < numv; v++) {
        if(pos[v] && neg[v]) {
            return 1;
        }
    }
    return 0;
}
