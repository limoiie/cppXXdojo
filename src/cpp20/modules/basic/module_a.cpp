export module module_a;

// Exported definition
export [[maybe_unused]] char const *hello_from_hidden_inner() {
    return "Hello";
}

// Exported multiple definitions
export {
    [[maybe_unused]] int add(int a, int b) {
        return a + b;
    }

    [[maybe_unused]] int minus(int a, int b) {
        return a - b;
    }

}

// Exported namespace
export namespace hi {
    [[maybe_unused]] char const *english() {
        return "Hi!";
    }

    [[maybe_unused]] char const *french() {
        return "Sa-lut!";
    }
}

// Inner module
[[maybe_unused]] char const *world() {
    return "World";
}
