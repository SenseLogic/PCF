// -- IMPORTS

#include "cell.hpp"
using namespace pcf;

// -- ATTRIBUTES

CELL::FUNCTION
    CELL::PreWriteFunction = nullptr,
    CELL::PostWriteFunction = nullptr,
    CELL::PreReadFunction = nullptr,
    CELL::PostReadFunction = nullptr;
