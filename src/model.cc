#include "model.hh"
#include <iostream>
#include <iomanip>

using namespace std;

int Model::get(int v)
{
    if (pos[v])
        return +1;
    if (neg[v])
        return -1;
    return 0;
}

void Model::reset(int v)
{
    pos.set(v, false);
    neg.set(v, false);
}

void Model::set(int v, int p)
{
    if (p == +1)
        pos.set(v);
    else if (p == -1)
        neg.set(v);
}

bool Model::isConflict()
{
    return (pos & neg).any();
}

void Model::print() {
    for (int v = 0; v < numv; v++)
    {
        cout << setfill(' ') << setw(2) << get(v) << " ";
    }
    cout << endl;
}
