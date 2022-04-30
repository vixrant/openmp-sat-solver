# Parallel unit propagation and pure literal elimination
## CS 525: Parallel Computing, Purdue Spring '22.
https://github.com/vixrant/parallel-sat-solver

### Abstract

Herewithin lies an implementation of DPLL algorithm, with deduction steps of unit clause propagation implemented using OpenMP. The aim of this project was to develop a SIMT-compatible algorithm to accelerate the deduction assignments in DPLL using GPGPUs. While parallelising state-space exploration is trivial, a bulk of the work is performed in finding unit clauses. The most optimal algorithm for unit propagation is two-watched literals as proposed by Chaff solver.

My solver uses a matrix representation of input CNF formula and decomposes the input to multiple threads for finding unit clauses, instead of using a lazy data structure. The idea is to find 2 unique, unassigned literals in a clause to prove that the clause is not a unit clause. Therefore, each thread returns its min and max unassigned literals. If such literals are found and unique, then the clause is not a unit clause. Or else the literal is set to the polarity that is present in that clause.

### Technology used

1. CMake for build system
2. OpenMP for multithreading
3. Boost C++ libraries for data structures

The implementation can be transferred over to a GPGPU using OpenMP target offloading.

### Build Instructions

> PLEASE MAKE SURE BOOST, OPENMP, AND CMAKE ARE INSTALLED ON SYSTEM!

#### Parallel Implementation

```
mkdir build
cd build
cmake . ..
make
```

This would give you `solver` program.

### Test Instructions

```
./solver <path-to-cnf-file>
```

CNF files are present in `examples/` directory. `uf20-91` has 20 literals, 91 clauses, all SAT. `uuf50.218.1000` has 218 literals, 1000 clauses, all UNSAT.
