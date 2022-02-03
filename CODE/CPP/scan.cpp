// -- IMPORTS

#include "scan.hpp"
using namespace pcf;

// -- ATTRIBUTES

SCAN::DELEGATE
    SCAN::PreWriteDelegate = nullptr,
    SCAN::PostWriteDelegate = nullptr,
    SCAN::PreReadDelegate = nullptr,
    SCAN::PostReadDelegate = nullptr;
