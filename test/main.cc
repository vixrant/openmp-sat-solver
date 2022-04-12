#include "solver.hh"
#include "parser.hh"
#include "debug.hh"
#include <iostream>
#include <memory>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    if(argc < 2) {
        cout << "Enter folder path" << endl;
        return 1;
    }

    for (const auto & entry : fs::directory_iterator(argv[1])) {
        if(!entry.is_regular_file() || entry.path().extension() != ".cnf") {
            continue;
        }

        ifstream f(entry.path());
        auto i = parse_dimacs(f);
        f.close();

        bool sat = solve(*i);
        cout << entry.path() << " sat=" << (sat ? "T" : "F") << endl;

        delete i;
    }
}
