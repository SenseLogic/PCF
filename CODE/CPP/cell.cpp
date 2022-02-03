// -- IMPORTS

#include "cell.hpp"
using namespace pcf;

// -- ATTRIBUTES

CELL::DELEGATE
    CELL::PreWriteDelegate = nullptr,
    CELL::PostWriteDelegate = nullptr,
    CELL::PreReadDelegate = nullptr,
    CELL::PostReadDelegate = nullptr;
