#include <iostream>

#include <unstd/Array.hpp>
#include <unstd/Vector.hpp>

struct AllocTest {
private:
    int placeholder = 0;
public:
    AllocTest() {}
    AllocTest(int i) : placeholder(i) {}

    AllocTest(const AllocTest& t) : placeholder(t.placeholder) {
        std::cout << "AllocTest Copied" << std::endl;
    }

    AllocTest(AllocTest&& t) : placeholder(std::move(t.placeholder)) {
        std::cout << "AllocTest Moved" << std::endl;
    }

    ~AllocTest() {
        std::cout << "AllocTest Destroyed" << std::endl;
    }

    AllocTest& operator=(const AllocTest& t) {
        std::cout << "AllocTest Copied" << std::endl;
        placeholder = t.placeholder;
        return *this;
    }

    AllocTest& operator=(AllocTest&& t) {
        std::cout << "AllocTest Moved" << std::endl;
        placeholder = std::move(t.placeholder);
        return *this;
    }
};

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
    unstd::Vector<std::string> vector(5);
    std::cout << "vector size: " << vector.Size() << std::endl;
    std::cout << "vector capacity: " << vector.Capacity() << std::endl;
    std::cout << "Vector Created, Pushing Items..." << std::endl;
    vector.PushBack("Testing");
    vector.PushBack("Unstandard Library");
    vector.PushBack("Vectors");
    std::cout << "Checking Vector Size and Capacity..." << std::endl;
    std::cout << "vector size: " << vector.Size() << std::endl;
    std::cout << "vector capacity: " << vector.Capacity() << std::endl;
    
    vector.PushBack("Testing");
    vector.PushBack("Unstandard Library");
    vector.PushBack("Vectors");
    std::cout << "vector size: " << vector.Size() << std::endl;
    std::cout << "vector capacity: " << vector.Capacity() << std::endl;

    vector.PushBack("Testing");
    vector.PushBack("Unstandard Library");
    vector.PushBack("Vectors");
    std::cout << "vector size: " << vector.Size() << std::endl;
    std::cout << "vector capacity: " << vector.Capacity() << std::endl;

    std::cout << "Vectors Copy Semantics..." << std::endl;
    unstd::Vector<AllocTest> allocVector;
    AllocTest tester = AllocTest();
    allocVector.PushBack(tester);
    allocVector.PushBack(tester);
    allocVector.PushBack(tester);
    std::cout << "Vectors Move Semantics..." << std::endl;
    allocVector.PushBack(AllocTest(1));
    allocVector.PushBack(AllocTest(2));
    allocVector.PushBack(AllocTest(3));

    std::cout << "Vector Emplace..." << std::endl;
    unstd::Vector<AllocTest> emplaceVector;
    emplaceVector.EmplaceBack(1);
    emplaceVector.EmplaceBack(2);
    emplaceVector.EmplaceBack(3);

    std::cout << "Vector PopBack..." << std::endl;
    allocVector.PopBack();
    allocVector.PopBack();
    emplaceVector.PopBack();

    std::cout << "Clearing Vectors..." << std::endl;
    vector.Clear();
    allocVector.Clear();
    emplaceVector.Clear();
    
    std::cin.get();
    
}
