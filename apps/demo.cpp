#include <iostream>

#include <unstd/Array.hpp>
#include <unstd/Vector.hpp>

int main(int argc, const char* argv[]) {
    std::cout << "Array..." << std::endl;
    unstd::Array<int, 5> data;
    data[0] = 0;
    data[1] = 1;
    data[2] = 2;
    data[3] = 3;
    data[4] = 4;
    std::cout << "Manual Loop..." << std::endl;
    for (int i = 0; i < data.Size(); i++) {
        std::cout << data[i] << std::endl;
    }
    std::cout << "Iterators..." << std::endl;
    for (auto& value : data) {
        std::cout << value << std::endl;
    }

    std::cout << "Vectors..." << std::endl;
    unstd::Vector<std::string> vector = unstd::Vector<std::string>(5);
    vector.PushBack("Testing");
    vector.PushBack("Unstandard Library");
    vector.PushBack("Vectors");
    std::cout << "vector size: " << vector.Size() << std::endl;
    
    std::cin.get();
    
}
