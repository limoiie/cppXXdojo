export module module_outer;

export import module_exported_inner;
import module_inner;

import <iostream>;

// Exported definition
export [[maybe_unused]] void hello_nested() {
    hello_from_hidden_inner();
    hello_from_exported_inner();
    std::cout << "Hello from module outer" << std::endl;
}
