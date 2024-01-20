export module module_exported_inner;

import <iostream>;

// Exported definition
export [[maybe_unused]] void hello_from_exported_inner() {
    std::cout << "Hello from exported inner" << std::endl;
}
