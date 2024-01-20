/**
 * A module partition represents exactly one module unit
 * (two module units cannot designate the same module partition).
 * They are visible only from inside the named module
 * (translation units outside the named module cannot import a module partition directly). [1]
 *
 * Reference:
 * [1] https://en.cppreference.com/w/cpp/language/modules
 */

export module A;

// any exported declarations of A:B are visible to importers of A
export import :B;

// any declarations of A:C are not visible to importers of A
import :C;

// error: cannot export a module implementation unit as A:C is declared without 'export'
//export import :C;
