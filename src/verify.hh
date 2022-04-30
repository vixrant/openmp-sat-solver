#ifndef _VERIFY_HH_
#define _VERIFY_HH_

#include "instance.hh"
#include "model.hh"

bool verify(Instance& i, Model& m) {
    for(int c = 0; c < i.numc; c++) {
        bool sat = false;

        for(int v = 0; v < i.numv; v++) {
            if(m.get(v) == i.get(c, v)) {
                sat = true;
                break;
            }
        }

        if(!sat) {
            return false;
        }
    }

    return true;
}

#endif
