// -- IMPORTS

#include "scan.hpp"

// -- ATTRIBUTES

SCAN::DELEGATE
    SCAN::PreWriteDelegate = nullptr,
    SCAN::PostWriteDelegate = nullptr,
    SCAN::PreReadDelegate = nullptr,
    SCAN::PostReadDelegate = nullptr;
