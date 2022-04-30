#include <boost/program_options.hpp>
#include <boost/dynamic_bitset.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include "parser.hh"
#include "solver.hh"
#include "verify.hh"
#include "debug.hh"

using namespace std;
namespace po = boost::program_options;

int runFile(string fname)
{
    auto i = parse_dimacs(fname.c_str());
    D({
        cout << "Input formula:" << endl;
        i->print()
    });

    auto m = solve(*i);

    if (m == nullptr)
    {
        return 0;
    }

    D({
        cout << "Final model:" << endl;
        m->print();
    });
    bool check = verify(*i, *m);
    if (!check)
    {
        return -1;
    }

    return 1;
}

void runDir(string dname)
{
    for (const auto &entry : filesystem::directory_iterator(dname))
    {
        if (entry.path().extension() != ".cnf")
        {
            continue;
        }
        int status = runFile(entry.path().c_str());

        cout << entry.path().filename().string() << "\t";
        if (status == 1)
            cout << "T" << endl;
        else if (status == 0)
            cout << "F" << endl;
        else
            cout << "Incorrect Model" << endl;
    }
}

int main(int ac, char **av)
{
    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")("input-file", po::value<string>(), "input file")("test-dir", po::value<string>(), "test dir");

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    // --help
    if (vm.count("help"))
    {
        cout << desc << "\n";
        return 1;
    }

    // no options
    if (!vm.count("input-file") && !vm.count("test-dir"))
    {
        cout << "No .cnf file path provided." << endl;
        return 1;
    }

    // both options
    if (vm.count("input-file") && vm.count("test-dir"))
    {
        cout << "Please enter either input-file or input-dir" << endl;
        return 1;
    }

    // --input-file
    if (vm.count("input-file"))
    {
        auto fname = vm["input-file"].as<string>();
        int status = runFile(fname);
        if (status == 1)
            cout << "T" << endl;
        else if (status == 0)
            cout << "F" << endl;
        else
            cout << "Incorrect Model" << endl;

        int retval = status == -1 ? -1 : 0;
        return retval;
    }

    // --test-dir
    if (vm.count("test-dir"))
    {
        auto dname = vm["test-dir"].as<string>();
        runDir(dname);
        return 0;
    }

    return 0;
}
