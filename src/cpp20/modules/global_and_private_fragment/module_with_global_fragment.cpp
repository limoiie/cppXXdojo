/**
 * Module units can be prefixed by a global module fragment,
 * which can be used to include headers when importing the headers is not possible
 * (notably when the header uses preprocessing macros as configuration) [1].
 *
 * Reference:
 * [1] https://en.cppreference.com/w/cpp/language/modules
 */

/////////////////////////////////////////////
/// here we define the global module fragment
/////////////////////////////////////////////
module;

// If a module-unit has a global module fragment,
// the `module` declaration must be the first declaration in the module-unit.

// Defining _POSIX_C_SOURCE adds functions to standard headers,
// according to the POSIX standard.
#define _POSIX_C_SOURCE 200809L // NOLINT(*-reserved-identifier)

#include <cstdlib>

/////////////////////////////////////////////
// end of the global module fragment
/////////////////////////////////////////////

// here is the normal module unit
export module module_with_global_fragment;

import <ctime>;

// Only for demonstration (bad source of randomness).
// Use C++ <random> instead.
export [[maybe_unused]] double weak_random() {
    std::timespec ts{};
    std::timespec_get(&ts, TIME_UTC);
    srand48(ts.tv_nsec);
    return drand48();
}
