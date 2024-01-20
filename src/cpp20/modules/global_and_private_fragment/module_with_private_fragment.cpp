/**
 * Primary module interface unit can be suffixed by a private module fragment,
 * which allows a module to be represented as a single translation unit
 * without making all of the contents of the module reachable to importers.[1]
 *
 * Reference:
 * [1] https://en.cppreference.com/w/cpp/language/modules
 */

export module module_with_private_fragment;

export [[maybe_unused]] int f();

/////////////////////////////////////////////
/// here we define the private module fragment
///
/// ends the portion of the module interface unit that
/// can affect the behavior of other translation units
/// starts a private module fragment
/////////////////////////////////////////////
module : private;

// If a module unit contains a private module fragment,
// it will be the only module unit of its module.

// definition not reachable from importers of foo
[[maybe_unused]] int f() { return 42; }
