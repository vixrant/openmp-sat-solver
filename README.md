# Parallel unit propagation and pure literal elimination
## CS 525: Parallel Computing, Purdue Spring '22.

https://github.com/vixrant/openmp-sat-solver

### Abstract

Herewithin lies an implementation of DPLL algorithm, with deduction steps of unit clause propagation implemented using OpenMP. The aim of this project was to develop a SIMT-compatible algorithm to accelerate the deduction assignments in DPLL using GPGPUs. While parallelising state-space exploration is trivial, a bulk of the work is performed in finding unit clauses. The most optimal algorithm for unit propagation is two-watched literals as proposed by Chaff solver.

My solver uses a matrix representation of input CNF formula and decomposes the input to multiple threads for finding unit clauses, instead of using a lazy data structure. The idea is to find 2 unique, unassigned literals in a clause to prove that the clause is not a unit clause. Therefore, each thread returns its min and max unassigned literals. If such literals are found and unique, then the clause is not a unit clause. Or else the literal is set to the polarity that is present in that clause. However, I found that due to less number of literals in my dataset, the communication overhead was far more than linear search time. Therefore, I disabled it in build files. Secondly, I divided clauses across threads and then reduced the "intermediate models" using logical OR operation. Since my dataset has large number of clauses, this decomposition worked very well for larger problems.

### Technology used

1. CMake for build system
2. OpenMP for multithreading
3. Boost C++ libraries for dynamic_bitset

The implementation can be transferred over to a GPGPU with engineering effort.

### Build Instructions

> PLEASE MAKE SURE BOOST, OPENMP, AND CMAKE ARE INSTALLED ON SYSTEM!

```sh
mkdir build
cd build
cmake . ..
make
```

This would give you `serial_solver` and `parallel_solver`.

CMakeLists file contains a target for `block_parallel_solver` which enables column stripping, however, due to implementation issues, it is commented out.

Some other options for CMake include `-DPRINT_LOGS=1` which tells you the step that the algorithm is performing by printing them out.

### Test Instructions

```sh
./X_solver --help
```

You can run a single file by:
```sh
./X_solver --input-file <path-to-cnf-file>
```

You can test an entire directory of CNF files by:
```sh
./X_solver --test-dir <path-to-cnf-directory>
```

### Benchmarks

CNF files are present in `examples/` directory.

#### Quick testing to check if program runs:

`T_quinn.cnf` and `T_simple_v3_c2.cnf` are small CNF files that can be ran for testing. They are both SAT (T). **PLEASE RUN THESE FOR TESTING IF PROGRAM WORKS**.

#### Benchmarks

1. `uf20-91` has 20 literals, 91 clauses, 1000 files, all SAT (T). Use this benchmark to check for correctness.
2. `short_bulk/uf50-218`, `short_bulk/uuf50-218` has 50 literals, 218 clauses, 1000 files, all SAT (T) and UNSAT (F) respectively. Use these benchmarks for performance information on 3-SAT problems. They should take about 15-45 minutes to run.
3. `benchmarks/` and `samples/` contains more difficult tests that may take some time to finish. Run them if you are ok with waiting a 3-48 hours. Do not run these for now!

Sources:
[1] https://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html
[2] https://www.cs.ubc.ca/~hoos/SATLIB/benchm.html
