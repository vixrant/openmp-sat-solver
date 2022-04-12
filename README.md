# Parallel unit propagation and pure literal elimination
## CS 525: Parallel Computing, Purdue Spring '22.

### Abstract

Herewithin lies an implementation of DPLL algorithm, with deduction steps of unit clause propagation and pure literal elimination implemented using OpenMPI. The aim of this project was to develop a SIMT-compatible algorithm to accelerate the deduction assignments in DPLL using GPGPUs. While parallelising state-space exploration is trivial, a bulk of the work is performed in finding unit clauses and pure literals. The most optimal algorithm for unit propagation is two-watched literals, which disables the solver from finding pure literals in an efficient manner. Therefore, my solver uses a matrix representation of input CNF formula and decomposes the input to multiple processors for partial deductions. The partial deductions are later reduced and then analysed to find unit clauses and pure literals.

### Build Instructions

```
mkdir build
cd build
cmake . ..
make
```

This would give you `serialsat`, `test_serial`, `parallelsat`, `test_parallel`.
