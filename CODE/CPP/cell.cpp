// -- IMPORTS

#include "cell.hpp"

// -- ATTRIBUTES

CELL::DELEGATE
    CELL::PreWriteDelegate = nullptr,
    CELL::PostWriteDelegate = nullptr,
    CELL::PreReadDelegate = nullptr,
    CELL::PostReadDelegate = nullptr;
