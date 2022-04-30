#ifndef _MODEL_HH
#define _MODEL_HH

#include <boost/dynamic_bitset.hpp>

using boost::dynamic_bitset;

/**
 * Represents an interpretation
 */
struct Model {
    dynamic_bitset<> pos;
    dynamic_bitset<> neg;
    const int numv;

    Model(int nv): pos(nv), neg(nv), numv(nv) {};
    Model(const Model& b): pos(b.pos), neg(b.neg), numv(b.numv) {};

    int get(int v);
    void reset(int v);
    void set(int v, int p);
    bool isConflict();
    void print();
};

#endif
