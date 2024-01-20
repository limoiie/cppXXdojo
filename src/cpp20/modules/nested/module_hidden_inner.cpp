export module module_inner;

import <iostream>;

// Exported definition
export [[maybe_unused]] void hello_from_hidden_inner() {
    std::cout << "Hello from hidden module inner" << std::endl;
}
