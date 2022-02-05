// -- IMPORTS

#include "scan.hpp"
using namespace pcf;

// -- ATTRIBUTES

SCAN::FUNCTION
    SCAN::PreWriteFunction = nullptr,
    SCAN::PostWriteFunction = nullptr,
    SCAN::PreReadFunction = nullptr,
    SCAN::PostReadFunction = nullptr;
