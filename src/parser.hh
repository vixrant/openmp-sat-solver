#ifndef _PARSER_HH_
#define _PARSER_HH_

#include <memory>
#include "instance.hh"

using std::shared_ptr;

shared_ptr<Instance> parse_dimacs(const char* fname);

#endif
