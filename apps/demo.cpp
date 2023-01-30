#include <iostream>

#include <unstd/Array.hpp>

int main(int argc, const char* argv[]) {
    std::cout << "Array..." << std::endl;
    unstd::Array<int, 5> data;
    data[0] = 0;
    data[1] = 1;
    data[2] = 2;
    data[3] = 3;
    data[4] = 4;
    for (int i = 0; i < data.Size(); i++) {
        std::cout << data[i] << std::endl;
    }
    
    std::cin.get();
    
}
