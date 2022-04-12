#include "solver.hh"
#include "parser.hh"
#include "debug.hh"
#include <iostream>
#include <memory>

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2) {
        cout << "Enter file name" << endl;
        return 1;
    }

    ifstream f(argv[1]);
    auto i = parse_dimacs(f);
    f.close();
    cout << "c/l" << "\t";
    for(int v = 0; v < i->numv; v++) {
        cout << v << "\t";
    }
    cout << endl;
    for(int c = 0; c < i->numc; c++) {
        cout << c << "\t";
        for(int v = 0; v < i->numv; v++) {
            cout << i->elemAt(c, v) << "\t";
            if(i->elemAt(c, v) == 0) {
                cout << " ";
            }
        }
        cout << endl;
    }

    bool sat = solve(*i);
    cout << "sat=" << (sat ? "T" : "F") << endl;

    delete i;
}
