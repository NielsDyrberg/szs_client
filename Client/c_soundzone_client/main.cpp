#include <iostream>
#include "c_project_test/c_project_test.h"
#include "test_src.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << test_projectLink() << std::endl;
    testSrcHello();
    return 0;
}
